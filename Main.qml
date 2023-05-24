import QtQuick
import QtQuick.Window
import ImageOrientationpackage

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Image Rotation")

    ImageOrientation {
        id: imgOrientation
    }

    Rectangle {
        width: parent.width
        color: "grey"
        height: 40
        Text {
            text: "Image Rotation"
            font.pointSize: 32
            color: "white"
        }
    }

    Image {
        id: image
        source: "qrc:/images/exampleimg.png"
        width:  200
        height: 200
        anchors.centerIn: parent
        rotation: imgOrientation.rotation
    }

    Connections {
        target: imgOrientation
        onRotationChanged: imgOrientation.setRotation(newRotation);

    }

}
