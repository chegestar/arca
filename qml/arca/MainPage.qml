import QtQuick 1.1
import com.nokia.meego 1.0

Page {
    id: mainPage
    tools: commonTools

    property alias linkSheet: linkSheet

    LinkSheet {
        id: linkSheet
    }

    ListModel {
        id: metadataListModel
    }
}
