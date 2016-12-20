//
// Created by tom on 16-12-20.
//

#include "FrameWdg.h"
#include <QPainter>
#include <QPaintEvent>

FrameWdg::FrameWdg(QWidget *parent)
        : QOpenGLWidget(parent) {
    resize(200, 200);
}


void FrameWdg::showImage(const QImage &image) {
    _image = image;
    repaint();
}

void FrameWdg::paintEvent(QPaintEvent *event) {
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawImage(rect(), _image);
    painter.end();
}