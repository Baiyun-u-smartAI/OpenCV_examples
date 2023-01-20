import sys

import cv2 as cv
import numpy as np

if __name__ == "__main__":
    # 读图，场景图<->目标图
    object = cv.imread("box.png")
    scene = cv.imread("box_in_scene.png")
    # 创建描述符对象detector
    detector = cv.AKAZE_create() # ORB_create()  BRISK_create()
    # 计算描述子
    keyPoint_object, descrs_object = detector.detectAndCompute(object, None)
    keyPoint_scene, descrs_scene = detector.detectAndCompute(scene, None)
    # 暴力匹配对象matcher
    matcher = cv.BFMatcher(cv.NORM_HAMMING)
    # 创建匹配
    matches = matcher.match(descrs_object, descrs_scene)
    if len(matches) == 0:
        print("BFMatcher 找不到任何匹配!!!")
        sys.exit(-1)

    maxdist = max([m.distance for m in matches]) # 匹配的最大汉明距离
    thresh = .5
    goodMatches = []
    for match in matches:
        if match.distance < thresh * maxdist: # 如果匹配的距离小于最大的50%，认为匹配效果好
            goodMatches.append(match)
    if len(goodMatches) < 2:
        print("BFMatcher 找不到任何有效的匹配!!!")
        sys.exit(-1)
    dst = None
    # 绘制好的匹配点
    dst = cv.drawMatches(object, keyPoint_object, scene, keyPoint_scene, goodMatches, dst, matchColor=[-1,-1,-1], singlePointColor= [-1,-1,-1], flags=cv.DRAW_MATCHES_FLAGS_DEFAULT)
    cv.imshow("pure AKAZE Matches", dst)
    cv.waitKey()

    # goodMatch 里面的数据是queryIdx对应的是keyPoint_object的序号，trainIdx对应的是keyPoint_scene的序号

    # RANSAC优化 (随机抽样一致算法)
    matches_ransac = []
    objectPoints, scenePoints = [], []
    for goodMatch in goodMatches:
        objectPoints.append(keyPoint_object[goodMatch.queryIdx].pt)
        scenePoints.append(keyPoint_scene[goodMatch.trainIdx].pt)

    if len(objectPoints) < 4 or len(scenePoints) < 4 or len(objectPoints)+len(scenePoints) < 9:
        print("匹配点数过少")
        sys.exit(1)
    # inliersMask = np.zeros(len(objectPoints), dtype=np.uint8)

    # 进行投影变换矩阵求解，inliersMask代表输入点的有效性
    H, inliersMask = cv.findHomography(np.array(objectPoints), np.array(scenePoints), cv.RANSAC, ransacReprojThreshold=4)
    for i in range(len(inliersMask)):
        if inliersMask[i]:
            matches_ransac.append(goodMatches[i])


    dst = cv.drawMatches(object, keyPoint_object, scene, keyPoint_scene, matches_ransac, dst, matchColor=[-1, -1, -1],
                         singlePointColor=[-1, -1, -1], flags=cv.DRAW_MATCHES_FLAGS_NOT_DRAW_SINGLE_POINTS)
    cv.imshow("RANSAC AKAZE", dst)
    cv.waitKey()

    x, y = 0., 0.
    rows, cols, _ = object.shape
    # 这是object图的四个点（按照顺时针、逆时针顺序）
    points = np.float32([[x, y], [cols-1, y], [cols-1, rows-1], [x, rows-1]])

    # object_p = []
    # for i in matches_ransac:
    #     object_p.append(keyPoint_object[i.queryIdx].pt)
    #
    # cv.polylines(object, [np.int32(object_p)], True, (255, 0, 0), 2)
    #
    #
    # cv.imshow("Zone_object", object)
    # cv.waitKey()
    # 用刚才得到的H做投影变换
    points = cv.perspectiveTransform(points.reshape(1, -1, 2), H).reshape(-1, 2)
    # 变换后的四个点用polylines来绘制四边形
    cv.polylines(scene, [np.int32(points)], True, (255, 0, 0), 2)

    # object_s = []
    # for i in matches_ransac:
    #     object_s.append(keyPoint_scene[i.trainIdx].pt)
    #
    # cv.polylines(scene, [np.int32(object_s)], True, (255, 0, 0), 2)


    cv.imshow("Zone", scene)
    cv.waitKey()

    cv.destroyAllWindows()