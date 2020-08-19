import QtQuick 2.12
import QtQuick.Controls 2.12
import alijafari.musicorganizer 1.0


ScrollablePage {
    id: page

    Column {
        spacing: 40
        width: parent.width

        Row {
            spacing: 20

            Label {
                wrapMode: Label.Wrap
                text: qsTr("Album Name:")
            }
            TextField {
                id: albumNameField
                placeholderText: qsTr("album name")
                width: 300
            }
        }

        Row {
            spacing: 20

            Label {
                wrapMode: Label.Wrap
                text: qsTr("Track Name:")
            }
            TextField {
                id: nameField
                placeholderText: qsTr("track name")
                width: 300
            }
        }

        Row {
            spacing: 20

            Label {
                wrapMode: Label.Wrap
                text: qsTr("Musician:")
            }

            ComboBox {
                id: musicianCB
                editable: true
                model: addNewData.getAvailableMusician()
                width: 300
                onAccepted: {
                    if (find(editText) === -1)
                        ;//TODO show warning Dialog
                }
            }
        }

        Row {
            spacing: 20

            Label {
                wrapMode: Label.Wrap
                text: qsTr("Signer:")
            }

            ComboBox {
                id: signerCB
                editable: true
                model: addNewData.getAvailableSigner()
                width: 300
                onAccepted: {
                    if (find(editText) === -1)
                        ;
                }
            }
        }

        Row {
            spacing: 20

            Label {
                wrapMode: Label.Wrap
                text: qsTr("Dastgah:")
            }

            ComboBox {
                id: dastgahCB
                editable: true
                model: addNewData.getAvailableDastgah()
                width: 300
                onAccepted: {
                    if (find(editText) === -1)
                        ;
                }
            }
        }

        Row {
            spacing: 20

            Label {
                wrapMode: Label.Wrap
                text: qsTr("gusheh:")
            }

            ComboBox {
                id: gushehCB
                editable: true
                model: addNewData.getAvailableGusheh()
                width: 300
                onAccepted: {
                    if (find(editText) === -1)
                        ;
                }
            }
        }

        Row {
            spacing: 20

            Label {
                wrapMode: Label.Wrap
                text: qsTr("Instrument:")
            }

            ComboBox {
                id: musicalInstrumentCB
                editable: true
                model: addNewData.getAvailableMusicalInstrument()
                width: 300
                onAccepted: {
                    if (find(editText) === -1)
                        ;
                }
            }
        }

        Row {
            spacing: 20

            Label {
                wrapMode: Label.Wrap
                text: qsTr("Composer:")
            }

            ComboBox {
                id: composer
                editable: true
                model: addNewData.getAvailableComposer()
                width: 300
                onAccepted: {
                    if (find(editText) === -1)
                        ;
                }
            }
        }

        Row {
            spacing: 20

            Label {
                wrapMode: Label.Wrap
                text: qsTr("Lyrics:")
            }
            TextField {
                id: lyricsField
                placeholderText: qsTr("lyrics")
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
                    ListElement { text: qsTr("all") }
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

        Row{

            Button{
                text: qsTr("Search")
                onClicked: {
                    searchMusci.findMusicsInDatabase(albumNameField.text,
                                                     nameField.text,
                                                     musicianCB.currentText,
                                                     signerCB.currentText,
                                                     dastgahCB.currentText,
                                                     gushehCB.currentText,
                                                     musicalInstrumentCB.currentText,
                                                     composer.currentText,
                                                     lyricsField.text,
                                                     kind.currentText);
                }
            }
        }

    }
}
