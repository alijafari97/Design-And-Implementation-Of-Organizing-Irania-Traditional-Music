#include "addnewdata.h"

AddNewData::AddNewData(QObject *parent) : QObject(parent)
{
    initAvailables();

}

QString AddNewData::insertNewAlbum(const QString &name,
                                   const int &year,
                                   const QString &folderPath,
                                   const QString &picPath,
                                   const QString &totalTime,
                                   const QString &lyrics,
                                   const QString &comment,
                                   const int &numOfTracks)
{
    qDebug() << "inserting into Album: " << name << year << folderPath << picPath << totalTime << lyrics << comment << numOfTracks;
    if (!q.prepare(QLatin1String("insert into Album(a_name, a_lyrics, a_year, a_pic, a_comment, a_path, a_total_time, a_num_of_track, a_is_favorite) values(?, ?, ?, ?, ?, ?, ?, ?, ?)"))) {
        qDebug() << q.lastError();
        return "failed";
    }

    q.addBindValue(name);
    q.addBindValue(lyrics);
    q.addBindValue(year);//TODO dorostesh konam
    q.addBindValue(picPath);
    q.addBindValue(comment);
    q.addBindValue(folderPath);
    q.addBindValue(totalTime);
    q.addBindValue(numOfTracks);
    q.addBindValue(false);//favorite
    q.exec();

    return q.lastInsertId().toString();
}

QString AddNewData::insertNewTrack(const QString &albumId,
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
                                   const QString &composer)
{
    qDebug() << "inserting into Tracks: " << albumId << trackNumber << name << filePath << time << kind << musician << signer << dastgah << gushe << musicalInstrument << composer;
    if (!q.prepare(QLatin1String("insert into Track(a_id, t_track_number, t_name, t_path, t_time, t_kind, t_is_favorite) values(?, ?, ?, ?, ?, ?, ?)"))) {
        qDebug() << q.lastError();
        return "failed";
    }
    q.addBindValue(albumId);
    q.addBindValue(trackNumber);
    q.addBindValue(name);
    q.addBindValue(filePath);
    q.addBindValue(time);
    q.addBindValue(kind);
    q.addBindValue(false);
    q.exec();
    QVariant trackId = q.lastInsertId();

    QStringList musicianList = musician.split(",");
    for (int i = 0; i < musicianList.size(); i++){
        musicianList.replace(i, musicianList.at(i).trimmed());
    }
    if(!q.prepare(QLatin1String("insert into T_Navazandeh(tn_name, t_id) values(?, ?)"))){
        qDebug() << q.lastError();
        return "failed";
    }
    foreach (QString s, musicianList) {
        q.addBindValue(s);
        q.addBindValue(trackId);
        q.exec();
    }

    QStringList signerList = signer.split(",");
    for (int i = 0; i < signerList.size(); i++){
        signerList.replace(i, signerList.at(i).trimmed());
    }
    if(!q.prepare(QLatin1String("insert into T_Khanandeh(tk_name, t_id) values(?, ?)"))){
        qDebug() << q.lastError();
        return "failed";
    }
    foreach (QString s, signerList) {
        q.addBindValue(s);
        q.addBindValue(trackId);
        q.exec();
    }

    QStringList dastgahList = dastgah.split(",");
    for (int i = 0; i < dastgahList.size(); i++){
        dastgahList.replace(i, dastgahList.at(i).trimmed());
    }
    if(!q.prepare(QLatin1String("insert into T_Dastgah(td_name, t_id) values(?, ?)"))){
        qDebug() << q.lastError();
        return "failed";
    }
    foreach (QString s, dastgahList) {
        q.addBindValue(s);
        q.addBindValue(trackId);
        q.exec();
    }

    QStringList gushehList = gushe.split(",");
    for (int i = 0; i < gushehList.size(); i++){
        gushehList.replace(i, gushehList.at(i).trimmed());
    }
    if(!q.prepare(QLatin1String("insert into T_Gusheh(tg_name, t_id) values(?, ?)"))){
        qDebug() << q.lastError();
        return "failed";
    }
    foreach (QString s, gushehList) {
        q.addBindValue(s);
        q.addBindValue(trackId);
        q.exec();
    }

    QStringList musicalInstrumentList = musicalInstrument.split(",");
    for (int i = 0; i < musicalInstrumentList.size(); i++){
        musicalInstrumentList.replace(i, musicalInstrumentList.at(i).trimmed());
    }
    if(!q.prepare(QLatin1String("insert into T_Saaz(ts_name, t_id) values(?, ?)"))){
        qDebug() << q.lastError();
        return "failed";
    }
    foreach (QString s, musicalInstrumentList) {
        q.addBindValue(s);
        q.addBindValue(trackId);
        q.exec();
    }

    QStringList composerList = composer.split(",");
    for (int i = 0; i < composerList.size(); i++){
        composerList.replace(i, composerList.at(i).trimmed());
    }
    if(!q.prepare(QLatin1String("insert into T_Ahangsaz(ta_name, t_id) values(?, ?)"))){
        qDebug() << q.lastError();
        return "failed";
    }
    foreach (QString s, composerList) {
        q.addBindValue(s);
        q.addBindValue(trackId);
        q.exec();
    }

    reInitAvailables();

    return "success";

}

