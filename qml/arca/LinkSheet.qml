import QtQuick 1.0
import com.nokia.meego 1.0

Sheet {

    acceptButtonText: "Link"
    rejectButtonText: "Cancel"

    content: Flickable {
        anchors.fill: parent
        anchors.leftMargin: 10
        anchors.topMargin: 10
        contentWidth: col2.width
        contentHeight: col2.height
        flickableDirection: Flickable.VerticalFlick
        Column {
            id: col2
            anchors.top: parent.top
            spacing: 10
            Text {
                text: "Link to Dropbox"
            }
            Text {
                text: "Email"
            }
            TextField {
                id: email
            }
            Text {
                text: "Password"
            }
            TextField {
                id: password
                echoMode: TextInput.PasswordEchoOnEdit
            }
        }
    }

    onAccepted: restClient.login(email.text, password.text)
}
