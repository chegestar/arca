#ifndef DBSESSION_H
#define DBSESSION_H

#include <QObject>
#include <QSettings>

const int kDBDropboxAPIVersion = 0;
extern const QString kDBDropboxAPIHost;
extern const QString kDBDropboxAPIContentHost;

class DBSession : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString consumerKey READ consumerKey WRITE setConsumerKey)
    Q_PROPERTY(QString consumerSecret READ consumerSecret WRITE setConsumerSecret)
    Q_PROPERTY(QString token READ token WRITE setToken)
    Q_PROPERTY(QString tokenSecret READ tokenSecret WRITE setTokenSecret)
    Q_PROPERTY(bool hasCredentials READ hasCredentials)

public:
    explicit DBSession(QObject *parent = 0);

    QString consumerKey() const { return _consumerKey; }
    void setConsumerKey(const QString& consumerKey) { _consumerKey = consumerKey; }
    QString consumerSecret() const { return _consumerSecret; }
    void setConsumerSecret(const QString& consumerSecret) { _consumerSecret = consumerSecret; }
    QString token() const { return _token; }
    void setToken(const QString& token);
    QString tokenSecret() const { return _tokenSecret; }
    void setTokenSecret(const QString& tokenSecret);

    bool hasCredentials() const;

signals:

public slots:

private:
    QString _consumerKey;
    QString _consumerSecret;
    QString _token;
    QString _tokenSecret;
    QSettings _settings;
};

#endif // DBSESSION_H
