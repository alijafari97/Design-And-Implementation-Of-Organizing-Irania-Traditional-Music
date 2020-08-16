import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.3
import QtQuick.Layouts 1.12
import alijafari.musicorganizer 1.0
import QtQuick.Controls.Material 2.12

ScrollablePage {
    id: page
//    ColumnLayout{
//        layoutDirection: Qt.RightToLeft

    Column {
        spacing: 10
        width: parent.width

        Label {
            width: parent.width
            wrapMode: Label.Wrap
            horizontalAlignment: Qt.AlignHCenter
            text: qsTr("Album:")
        }

        Row {
            spacing: 20

            Label {
                wrapMode: Label.Wrap
                text: qsTr("Name:")
            }
            TextField {
                id: nameField
                placeholderText: qsTr("name")
                width: 300
            }
        }

        Row {
            spacing: 20

            Label {
                wrapMode: Label.Wrap
                text: qsTr("Year:")
            }
            TextField {
                id: yearField
                placeholderText: qsTr("year")
                width: 300
            }
        }

        Row{
            spacing: 20

            Button{
                text: qsTr("file Path")
                onClicked: {folderPathDialog.open()}
            }

            FileDialog {
                id: folderPathDialog
                title: qsTr("Please choose a folder")
                folder: shortcuts.home
                selectFolder: true
                onAccepted: {
                    console.log("You chose: " + folderPathDialog.fileUrls)
                    folderPathLabel.text = fileUrl
                }
                onRejected: {
                    console.log("Canceled")
                }
            }

            Label {
                id: folderPathLabel
                wrapMode: Label.Wrap
                text: ""
            }

        }

        Row{
            spacing: 20

            Button{
                text: qsTr("Pic Path")
                onClicked: {picPathDialog.open()}
            }

            FileDialog {
                id: picPathDialog
                title: qsTr("Please choose a pic")
                folder: shortcuts.home
                selectMultiple: false
                selectFolder: false
                nameFilters: [ "image files (*.jpg *.png *.jpeg)"]
                onAccepted: {
                    console.log("You chose: " + picPathDialog.fileUrls)
                    picPathLabel.text = picPathDialog.fileUrl
                    albumPic.source = picPathDialog.fileUrl

                }
                onRejected: {
                    console.log("Canceled")
                }
            }

            Label {
                id: picPathLabel
                wrapMode: Label.Wrap
                text: ""
            }

            Image {
                id: albumPic
                width: 100
                height: 100
                fillMode: Image.PreserveAspectFit
            }

        }

        Row {
            spacing: 20

            Label {
                wrapMode: Label.Wrap
                text: qsTr("Total Time:")
            }
            TextField {
                id: totalTimeField
                placeholderText: qsTr("total time")
                width: 300
            }
        }

        Row {
            spacing: 20
            Label {
                wrapMode: Label.Wrap
                text: qsTr("Lyrics")
            }

            TextArea {
                id: lyricsField
                wrapMode: TextArea.Wrap
                width: 400
            }
        }

        Row {
            spacing: 20
            Label {
                wrapMode: Label.Wrap
                text: qsTr("Comment")
            }

            TextArea {
                id: commentField
                wrapMode: TextArea.Wrap
                width: 400
            }
        }

        Row {
            spacing: 20

            Label {
                wrapMode: Label.Wrap
                text: qsTr("Number Of Tracks")
            }

            SpinBox {
                id: numOfTrackBox
                value:5
                editable: true
            }

            Button{
                text: qsTr("make tracks")
                //TODO handle if push more than once or when it was smaller value
                onClicked: {for (var i = 0; i < numOfTrackBox.value; i++) {tracksModel.append({"index": i})}}
            }


        }

        ListModel {
             id: tracksModel
        }

        Label {
            width: parent.width
            wrapMode: Label.Wrap
            horizontalAlignment: Qt.AlignHCenter
            text: qsTr("Tracks:")
        }

        ListView {
            id: tracksView
            model: tracksModel
            spacing: 10
            interactive: false

            delegate :TrackForm {
                trackNumber: model.index + 1
                objectName: "trackform"

            }

            onCountChanged: {
//                var root = tracksView.children[0]
                var listViewHeight = 0
                var listViewWidth = 0

                for(var child in contentItem.children) {
                    console.log(contentItem.children[child].height)
                    listViewHeight += contentItem.children[child].height
                    listViewWidth  = Math.max(listViewWidth, contentItem.children[child].width)
                }

//                for (var i = 0; i < root.children.length; i++) {
//                    listViewHeight += root.children[i].height
//                    listViewWidth  = Math.max(listViewWidth, root.children[i].width)
//                }

                tracksView.height = (contentItem.children[child].height + spacing) * count
                tracksView.width = listViewWidth
            }


        }

        Row{

            Button{
                text: qsTr("Save")
                onClicked: {
                    var result = addNewData.insertNewAlbum(nameField.text,
                                                           yearField.text,
                                                           folderPathLabel.text,
                                                           picPathLabel.text,
                                                           totalTimeField.text,
                                                           lyricsField.text,
                                                           commentField.text,
                                                           numOfTrackBox.value);

                    console.log("QML:insertNewAlbum: ",result);
                    if (result === "failed"){
                        errorDialogLabel.text = qsTr("Something Wrong!!!");
                        errorDialog.open();
                        return;
                    }

                    for(var child in tracksView.contentItem.children) {
                        if (tracksView.contentItem.children[child].objectName === "trackform"){
                            var chItem = tracksView.contentItem.children[child];
                            addNewData.insertNewTrack(result,
                                                      chItem.trackNumber,
                                                      chItem.nameField.text,
                                                      chItem.trackPathLabel.text,
                                                      chItem.timeField.text,
                                                      chItem.kind.text,
                                                      chItem.musicianField.text,
                                                      chItem.singerField.text,
                                                      chItem.dastgahField.text,
                                                      chItem.gushehField.text,
                                                      chItem.musicalInstrumentField.text,
                                                      chItem.composerField.text);
                        }
                    }
                }
                Dialog {
                    id: errorDialog

                    title: "Error"

                    Label {
                        id: errorDialogLabel
                        text: ""
                    }
                }
            }
        }


//    }

    }
}
