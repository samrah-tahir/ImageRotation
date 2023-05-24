#include "imageorientation.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QJniObject>
#include <QDebug>
#include <QObject>
#include <QTimer>

ImageOrientation::ImageOrientation(QObject *parent) : QObject{parent}
{
    QJniObject javaClass = QNativeInterface::QAndroidApplication::context();
    javaClass.callMethod<void>("setPointer","(J)V",(long long)(ImageOrientation*)this);

    setRotation(0);
    qDebug() << "constructor"<<QThread::currentThreadId();
}

extern "C" {

JNIEXPORT void JNICALL Java_com_example_myapplication_MainActivity_setNativeRotation
    (JNIEnv *, jobject, jint rotation, jlong ptr){

    QPointer<ImageOrientation> orientation = reinterpret_cast<ImageOrientation*>(ptr);

    qDebug() << QThread::currentThreadId() << "before invoke";
    QMetaObject::invokeMethod(orientation->thread(), [orientation, rotation]()  {
        orientation->setRotation(rotation);
        qDebug() << QThread::currentThreadId();
    });

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
    emit rotationChanged(newRotation);
}


