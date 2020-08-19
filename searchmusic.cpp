#include "searchmusic.h"
#include <QDebug>
#include <QString>
#include <QMetaObject>
#include <QQmlContext>

SearchMusic::SearchMusic(QObject *parent) : QObject(parent)
{

}

SearchMusic::SearchMusic(QQmlEngine *engine, QObject *parent) : QObject(parent)
{
    _engine = engine;
}

SearchMusic::SearchMusic(QObject *mainqml, QQmlEngine *engine, QObject *parent) : QObject(parent)
{
    _mainQml = mainqml;
    _engine = engine;
}

void SearchMusic::findMusicsInDatabase(const QString &albumName,
                                       const QString &trackName,
                                       const QString &musician,
                                       const QString &signer,
                                       const QString &dastgah,
                                       const QString &gusheh,
                                       const QString &instrument,
                                       const QString &composer,
                                       const QString &Lyrics,
                                       const QString &kind)
{
    QSqlQuery query;
    QList<int> tempList;
    bool isFirstTime = true;

    if (albumName != ""){
        query = QSqlQuery("select a_id from Album where a_name like \"\%" + albumName + "\%\"");
        QList<int> AlbumId;
        while (query.next()) {
            AlbumId.append(query.value(0).toInt());
        }
        for (int i = 0; i < AlbumId.length(); i++){
            QSqlQuery tempQuery("select t_id from Track where a_id = " + QString::number(AlbumId.at(i)));
            while (tempQuery.next()) {
                if (isFirstTime || trackIdResult.contains(tempQuery.value(0).toInt()))
                    tempList.append(tempQuery.value(0).toInt());
            }
        }
        isFirstTime = false;
        trackIdResult.clear();
        trackIdResult = tempList;
        tempList.clear();
    }

    if (Lyrics != ""){
        query = QSqlQuery("select a_id from Album where a_lyrics like \"\%" + Lyrics + "\%\"");
        QList<int> AlbumId;
        while (query.next()) {
            AlbumId.append(query.value(0).toInt());
        }
        for (int i = 0; i < AlbumId.length(); i++){
            QSqlQuery tempQuery("select t_id from Track where a_id = " + QString::number(AlbumId.at(i)));
            while (tempQuery.next()) {
                if (isFirstTime || trackIdResult.contains(tempQuery.value(0).toInt()))
                    tempList.append(tempQuery.value(0).toInt());
            }
        }
        isFirstTime = false;
        trackIdResult.clear();
        trackIdResult = tempList;
        tempList.clear();
    }

    if (trackName != ""){
        query = QSqlQuery("select distinct(t_id) from Track where t_name like \"\%" + trackName + "\%\"");
        while (query.next()) {
            if (isFirstTime || trackIdResult.contains(query.value(0).toInt()))
                tempList.append(query.value(0).toInt());
        }

        isFirstTime = false;
        trackIdResult.clear();
        trackIdResult = tempList;
        tempList.clear();
    }

    if (kind != "all"){
        query = QSqlQuery("select distinct(t_id) from Track where t_kind = \"" + kind + "\"");
        while (query.next()) {
            if (isFirstTime || trackIdResult.contains(query.value(0).toInt()))
                tempList.append(query.value(0).toInt());
        }

        isFirstTime = false;
        trackIdResult.clear();
        trackIdResult = tempList;
        tempList.clear();
    }

    if (musician != "all"){
        query = QSqlQuery("select distinct(t_id) from T_Navazandeh where tn_name = \"" + musician + "\"");
        while (query.next()) {
            if (isFirstTime || trackIdResult.contains(query.value(0).toInt()))
                tempList.append(query.value(0).toInt());
        }

        isFirstTime = false;
        trackIdResult.clear();
        trackIdResult = tempList;
        tempList.clear();
    }

    if (signer != "all"){
        query = QSqlQuery("select distinct(t_id) from T_Khanandeh where tk_name = \"" + signer + "\"");
        while (query.next()) {
            if (isFirstTime || trackIdResult.contains(query.value(0).toInt()))
                tempList.append(query.value(0).toInt());
        }
        isFirstTime = false;
        trackIdResult.clear();
        trackIdResult = tempList;
        tempList.clear();
    }

    if (dastgah != "all"){
        query = QSqlQuery("select distinct(t_id) from T_Dastgah where td_name = \"" + dastgah + "\"");
        while (query.next()) {
            if (isFirstTime || trackIdResult.contains(query.value(0).toInt()))
                tempList.append(query.value(0).toInt());
        }
        isFirstTime = false;
        trackIdResult.clear();
        trackIdResult = tempList;
        tempList.clear();
    }

    if (gusheh != "all"){
        query = QSqlQuery("select distinct(t_id) from T_Gusheh where tg_name = \"" + gusheh + "\"");
        while (query.next()) {
            if (isFirstTime || trackIdResult.contains(query.value(0).toInt()))
                tempList.append(query.value(0).toInt());
        }
        isFirstTime = false;
        trackIdResult.clear();
        trackIdResult = tempList;
        tempList.clear();
    }

    if (instrument != "all"){
        query = QSqlQuery("select distinct(t_id) from T_Saaz where ts_name = \"" + instrument + "\"");
        while (query.next()) {
            if (isFirstTime || trackIdResult.contains(query.value(0).toInt()))
                tempList.append(query.value(0).toInt());
        }
        isFirstTime = false;
        trackIdResult.clear();
        trackIdResult = tempList;
        tempList.clear();
    }

    if (composer != "all"){
        query = QSqlQuery("select distinct(t_id) from T_Ahangsaz where ta_name = \"" + composer + "\"");
        while (query.next()) {
            if (isFirstTime || trackIdResult.contains(query.value(0).toInt()))
                tempList.append(query.value(0).toInt());
        }
        isFirstTime = false;
        trackIdResult.clear();
        trackIdResult = tempList;
        tempList.clear();
    }

    qDebug() << "SearchMusic::findMusicsInDatabase trackIdResult:" <<trackIdResult;

    responseToUi(isFirstTime);

    QList<QObject *> dataList = {
//            new DataObject("Item 5", "red", "2"),
//            new DataObject("Item 6", "green", "3"),
//            new DataObject("Item 7", "blue", "4"),
//            new DataObject("Item 8", "yellow", "5")
        };

    QVariant ret = "";
    QVariant in = QVariant::fromValue(dataList);
    QMetaObject::invokeMethod(_mainQml, "searchResult", Q_RETURN_ARG(QVariant, ret), Q_ARG(QVariant, in));

//    _engine->rootContext()->setContextProperty("resultModel", in);
//    qDebug() << ret.toString();
}

