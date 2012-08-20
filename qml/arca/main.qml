import QtQuick 1.1
import com.nokia.meego 1.0

PageStackWindow {
    id: appWindow

    initialPage: mainPage

    Component.onCompleted: {
        console.log("main onCompleted")
        restClient.openNetworkSession()
    }

    MainPage {
        id: mainPage
    }

    ToolBarLayout {
        id: commonTools
        visible: true
        ToolIcon {
            platformIconId: "toolbar-view-menu"
            anchors.right: (parent === undefined) ? undefined : parent.right
            onClicked: (myMenu.status === DialogStatus.Closed) ? myMenu.open() : myMenu.close()
        }
    }

    Menu {
        id: myMenu
        visualParent: pageStack
        MenuLayout {
            MenuItem { text: qsTr("Sample menu item") }
            MenuItem {
                text: "Open link sheet"
                onClicked: linkSheet.open()
            }
        }
    }

    QueryDialog {
        id: errorDialog
        acceptButtonText: "OK"
        message: "An error has occured."
        titleText: "Error"
    }

    QueryDialog {
        id: welcomeDialog
        acceptButtonText: "OK"
        message: "Welcome: " + param
        titleText: "Arca"
    }

    Connections {
        target: restClient

        onOnline: {
            if (restClient.hasCredentials) {
                console.log("loading metadata")
                mainPage.state = "loading"
                restClient.loadMetadata("/")
            } else {
                console.log("need to log in")
                //mainPage.state = "logging in"
                //mainPage.linkSheet.open()
                welcomeDialog.open()
                restClient.requestToken()
            }
        }

        onAuthorized: {
            mainPage.state = "loading"
            restClient.loadMetadata("/")
        }

        onLoadedFile: {
            console.log("Loaded File")
            console.log(fileData)
            restClient.showFile()
        }

        onLoadedMetadata: {
            pageStack.currentPage.state = "online"

            var responseObj = eval('(' + metadata + ')');
            var metadataObj = responseObj.body;

            if (metadataObj.is_dir === true)
                for (var index in metadataObj.contents) {
                    pageStack.currentPage.listModel.append(metadataObj.contents[index]);
                    console.log(metadataObj.contents[index].icon);
                }
        }

        onNeedAuthorization: {
            mainPage.state = "logging in"
            mainPage.linkSheet.open()
        }

        onError: {
            console.log(networkReply)
            errorDialog.open()
        }
    }
}
