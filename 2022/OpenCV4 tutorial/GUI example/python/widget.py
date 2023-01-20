# This Python file uses the following encoding: utf-8

import sys
from interactiveView import InteractiveView
from PySide2.QtWidgets import QApplication, QWidget, QPushButton,\
                              QGraphicsScene, QGraphicsView, QGridLayout,\
                              QLabel, QSlider

import PySide2.QtGui as QtGui
import numpy as np
from PySide2.QtCore import Slot, Qt, QSize
import cv2 as cv


class Widget(QWidget):
    def __init__(self):
        super(Widget, self).__init__()
        self.load_ui()
        self.pushButton.clicked.connect(self.showImage)
        self.gScene: QGraphicsScene = QGraphicsScene()
        self.horizontalSlider.sliderMoved.connect(self.update_label)
        self.img = None

    @Slot()
    def showImage(self):
        self.img = cv.imread(r'b79e6bbcc064cbcec5e573394406a081.png',
                             cv.IMREAD_COLOR)
        if self.img is None:
            print("read Image fail")
            return None
        gView: QGraphicsView = self.graphicsView
        img = QtGui.QImage(self.img.data, self.img.shape[1],
                           self.img.shape[0],
                           QtGui.QImage.Format_RGB888).rgbSwapped()
        self.gScene.clear()
        self.gScene.addPixmap(QtGui.QPixmap.fromImage(img))
        gView.setScene(self.gScene)
        gView.update()
        self.horizontalSlider.setValue(0)
        self.label.setText("0")

    @Slot(int)
    def update_label(self, val: int) -> None:
        self.label.setText(str(val))
        if self.img is not None:

            dst = np.array(self.img, dtype=np.int16)
            dst[:, :, :] += val
            dst = np.maximum(dst, np.zeros((dst.shape[0], dst.shape[1],
                             dst.shape[2]), dtype=np.int16))  # 负数变成0
            dst = np.minimum(dst, np.ones((dst.shape[0], dst.shape[1],
                             dst.shape[2]), dtype=np.int16)*255)  # 超过255变成255

            dst = np.array(dst, dtype=np.uint8)
            gView: QGraphicsView = self.graphicsView
            dst = QtGui.QImage(dst.data, dst.shape[1], dst.shape[0],
                               QtGui.QImage.Format_RGB888).rgbSwapped()
            self.gScene.clear()
            self.gScene.addPixmap(QtGui.QPixmap.fromImage(dst))
            gView.setScene(self.gScene)
            gView.update()

    def load_ui(self):
        self.resize(720, 720)
        self.gridLayout = QGridLayout(self)
        self.graphicsView = InteractiveView(self)
        self.gridLayout.addWidget(self.graphicsView, 1, 0, 1, 2)

        self.pushButton = QPushButton(self)
        self.pushButton.setText("reset")
        self.gridLayout.addWidget(self.pushButton, 2, 0, 1, 2)

        self.label = QLabel(self)
        self.label.setMinimumSize(QSize(40, 0))
        font = QtGui.QFont()
        font.setPointSize(20)
        self.label.setFont(font)
        self.label.setAlignment(Qt.AlignCenter)
        self.label.setText("0")
        self.gridLayout.addWidget(self.label, 3, 1, 1, 1)

        self.horizontalSlider = QSlider(self)
        self.horizontalSlider.setMinimum(-255)
        self.horizontalSlider.setValue(0)
        self.horizontalSlider.setMaximum(255)
        self.horizontalSlider.setOrientation(Qt.Horizontal)

        self.gridLayout.addWidget(self.horizontalSlider, 3, 0, 1, 1)


if __name__ == "__main__":
    app = QApplication([])
    widget = Widget()
    widget.show()
    sys.exit(app.exec_())
