#ifndef ADDNEWDATA_H
#define ADDNEWDATA_H

#include <QObject>
#include <QDebug>
#include <QtSql>

class AddNewData : public QObject
{
    Q_OBJECT
public:
    AddNewData(QObject *parent = nullptr);

    Q_INVOKABLE QString insertNewAlbum(const QString &name,
                                       const QString &year,
                                       const QString &folderPath,
                                       const QString &picPath,
                                       const QString &totalTime,
                                       const QString &lyrics,
                                       const QString &comment,
                                       const int &numOfTracks);

    Q_INVOKABLE QString insertNewTrack(const QString &albumId,
                                       const int &trackNumber,
                                       const QString &name,
                                       const QString &filePath,
                                       const QString &time,
                                       const QString &kind,
                                       const QString &musician,
                                       const QString &signer,
                                       const QString &dastgah,
                                       const QString &gushe,
                                       const QString &musicalInstrument,
                                       const QString &composer);
    Q_INVOKABLE QVariant getAvailableMusician();
    Q_INVOKABLE QVariant getAvailableSigner();
    Q_INVOKABLE QVariant getAvailableDastgah();
    Q_INVOKABLE QVariant getAvailableGusheh();
    Q_INVOKABLE QVariant getAvailableMusicalInstrument();
    Q_INVOKABLE QVariant getAvailableComposer();

    void selectAvailableMusician();
    void selectAvailableSigner();
    void selectAvailableDastgah();
    void selectAvailableGusheh();
    void selectAvailableMusicalInstrument();
    void selectAvailableComposer();
    void initAvailables();
    void reInitAvailables();

signals:

private:
    QSqlQuery q;
    QStringList availableMusician;
    QStringList availableSigner;
    QStringList availableDastgah;
    QStringList availableGusheh;
    QStringList availableMusicalInstrument;
    QStringList availableComposer;

};



#endif // ADDNEWDATA_H
