#include "imageorientation.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QJniObject>
#include <QDebug>
#include <QObject>
#include <QQmlContext>

ImageOrientation::ImageOrientation(QObject *parent) : QObject{parent}
{
    QJniObject javaClass = QNativeInterface::QAndroidApplication::context();
    javaClass.callMethod<void>("setPointer","(J)V",(long long)(ImageOrientation*)this);
    setRotation(0);
}

extern "C" {

JNIEXPORT void JNICALL Java_com_example_myapplication_MainActivity_setNativeRotation
    (JNIEnv *, jobject, jint rotation, jlong ptr){

    ImageOrientation* orientation = reinterpret_cast<ImageOrientation*>(ptr);

    orientation->setRotation(rotation);
    qDebug() << rotation;
}

}

int ImageOrientation::rotation() const
{
    return m_rotation;
}

void ImageOrientation::setRotation(int newRotation)
{

    if (m_rotation == newRotation)
        return;
    m_rotation = newRotation;
    emit rotationChanged();
}


