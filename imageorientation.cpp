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
}

extern "C" {

JNIEXPORT void JNICALL Java_com_example_myapplication_MainActivity_setNativeRotation
    (JNIEnv *, jobject, jint rotation, jlong ptr){

    QPointer<ImageOrientation> orientation = reinterpret_cast<ImageOrientation*>(ptr);

    auto setupTimer = [](QPointer<ImageOrientation> orientation,int rotation){
        QTimer *t = new QTimer(nullptr);
        t->setSingleShot(true);

        QObject::connect(t, &QTimer::timeout, [t, orientation, rotation](){
            if(!orientation.isNull()){
                orientation->setRotation(rotation);
                t->deleteLater();
            }
        });

        t->start(0);
    };
    QMetaObject::invokeMethod(orientation->thread(), [setupTimer, orientation, rotation]()  {
        setupTimer(orientation, rotation);
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


