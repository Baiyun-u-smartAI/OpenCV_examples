import cv2 as cv
import numpy as np
import pathlib
import time
if __name__ == "__main__":
    Path = list()
    # 将训练集training的所有数据导入进来trainDataPath
    trainDataPath = list(list())
    testDataPath = list(list())
    for i in range(0, 10):

        Path.append(pathlib.Path('MNIST/training/'+str(i))) # 把MNIST/training/里面的所有目录添加到Path里

        _data = list()
        # 找到上述的Path里找png图片
        for name in Path[i].glob("*.png"):
            _data.append(str(name))
        trainDataPath.append(_data) # 把找到的所有路径添加到trainDataPath

    # 将测试集testing的所有数据导入进来testDataPath
    for i in range(0, 10):

        Path.append(pathlib.Path('MNIST/testing/'+str(i)))

        _data = list()
        for name in Path[i].glob("*.png"):
            _data.append(str(name))
        testDataPath.append(_data)


    # 训练
    if False:
        # 获取训练集数据
        trainData = list()
        trainLabel = list()
        for i in range(0, 10):
            for j in range(0, len(trainDataPath[i])):
                a = cv.imread(trainDataPath[i][j], cv.IMREAD_GRAYSCALE)
                a = a.reshape(-1, 28 * 28).astype(np.float32)[0] # 展平数据
                trainData.append(a)
                trainLabel.append(i)
        trainLabel = np.array(trainLabel)
        trainData = np.array(trainData)

        # print(trainData.shape, trainLabel.shape)
        # 训练
        knn = cv.ml.KNearest_create()
        knn.setIsClassifier(True)
        knn.setDefaultK(5)  # k的值设置为5
        knn.train(trainData, cv.ml.ROW_SAMPLE, trainLabel)
        knn.save('mnist_knn.xml')  # 保存

    knn = cv.ml.KNearest_load('mnist_knn.xml')


    # 获取测试集数据
    testData = list()
    testLabel = list()
    for i in range(0, 10):
        for j in range(0, len(testDataPath[i])//10):
            a = cv.imread(testDataPath[i][j], cv.IMREAD_GRAYSCALE)
            a = a.reshape(-1, 28 * 28).astype(np.float32)[0]
            testData.append(a)
            testLabel.append(i)
    testLabel = np.array(testLabel)

    testData = np.array(testData)




    # 测试一张图
    # img = cv.imread('MNIST/testing/3/309.png', cv.IMREAD_GRAYSCALE)
    # img = img.astype(np.float32)
    # img = img.reshape(-1, )
    # img = img.reshape(1, -1)
    
    begin = time.time()
    img_pre = knn.predict(testData)
    end = time.time()
    print(img_pre[1].reshape(-1, ).shape, testLabel.shape)
    corr = (img_pre[1].reshape(-1, ) == testLabel)
    corr = np.sum(corr)

    print(corr / testLabel.shape[0])
    print(f'last time: {end-begin}\naverage: { (end-begin)/testLabel.shape[0] }')
