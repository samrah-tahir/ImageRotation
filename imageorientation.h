#ifndef IMAGEORIENTATION_H
#define IMAGEORIENTATION_H

#include <QObject>

class ImageOrientation:public QObject
{
    Q_OBJECT

    Q_PROPERTY(int rotation READ rotation WRITE setRotation NOTIFY rotationChanged)

public:
    explicit ImageOrientation(QObject* parent = nullptr);

    int rotation() const;
    void setRotation(int newRotation);

signals:
    void rotationChanged();

private:
    int m_rotation;

};

#endif // IMAGEORIENTATION_H