void SearchMusic::responseToUi(bool isAll)
{
    QList<QObject *> dataList;
    QSqlQuery query;
    if (isAll){
        query = QSqlQuery("select t_id from Track");
        while (query.next()){
            trackIdResult.append(query.value(0).toInt());
        }
    }

    QString ra_name = "";
    QString ra_lyrics = "";
    QString ra_year = "";
    QString ra_pic = "";
    QString rt_name = "";
    QString rt_path = "";
    QString rt_time = "";
    QString rt_kind = "";
    QString rT_Navazandeh = "";
    QString rT_Khanandeh = "";
    QString rT_Dastgah = "";
    QString rT_Gusheh = "";
    QString rT_Saaz = "";
    QString rT_Ahangsaz = "";

    for (int i = 0; i < trackIdResult.length(); i++){
        query = QSqlQuery("select * from Track NATURAL JOIN Album where t_id = " + QString::number(trackIdResult.at(i)));
        query.next();

        int fieldNo = query.record().indexOf("a_name");
        ra_name = query.value(fieldNo).toString();

        fieldNo = query.record().indexOf("a_lyrics");
        ra_lyrics = query.value(fieldNo).toString();

        fieldNo = query.record().indexOf("a_year");
        ra_year = query.value(fieldNo).toString();

        fieldNo = query.record().indexOf("a_pic");
        ra_pic = query.value(fieldNo).toString();

        fieldNo = query.record().indexOf("t_name");
        rt_name = query.value(fieldNo).toString();

        fieldNo = query.record().indexOf("t_path");
        rt_path = query.value(fieldNo).toString();

        fieldNo = query.record().indexOf("t_time");
        rt_time = query.value(fieldNo).toString();

        fieldNo = query.record().indexOf("t_kind");
        rt_kind = query.value(fieldNo).toString();

        query = QSqlQuery("select tn_name from T_Navazandeh where t_id = " + QString::number(trackIdResult.at(i)));
        while (query.next()) {
            rT_Navazandeh = rT_Navazandeh + query.value(0).toString() + " , ";
        }
        rT_Navazandeh.remove(rT_Navazandeh.length()-3,3);

        query = QSqlQuery("select tk_name from T_Khanandeh where t_id = " + QString::number(trackIdResult.at(i)));
        while (query.next()) {
            rT_Khanandeh = rT_Khanandeh + query.value(0).toString() + " , ";
        }
        rT_Khanandeh.remove(rT_Khanandeh.length()-3,3);

        query = QSqlQuery("select td_name from T_Dastgah where t_id = " + QString::number(trackIdResult.at(i)));
        while (query.next()) {
            rT_Dastgah = rT_Dastgah + query.value(0).toString() + " , ";
        }
        rT_Dastgah.remove(rT_Dastgah.length()-3,3);

        query = QSqlQuery("select tg_name from T_Gusheh where t_id = " + QString::number(trackIdResult.at(i)));
        while (query.next()) {
            rT_Gusheh = rT_Gusheh + query.value(0).toString() + " , ";
        }
        rT_Gusheh.remove(rT_Gusheh.length()-3,3);

        query = QSqlQuery("select ts_name from T_Saaz where t_id = " + QString::number(trackIdResult.at(i)));
        while (query.next()) {
            rT_Saaz = rT_Saaz + query.value(0).toString() + " , ";
        }
        rT_Saaz.remove(rT_Saaz.length()-3,3);

        query = QSqlQuery("select ta_name from T_Ahangsaz where t_id = " + QString::number(trackIdResult.at(i)));
        while (query.next()) {
            rT_Ahangsaz = rT_Ahangsaz + query.value(0).toString() + " , ";
        }
        rT_Ahangsaz.remove(rT_Ahangsaz.length()-3,3);

        qDebug() << "SearchMusic::responseToUi: " <<ra_name  << ra_year << ra_pic << rt_name << rt_path << rt_time << rt_kind << rT_Navazandeh << rT_Khanandeh << rT_Dastgah << rT_Gusheh << rT_Saaz << rT_Ahangsaz;

        dataList.append(new DataObject(ra_name, ra_lyrics, ra_year, ra_pic, rt_name, rt_path, rt_time, rt_kind, rT_Navazandeh, rT_Khanandeh, rT_Dastgah, rT_Gusheh, rT_Saaz, rT_Ahangsaz));
    }

    QVariant in = QVariant::fromValue(dataList);
    _engine->rootContext()->setContextProperty("resultModel", in);
    trackIdResult.clear();
}

