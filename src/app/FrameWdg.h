//
// Created by tom on 16-12-20.
//

#ifndef MLT_FRAMEWDG_H
#define MLT_FRAMEWDG_H

#include <QOpenGLWidget>
#include <QImage>


class FrameWdg : public QOpenGLWidget {

Q_OBJECT

public:

FrameWdg(QWidget * parent = nullptr);

public slots:
    void showImage (const QImage & image);

protected:

void paintEvent(QPaintEvent * event) override;

    QImage _image;
};


#endif //MLT_FRAMEWDG_H
