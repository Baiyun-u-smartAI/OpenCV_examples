import cv2 as cv
import glob
import sys
def create_opencv_xml():
    s = cv.FileStorage("data.xml", cv.FileStorage_WRITE)
    imagesName = glob.glob("*.jpg") + glob.glob("*.png") + glob.glob("*.bmp")
    s.write("images", imagesName)
    s.release()

def read_opencv_xml():
    s = cv.FileStorage("data.xml", cv.FileStorage_READ)
    node = s.getNode("images")
    imageNames = []
    if (not node.isSeq()):
        print('strings is not a sequence! FAIL', file=sys.stderr)
        exit(1)
    for i in range(node.size()):
        print(node.at(i).string())
        imageNames.append(node.at(i).string())
    s.release()
    return imageNames

if __name__ == "__main__":
    create_opencv_xml()
    print(read_opencv_xml())