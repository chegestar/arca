import QtQuick 1.0
import com.nokia.meego 1.0
import "util.js" as Util

Page {

    property string metadataPath
    property alias listModel: metadataListModel

    ListModel {
        id: metadataListModel
    }

    Rectangle {
        id: header
        x: 0; y: 0
        width: parent.width; height: 72
        color: metadataPath ? "white" : "blue"
        Label {
            x: 16; y: 20
            text: metadataPath ? metadataPath : 'Dropbox'
            font.pixelSize: 32
            color: metadataPath ? "black" : "white"
        }
    }

    Item {
        id: offline
        visible: true
        anchors.top: header.bottom
        width: parent.width
        height: parent.height - header.height
        Label {
            anchors.centerIn: parent
            width: parent.width
            text: 'Not connected to Dropbox'
            font.pixelSize: 64
            horizontalAlignment: Text.AlignHCenter
            wrapMode: Text.Wrap
            color: "lightgray"
        }
    }

    Item {
        id: busyItem
        visible: false
        anchors.top: header.bottom
        width: parent.width
        height: parent.height - header.height
        BusyIndicator {
            id: busyIndicator
            anchors.centerIn: parent
            platformStyle: BusyIndicatorStyle { size: "large" }
            running: true
        }
        Label {
            id: busyLabel
            anchors.top: busyIndicator.bottom
            anchors.topMargin: 16
            width: parent.width
            font.pixelSize: 32
            horizontalAlignment: Text.AlignHCenter
            color: "gray"
        }
    }

    ListView {
        id: listView
        visible: false
        anchors.top: header.bottom
        width:  parent.width
        height: parent.height - header.height
        model: metadataListModel
        delegate: Item {
            id: wrapper; width: parent.width; height: 80
            Row {
                Image {
                    source: Util.iconSource(icon)
                }
                Column {
                    x: 16; y: 24
                    Text {
                        text: Util.fileNameFromPath(path)
                        font.pixelSize: 24
                    }
                    Text {
                        text: Util.readableSize(bytes) + ", " + modified
                        visible: !is_dir
                        font.pixelSize: 16
                        color: "gray"
                    }
                }
            }
            MouseArea {
                id: mouseArea
                anchors.fill: parent
                onClicked: {
                    if (is_dir) {
                        openDirPage("SubDirPage.qml", path)
                    } else {
                        openFilePage("FilePage.qml", path)
                    }
                }
            }
        }
//        highlight: highlight
        clip: true
    }

    ScrollDecorator {
         id: scrolldecorator
         flickableItem: listView
    }

    states: [
        State {
            name: "logging in"
            PropertyChanges { target: offline; visible: false }
            PropertyChanges { target: busyItem; visible: true }
            PropertyChanges { target: busyLabel; text: "Logging In" }
            PropertyChanges { target: listView; visible: false }
        },
        State {
            name: "loading"
            PropertyChanges { target: offline; visible: false }
            PropertyChanges { target: busyItem; visible: true }
            PropertyChanges { target: busyLabel; text: "Loading" }
            PropertyChanges { target: listView; visible: false }
        },
        State {
            name: "online"
            PropertyChanges { target: offline; visible: false }
            PropertyChanges { target: busyItem; visible: false }
            PropertyChanges { target: listView; visible: true }
        }
    ]

    function openDirPage(file, metadataPath) {
        var component = Qt.createComponent(file)
        if (component.status == Component.Ready) {
            var page = pageStack.push(component, {"metadataPath": metadataPath});
            page.state = "loading"
            restClient.loadMetadata(metadataPath);
        } else {
            console.log("Error loading component:", component.errorString());
        }
    }

    function openFilePage(file, path) {
        var component = Qt.createComponent(file)
        if (component.status == Component.Ready) {
            var page = pageStack.push(component, {"path": path});
//            page.state = "loading"
            restClient.loadFile(path);
        } else {
            console.log("Error loading component:", component.errorString());
        }
    }
}