QVariant AddNewData::getAvailableMusician()
{
    return QVariant::fromValue(availableMusician);
}

QVariant AddNewData::getAvailableSigner()
{
    return QVariant::fromValue(availableSigner);
}

QVariant AddNewData::getAvailableDastgah()
{
    return QVariant::fromValue(availableDastgah);
}

QVariant AddNewData::getAvailableGusheh()
{
    return QVariant::fromValue(availableGusheh);
}

QVariant AddNewData::getAvailableMusicalInstrument()
{
    return QVariant::fromValue(availableMusicalInstrument);
}

QVariant AddNewData::getAvailableComposer()
{
    return QVariant::fromValue(availableComposer);
}

void AddNewData::selectAvailableMusician()
{
    availableMusician.append(tr("all"));
     QSqlQuery query("select distinct(tn_name) from T_Navazandeh");
     while (query.next()) {
         if (query.value(0).toString() != "")
              availableMusician.append(query.value(0).toString());
     }
}

void AddNewData::selectAvailableSigner()
{
    availableSigner.append(tr("all"));
    QSqlQuery query("select distinct(tk_name) from T_Khanandeh");
    while (query.next()) {
        if (query.value(0).toString() != "")
             availableSigner.append(query.value(0).toString());
    }
}

void AddNewData::selectAvailableDastgah()
{
    availableDastgah.append(tr("all"));
    QSqlQuery query("select distinct(td_name) from T_Dastgah");
    while (query.next()) {
        if (query.value(0).toString() != "")
             availableDastgah.append(query.value(0).toString());
    }
}

void AddNewData::selectAvailableGusheh()
{
    availableGusheh.append(tr("all"));
    QSqlQuery query("select distinct(tg_name) from T_Gusheh");
    while (query.next()) {
        if (query.value(0).toString() != "")
             availableGusheh.append(query.value(0).toString());
    }
}

void AddNewData::selectAvailableMusicalInstrument()
{
    availableMusicalInstrument.append(tr("all"));
    QSqlQuery query("select distinct(ts_name) from T_Saaz");
    while (query.next()) {
        if (query.value(0).toString() != "")
             availableMusicalInstrument.append(query.value(0).toString());
    }
}

void AddNewData::selectAvailableComposer()
{
    availableComposer.append(tr("all"));
    QSqlQuery query("select distinct(ta_name) from T_Ahangsaz");
    while (query.next()) {
        if (query.value(0).toString() != "")
             availableComposer.append(query.value(0).toString());
    }
}

void AddNewData::initAvailables()
{
    selectAvailableGusheh();
    selectAvailableSigner();
    selectAvailableDastgah();
    selectAvailableComposer();
    selectAvailableMusician();
    selectAvailableMusicalInstrument();
}

void AddNewData::reInitAvailables()
{
    availableGusheh.clear();
    availableSigner.clear();
    availableDastgah.clear();
    availableComposer.clear();
    availableMusician.clear();
    availableMusicalInstrument.clear();
    initAvailables();
}
