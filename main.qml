import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Universal 2.12
import QtQuick.Layouts 1.12
import QtQuick.Dialogs 1.0

ApplicationWindow {
    id: window
    width: 1280
    height: 720
    visible: true
    title: qsTr("Music Organizer")


    function searchResult(azoonvar) {
//        console.log("azoonvar" + azoonvar)
            stackView.pop()
            return "some return value"
        }

    function showAbout(){
        aboutDialog.open()
    }

    Shortcut {
        sequence: "Ctrl+Q"
        onActivated: Qt.quit()
    }

    Shortcut {
        sequences: ["Esc", "Back"]
        enabled: stackView.depth > 1
        onActivated: navigateBackAction.trigger()
    }

    Action {
        id: navigateBackAction
        icon.name: stackView.depth > 1 ? "back" : "drawer"
        onTriggered: {
            if (stackView.depth > 1) {
                stackView.pop()
                listView.currentIndex = -1
            } else {
                drawer.open()
            }
        }
    }

    Shortcut {
        sequence: "Menu"
        onActivated: optionsMenuAction.trigger()
    }

    Action {
        id: optionsMenuAction
        icon.name: "menu"
        onTriggered: optionsMenu.open()
    }

    header: ToolBar {
        Material.foreground: "white"

        RowLayout {
            spacing: 20
            anchors.fill: parent

            ToolButton {
                action: navigateBackAction
            }

            Label {
                id: titleLabel
                text: listView.currentItem ? listView.currentItem.text : qsTr("Music Organizer")
                font.pixelSize: 20
                elide: Label.ElideRight
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                Layout.fillWidth: true
            }

            ToolButton {
                action: optionsMenuAction

                Menu {
                    id: optionsMenu
                    x: parent.width - width
                    transformOrigin: Menu.TopRight

                    Action {
                        text: qsTr("Import Json")
                        onTriggered: jsonPathDialog.open()
                    }
                    Action {
                        text: qsTr("About")
                        onTriggered: aboutDialog.open()
                    }
                }
            }
            FileDialog {
                id: jsonPathDialog
                title: qsTr("Please choose a Json file")
                folder: shortcuts.home
                selectMultiple: false
                selectFolder: false
                onAccepted: {
                    console.log("You chose: " + jsonPathDialog.fileUrls)
                    addNewData.importFromjson(jsonPathDialog.fileUrls)
                    searchMusci.responseToUi(true)
                }
                onRejected: {
                    console.log("Canceled")
                }
            }

            Dialog {
                id: aboutDialog

                x: 40
                y: 40
                width: resultView.width - 2*40
                contentHeight: resultView.height -3*40
                parent: Overlay.overlay

                modal: true
                title: qsTr("Music Organization")
                standardButtons: Dialog.Close

                background: Image {
                    fillMode: Image.PreserveAspectCrop
                    source: "file://Users/ali/Downloads/1111.jpg"
                }

                Flickable {
                    id: flickable2
                    clip: true
                    anchors.fill: parent
                    contentHeight: column.height

                    Column {
                        id: column2
                        spacing: 20
                        width: parent.width

//                        Image {
//                            id: logo
//                            width: 400
//                            anchors.horizontalCenter: parent.horizontalCenter
//                            fillMode: Image.PreserveAspectFit
//                            source: "file://Users/ali/Downloads/5306720.jpg"
//                        }

                        Label {
                            width: parent.width
                            text: "by this application you can find the right music you feel to listen in fastes way!\n\n"
                            + "Search base on lots of iranian traditional music parameter like Dastgah, Gusheh, kind, saaz, etc \n\n"
                            + "add your own musics and specify its parameter to search them later\n\n"
                            + "import some famouse web-site musics\n\n"
                            + "...\n\n\n\n"
                            + "با استفاده از این برنامه می‌توانید بر اساس احساساتی که در لحظه دارید موسیقی مناسب را در زمانی کم پیدا کنید\n\n "
                            + "جست‌و‌جو بر اساس مشخصه‌های مختلف موسیقی سنتی ایرانی  مانند دستگاه، گوشه، نوع، ساز و غیره\n\n"
                            + "امکان اضافه کردن موسیقی شخصی خود و مشخص کردن مشخصه های آن\n\n"
                            + "وارد کردن موسیقی های بعضی سایت های معروف\n\n"

                            wrapMode: Label.Wrap
                            horizontalAlignment: Qt.AlignHCenter
                            font.pixelSize: 20
                        }
                    }

                    ScrollIndicator.vertical: ScrollIndicator {
                        parent: contentDialog.contentItem
                        anchors.top: flickable.top
                        anchors.bottom: flickable.bottom
                        anchors.right: parent.right
                        anchors.rightMargin: -contentDialog.rightPadding + 1
                    }
                }
            }
        }
    }

    Drawer {
        id: drawer
        width: Math.min(window.width, window.height) / 3
        height: window.height
        interactive: stackView.depth === 1

        ListView {
            id: listView
            focus: true
            currentIndex: -1
            anchors.fill: parent

            delegate: ItemDelegate {
                width: parent.width
                text: model.title
                icon.name: model.iconName
                highlighted: ListView.isCurrentItem
                onClicked: {
                    listView.currentIndex = index
                    stackView.push(model.source)
                    drawer.close()
                }
            }

            model: ListModel {
                ListElement { title: qsTr("Search"); source: "qrc:/pages/SearchPage.qml"; iconName: "search"}
                ListElement { title: qsTr("Add New"); source: "qrc:/pages/AddPage.qml"; iconName: "add" }
            }

            ScrollIndicator.vertical: ScrollIndicator { }
        }
    }

    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: Pane {
            id: pane
            background: Image {
                id: b
                fillMode: Image.PreserveAspectCrop
                source: /*"qrc:/images/applicationwindow-background.jpg"*/"file://Users/ali/Downloads/22.jpg"
            }

            ListView {
                id: resultView
                width: window.width - 20; height: window.height - 100
                spacing: 10
                model: resultModel

                delegate: GroupBox {
//                    ColumnLayout{
                        Row{
                            spacing: 20
                            Image {
                                id: trackpic
                                source: model.a_pic
                                width: 100
                                height: 100
                                fillMode: Image.PreserveAspectFit
                            }
                            Row{
                                id: row
                                property var maxWidth : 250
                                spacing:40
                                Column{


                                    spacing: 10

                                    Row{
                                        spacing: 30
                                        Label{ text: model.t_name }
                                        Label{ text: model.t_time }
                                    }

                                        Label { text: qsTr("Signer: ") + model.T_Khanandeh; width: row.maxWidth;wrapMode: Label.WordWrap}
                                        Label { text: qsTr("Musician: ") + model.T_Navazandeh; width: row.maxWidth;wrapMode: Label.WordWrap}
                                        Label { text: qsTr("Composer: ") + model.T_Ahangsaz; width: row.maxWidth;wrapMode: Label.WordWrap}
                                }
                                Column{
                                    spacing: 10

                                    Label{ text: qsTr("Kind: ") + model.t_kind; width: row.maxWidth;wrapMode: Label.WordWrap}
                                    Label { text: qsTr("Dastgah: ") + model.T_Dastgah; width: row.maxWidth;wrapMode: Label.WordWrap }
                                    Label { text: qsTr("Gusheh: ") + model.T_Gusheh; width: row.maxWidth;wrapMode: Label.WordWrap}
                                    Label { text: qsTr("Saaz: ") + model.T_Saaz; width: row.maxWidth;wrapMode: Label.WordWrap }

                                }
                                Column{
                                    spacing: 5
                                    Label{ text: qsTr("Album: ") + model.a_name}
                                    Label{ text: qsTr("Year: ") + model.a_year}
                                    Button{
                                        text: qsTr("Lyrics")
                                        height: 30
                                        onClicked: contentDialog.open()

                                        Dialog {
                                            id: contentDialog

                                            x: 40
                                            y: 40
                                            width: resultView.width - 2*40
                                            contentHeight: resultView.height -3*40
                                            parent: Overlay.overlay

                                            modal: true
                                            title: qsTr("Lyrics")
                                            standardButtons: Dialog.Close

                                            Flickable {
                                                id: flickable
                                                clip: true
                                                anchors.fill: parent
                                                contentHeight: column.height

                                                Column {
                                                    id: column
                                                    spacing: 20
                                                    width: parent.width

                                                    Image {
                                                        id: logo
                                                        width: 200
                                                        anchors.horizontalCenter: parent.horizontalCenter
                                                        fillMode: Image.PreserveAspectFit
                                                        source: model.a_pic
                                                    }

                                                    Label {
                                                        width: parent.width
                                                        text: model.a_lyrics
                                                        wrapMode: Label.Wrap
                                                    }
                                                }

                                                ScrollIndicator.vertical: ScrollIndicator {
                                                    parent: contentDialog.contentItem
                                                    anchors.top: flickable.top
                                                    anchors.bottom: flickable.bottom
                                                    anchors.right: parent.right
                                                    anchors.rightMargin: -contentDialog.rightPadding + 1
                                                }
                                            }
                                        }
                                    }
                                    Button{
                                        text: qsTr("play")
                                        height: 30
                                        onClicked: searchMusci.playExternal(model.t_path)
                                    }

                                }
                            }

//                        }


                    }
                }
        }

//            Label {
//                text: "by this application you can find the right music you feel to listen in fastes way!"
//                anchors.margins: 20
//                anchors.top: logo.bottom
//                anchors.left: parent.left
//                anchors.right: parent.right
//                anchors.bottom: arrow.top
//                horizontalAlignment: Label.AlignHCenter
//                verticalAlignment: Label.AlignVCenter
//                wrapMode: Label.Wrap
//            }

//            Image {
//                id: arrow
//                source: "images/arrow.png"
//                anchors.left: parent.left
//                anchors.bottom: parent.bottom
//            }
        }
    }
}
