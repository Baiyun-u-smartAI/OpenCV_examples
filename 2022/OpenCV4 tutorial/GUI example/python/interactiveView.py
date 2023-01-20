# This Python file uses the following encoding: utf-8
from PySide2.QtWidgets import QGraphicsView
from PySide2.QtGui import QKeyEvent, QMouseEvent, QWheelEvent, QPainter
import numpy as np
from PySide2.QtCore import Qt, QPointF, QPoint, QRectF
from PySide2.QtCore import Slot


class InteractiveView(QGraphicsView):
    def __init__(self, parent=None):
        super().__init__(parent)
        self.m_translateButton = Qt.MouseButton(Qt.LeftButton)
        self.m_translateSpeed: np.float64 = 1.0
        self.m_zoomDelta: np.float64 = 0.1
        self.m_bMouseTranslate = False
        self.m_scale: np.float64 = 1.0
        # 去掉滚动条
        super().setHorizontalScrollBarPolicy(Qt.ScrollBarAlwaysOff)
        super().setVerticalScrollBarPolicy(Qt.ScrollBarAlwaysOff)
        # 设置光标图案
        super().setCursor(Qt.PointingHandCursor)
        super().setRenderHint(QPainter.Antialiasing)
        super().setSceneRect(-2147483648/2, -2147483648/2,
                             2147483647, 2147483647)
        super().centerOn(0, 0)

    # 设置平移速度
    def setTranslateSpeed(self, speed: np.float64):
        self.m_translateSpeed = speed

    # 输出平移速度
    def translateSpeed(self):
        return self.m_translateSpeed

    # 设置缩放比例
    def setZoomDelta(self, delta: np.float64):
        self.m_zoomDelta = delta

    # 显示缩放比例
    def zoomDelta(self) -> np.float64:
        return self.m_zoomDelta

    # 上/下/左/右键向各个方向移动、加/减键进行缩放、空格/回车键旋转
    def keyPressEvent(self, event: QKeyEvent):
        if event.key() == Qt.Key_Up:  # ↑
            self.translate(QPointF(0, -2))
        elif event.key() == Qt.Key_Down:  # ↓
            self.translate(QPointF(0, 2))
        elif event.key() == Qt.Key_Left:  # ←
            self.translate(QPointF(-2, 0))
        elif event.key() == Qt.Key_Right:  # →
            self.translate(QPointF(2, 0))
        elif event.key() == Qt.Key_Plus:  # +
            self.zoomIn()  # 放大
        elif event.key() == Qt.Key_Minus:  # -
            self.zoomOut()  # 缩小
        elif event.key() == Qt.Key_Space:  # ␣
            super().rotate(-.5)  # 逆时针旋转
        elif event.key() == Qt.Key_Enter or event.key() == Qt.Key_Return:  # ↳
            super().rotate(.5)  # 顺时针旋转
        else:
            super().keyPressEvent(event)

    # 平移
    def mouseMoveEvent(self, event: QMouseEvent):
        if self.m_bMouseTranslate:
            mouseDelta: QPointF = super().mapToScene(event.pos())\
                                  - super().mapToScene(self.m_lastMousePos)
            self.translate(mouseDelta)
        self.m_lastMousePos = event.pos()
        super().mouseMoveEvent(event)

    def mousePressEvent(self, event: QMouseEvent):
        if event.button() == self.m_translateButton:
            point: QPointF = super().mapToScene(event.pos())
            # 当光标底下没有 item 时，才能移动
            if super().scene().itemAt(point, super().transform()) is None:
                self.m_bMouseTranslate = True
                self.m_lastMousePos = event.pos()
        super().mousePressEvent(event)

    def mouseReleaseEvent(self, event: QMouseEvent):
        if event.button() == self.m_translateButton:
            self.m_bMouseTranslate = False
        super().mouseReleaseEvent(event)

    # 放大/缩小
    def wheelEvent(self, event: QWheelEvent):
        # 滚轮的滚动量
        scrollAmount: QPoint = event.angleDelta()
        # 正值表示滚轮远离使用者（放大），负值表示朝向使用者（缩小）
        if scrollAmount.y() > 0:
            self.zoomIn()
        else:
            self.zoomOut()

    # 放大的槽函数
    @Slot()
    def zoomIn(self):
        self.zoom(1+self.m_zoomDelta)

    # 缩小的槽函数
    @Slot()
    def zoomOut(self):
        self.zoom(1-self.m_zoomDelta)

    # 缩放 - scaleFactor：缩放的比例因子
    @Slot(np.float32)
    def zoom(self, scaleFactor: np.float32):
        # 防止过小或过大
        factor: np.float64 = super().transform()\
                             .scale(scaleFactor, scaleFactor)\
                             .mapRect(QRectF(0, 0, 1, 1)).width()
        if factor < 0.07 or factor > 100:
            return None
        super().scale(scaleFactor, scaleFactor)
        self.m_scale *= scaleFactor

    # 平移
    @Slot(QPointF)
    def translate(self, delta: QPointF):
        # 根据当前 zoom 缩放平移数
        delta *= self.m_scale
        delta *= self.m_translateSpeed

        # view 根据鼠标下的点作为锚点来定位 scene
        super().setTransformationAnchor(QGraphicsView.AnchorUnderMouse)

        vWidth = super().viewport().rect().width()
        vHeight = super().viewport().rect().height()
        # vCenter = super().viewport().rect().center()

        newCenter: QPoint = QPoint(vWidth/2 - delta.x(), vHeight/2 - delta.y())
        super().centerOn(super().mapToScene(newCenter))

        super().setTransformationAnchor(QGraphicsView.AnchorViewCenter)
