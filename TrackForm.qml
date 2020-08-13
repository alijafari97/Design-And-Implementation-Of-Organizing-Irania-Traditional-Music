import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.12

GroupBox{

    property var trackNumber: 0
    property  alias kind: kind

ColumnLayout{
    spacing: 30

    Label {
        width: parent.width
        wrapMode: Label.Wrap
        horizontalAlignment: Qt.AlignHCenter
        text: qsTr("Track") + " " +  trackNumber
    }

    Row {
        spacing: 20

        Label {
            wrapMode: Label.Wrap
            text: qsTr("Name:")
        }
        TextField {
            id: nameField
            placeholderText: "name"
            width: 300
        }
    }

    Row{
        spacing: 20

        Button{
            text: qsTr("file Path")
            onClicked: {trackPathDialog.open()}
        }

        FileDialog {
            id: trackPathDialog
            title: qsTr("Please choose a file")
            folder: shortcuts.home
            selectFolder: false
            selectMultiple: false
            onAccepted: {
                console.log("You chose: " + trackPathDialog.fileUrls)
                trackPathLabel.text = fileUrl
            }
            onRejected: {
                console.log("Canceled")
            }
        }

        Label {
            id: trackPathLabel
            wrapMode: Label.Wrap
            text: ""
        }

    }

    Row {
        spacing: 20

        Label {
            wrapMode: Label.Wrap
            text: qsTr("Time:")
        }
        TextField {
            id: timeField
            placeholderText: qsTr("time")
            width: 300
        }
    }

    Row {
        spacing: 20

        Label {
            wrapMode: Label.Wrap
            text: qsTr("Kind:")
        }

        ComboBox {
            id: kind
            editable: true
            model: ListModel {
                id: kindModel
                ListElement { text: qsTr("Avaz") }
                ListElement { text: qsTr("Saz Va Avaz") }
                ListElement { text: qsTr("Saz") }
                ListElement { text: qsTr("Chahar Mezrab") }
                ListElement { text: qsTr("Tasnif") }
                ListElement { text: qsTr("Reng") }
                ListElement { text: qsTr("Zarbi") }
            }
            onAccepted: {
                if (find(editText) === -1)
                    kindModel.append({text: editText})
            }

        }
    }

    Row {
        spacing: 20

        Label {
            wrapMode: Label.Wrap
            text: qsTr("Musician:")
        }
        TextField {
            id: musicianField
            placeholderText: qsTr("seprate with \',\'")
            width: 300
        }
    }

    Row {
        spacing: 20

        Label {
            wrapMode: Label.Wrap
            text: qsTr("Singer:")
        }
        TextField {
            id: singerField
            placeholderText: qsTr("seprate with \',\'")
            width: 300
        }
    }

    Row {
        spacing: 20

        Label {
            wrapMode: Label.Wrap
            text: qsTr("Dastgah:")
        }
        TextField {
            id: dastgahField
            placeholderText: qsTr("seprate with \',\'")
            width: 300
        }
    }

    Row {
        spacing: 20

        Label {
            wrapMode: Label.Wrap
            text: qsTr("Gusheh:")
        }
        TextField {
            id: gushehField
            placeholderText: qsTr("seprate with \',\'")
            width: 300
        }
    }

    Row {
        spacing: 20

        Label {
            wrapMode: Label.Wrap
            text: qsTr("Musical Instrument:")
        }
        TextField {
            id: musicalInstrumentField
            placeholderText: qsTr("seprate with \',\'")
            width: 300
        }
    }

    Row {
        spacing: 20

        Label {
            wrapMode: Label.Wrap
            text: qsTr("Composer:")
        }
        TextField {
            id: composerField
            placeholderText: qsTr("seprate with \',\'")
            width: 300
        }
    }


}

}