void SearchMusic::setMainQml(QObject *mainqml)
{
    _mainQml = mainqml;
}


DataObject::DataObject(QString a_name, QString a_lyrics, QString a_year, QString a_pic, QString t_name,
                       QString t_path, QString t_time, QString t_kind, QString T_Navazandeh, QString T_Khanandeh,
                       QString T_Dastgah, QString T_Gusheh, QString T_Saaz, QString T_Ahangsaz)
{
    this->_a_name = a_name;
    this->_a_lyrics = a_lyrics;
    this->_a_year = a_year;
    this->_a_pic = a_pic;
    this->_t_name = t_name;
    this->_t_path = t_path;
    this->_t_time = t_time;
    this->_t_kind = t_kind;
    this->_T_Navazandeh = T_Navazandeh;
    this->_T_Khanandeh = T_Khanandeh;
    this->_T_Dastgah = T_Dastgah;
    this->_T_Gusheh = T_Gusheh;
    this->_T_Saaz = T_Saaz;
    this->_T_Ahangsaz = T_Ahangsaz;

}

QString DataObject::a_name()
{
    return _a_name;
}

void DataObject::seta_name(const QString &a_name)
{
    if (a_name == _a_name)
        return;
    _a_name = a_name;
    emit a_nameChanged();
}

