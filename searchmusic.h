#ifndef SEARCHMUSIC_H
#define SEARCHMUSIC_H

#include <QObject>
#include <QQmlEngine>
#include <QtSql>

class SearchMusic : public QObject
{
    Q_OBJECT
public:
    SearchMusic(QObject *parent = nullptr);
    SearchMusic(QQmlEngine *engine, QObject *parent = nullptr);
    SearchMusic(QObject *mainqml, QQmlEngine *engine, QObject *parent = nullptr);
    Q_INVOKABLE void findMusicsInDatabase(const QString &albumName,
                                          const QString &trackName,
                                          const QString &musician,
                                          const QString &signer,
                                          const QString &dastgah,
                                          const QString &gusheh,
                                          const QString &instrument,
                                          const QString &composer,
                                          const QString &Lyrics,
                                          const QString &kind);

    void responseToUi(bool isAll = false);
    void setMainQml(QObject *mainqml);
signals:

private:
    QObject *_mainQml;
    QQmlEngine *_engine;
    QList<int> trackIdResult;

};

class DataObject : public QObject
{
public :
    DataObject(QString a_name, QString a_lyrics, QString a_year, QString a_pic, QString t_name,
               QString t_path, QString t_time, QString t_kind, QString T_Navazandeh, QString T_Khanandeh,
               QString T_Dastgah, QString T_Gusheh, QString T_Saaz, QString T_Ahangsaz);
    Q_OBJECT

    Q_PROPERTY(QString a_name READ a_name WRITE seta_name NOTIFY a_nameChanged)
    QString a_name();
    void seta_name(const QString &a_name);

    Q_PROPERTY(QString a_lyrics READ a_lyrics WRITE seta_lyrics NOTIFY a_lyricsChanged)
    QString a_lyrics();
    void seta_lyrics(const QString &a_lyrics);

    Q_PROPERTY(QString a_year READ a_year WRITE seta_year NOTIFY a_yearChanged)
    QString a_year();
    void seta_year(const QString &a_year);

    Q_PROPERTY(QString a_pic READ a_pic WRITE seta_pic NOTIFY a_picChanged)
    QString a_pic();
    void seta_pic(const QString &a_pic);

    Q_PROPERTY(QString t_name READ t_name WRITE sett_name NOTIFY t_nameChanged)
    QString t_name();
    void sett_name(const QString &t_name);

    Q_PROPERTY(QString t_path READ t_path WRITE sett_path NOTIFY t_pathChanged)
    QString t_path();
    void sett_path(const QString &t_path);

    Q_PROPERTY(QString t_time READ t_time WRITE sett_time NOTIFY t_timeChanged)
    QString t_time();
    void sett_time(const QString &t_time);

    Q_PROPERTY(QString t_kind READ t_kind WRITE sett_kind NOTIFY t_kindChanged)
    QString t_kind();
    void sett_kind(const QString &t_kind);

    Q_PROPERTY(QString T_Navazandeh READ T_Navazandeh WRITE setT_Navazandeh NOTIFY T_NavazandehChanged)
    QString T_Navazandeh();
    void setT_Navazandeh(const QString &T_Navazandeh);

    Q_PROPERTY(QString T_Khanandeh READ T_Khanandeh WRITE setT_Khanandeh NOTIFY T_KhanandehChanged)
    QString T_Khanandeh();
    void setT_Khanandeh(const QString &T_Khanandeh);

    Q_PROPERTY(QString T_Dastgah READ T_Dastgah WRITE setT_Dastgah NOTIFY T_DastgahChanged)
    QString T_Dastgah();
    void setT_Dastgah(const QString &T_Dastgah);

    Q_PROPERTY(QString T_Gusheh READ T_Gusheh WRITE setT_Gusheh NOTIFY T_GushehChanged)
    QString T_Gusheh();
    void setT_Gusheh(const QString &T_Gusheh);

    Q_PROPERTY(QString T_Saaz READ T_Saaz WRITE setT_Saaz NOTIFY T_SaazChanged)
    QString T_Saaz();
    void setT_Saaz(const QString &T_Saaz);

    Q_PROPERTY(QString T_Ahangsaz READ T_Ahangsaz WRITE setT_Ahangsaz NOTIFY T_AhangsazChanged)
    QString T_Ahangsaz();
    void setT_Ahangsaz(const QString &T_Ahangsaz);

signals:
    void a_nameChanged();
    void a_lyricsChanged();
    void a_yearChanged();
    void a_picChanged();
    void t_nameChanged();
    void t_pathChanged();
    void t_timeChanged();
    void t_kindChanged();
    void T_NavazandehChanged();
    void T_KhanandehChanged();
    void T_DastgahChanged();
    void T_GushehChanged();
    void T_SaazChanged();
    void T_AhangsazChanged();

private:
    QString _a_name;
    QString _a_lyrics;
    QString _a_year;
    QString _a_pic;
    QString _t_name;
    QString _t_path;
    QString _t_time;
    QString _t_kind;
    QString _T_Navazandeh;
    QString _T_Khanandeh;
    QString _T_Dastgah;
    QString _T_Gusheh;
    QString _T_Saaz;
    QString _T_Ahangsaz;

};


#endif // SEARCHMUSIC_H
