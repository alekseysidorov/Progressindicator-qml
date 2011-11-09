import QtQuick 1.1
import QtDesktop 0.1

Item {
    width: 360
    height: 360
    Column {
        anchors.fill: parent
        anchors.margins: 10
        spacing: 10

        ProgressIndicator {
            id: indicator

            width: 200
            height: 200
            playing: true
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Button {
            id: clickMe
            anchors.horizontalCenter: parent.horizontalCenter
            text: qsTr("Click me")
            onClicked: Qt.quit();
        }
    }
}