QString DataObject::a_lyrics()
{
    return _a_lyrics;
}

void DataObject::seta_lyrics(const QString &a_lyrics)
{
    if (a_lyrics == _a_lyrics)
        return;
    _a_lyrics = a_lyrics;
    emit a_lyricsChanged();
}

QString DataObject::a_year()
{
    return _a_year;
}

void DataObject::seta_year(const QString &a_year)
{
    if (a_year == _a_year)
        return;
    _a_year = a_year;
    emit a_yearChanged();
}

QString DataObject::a_pic()
{
    return _a_pic;
}

void DataObject::seta_pic(const QString &a_pic)
{
    if (a_pic == _a_pic)
        return;
    _a_pic = a_pic;
    emit a_picChanged();
}

QString DataObject::t_name()
{
    return _t_name;
}

void DataObject::sett_name(const QString &t_name)
{
    if (t_name == _t_name)
        return;
    _t_name = t_name;
    emit t_nameChanged();
}

QString DataObject::t_path()
{
    return _t_path;
}

void DataObject::sett_path(const QString &t_path)
{
    if (t_path == _t_path)
        return;
    _t_path = t_path;
    emit t_pathChanged();
}

QString DataObject::t_time()
{
    return _t_time;
}

void DataObject::sett_time(const QString &t_time)
{
    if (t_time == _t_time)
        return;
    _t_time = t_time;
    emit t_timeChanged();
}

QString DataObject::t_kind()
{
    return _t_kind;
}

void DataObject::sett_kind(const QString &t_kind)
{
    if (t_kind == _t_kind)
        return;
    _t_kind = t_kind;
    emit t_kindChanged();
}

QString DataObject::T_Navazandeh()
{
    return _T_Navazandeh;
}

void DataObject::setT_Navazandeh(const QString &T_Navazandeh)
{
    if (T_Navazandeh == _T_Navazandeh)
        return;
    _T_Navazandeh = T_Navazandeh;
    emit T_NavazandehChanged();
}

QString DataObject::T_Khanandeh()
{
    return _T_Khanandeh;
}

void DataObject::setT_Khanandeh(const QString &T_Khanandeh)
{
    if (T_Khanandeh == _T_Khanandeh)
        return;
    _T_Khanandeh = T_Khanandeh;
    emit T_KhanandehChanged();
}

QString DataObject::T_Dastgah()
{
    return _T_Dastgah;
}

void DataObject::setT_Dastgah(const QString &T_Dastgah)
{
    if (T_Dastgah == _T_Dastgah)
        return;
    _T_Dastgah = T_Dastgah;
    emit T_DastgahChanged();
}

QString DataObject::T_Gusheh()
{
    return _T_Gusheh;
}

void DataObject::setT_Gusheh(const QString &T_Gusheh)
{
    if (T_Gusheh == _T_Gusheh)
        return;
    _T_Gusheh = T_Gusheh;
    emit T_GushehChanged();
}

QString DataObject::T_Saaz()
{
    return _T_Saaz;
}

void DataObject::setT_Saaz(const QString &T_Saaz)
{
    if (T_Saaz == _T_Saaz)
        return;
    _T_Saaz = T_Saaz;
    emit T_SaazChanged();
}

QString DataObject::T_Ahangsaz()
{
    return _T_Ahangsaz;
}

void DataObject::setT_Ahangsaz(const QString &T_Ahangsaz)
{
    if (T_Ahangsaz == _T_Ahangsaz)
        return;
    _T_Ahangsaz = T_Ahangsaz;
    emit T_AhangsazChanged();
}
