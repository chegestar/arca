import QtQuick 1.0
import com.nokia.meego 1.0
import QtWebKit 1.0

Page {
    property string path

    tools: tabTools

    WebView {
        anchors.fill: parent
    }

    ToolBarLayout {
        id: tabTools

        ToolIcon {
            iconId: "toolbar-back";
            anchors.left: parent.left
            onClicked: {
                pageStack.pop();
            }
        }

        ToolIcon {
            platformIconId: "toolbar-view-menu"
            anchors.right: parent===undefined ? undefined : parent.right
            onClicked: (myMenu.status == DialogStatus.Closed) ? myMenu.open() : myMenu.close()
        }
    }
}

