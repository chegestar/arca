#ifndef DBRESTCLIENT_H
#define DBRESTCLIENT_H

#include <QObject>
#include <QtNetwork/QtNetwork>
#include "dbsession.h"
#include "kqoauthrequest.h"

class QNetworkRequest;
class KQOAuthManager;
class DBMetadata;

class DBRestClient : public QObject
{
    Q_OBJECT
    Q_PROPERTY(DBSession *session READ session)
    Q_PROPERTY(bool hasCredentials READ hasCredentials)

public:
    explicit DBRestClient(DBSession &session, QObject *parent = 0);

    DBSession *session();
    bool hasCredentials() const;

signals:
    void online();
    void authorized();
    void loadedFile(QByteArray fileData);
    void loadedMetadata(const QString &metadata);
    void needAuthorization();
    void error(QByteArray networkReply);

public slots:
    void openNetworkSession();

//    void login(const QString &email, const QString &password);

    void requestToken();

    void loadFile(const QString &path);

    void loadMetadata(const QString &path);

    void loadAccountInfo();

    void requestReady(QByteArray networkReply);

//    void receivedToken(QString oauth_token, QString oauth_token_secret);

    void temporaryTokenReceived(QString oauth_token, QString oauth_token_secret);

    void accessTokenCallback(const QUrl &url);

    // TESTING
    void showFile();

private slots:
    void onOpened();

private:
    QNetworkSession *_networkSession;
    DBSession &_session;
    KQOAuthManager *manager;
    KQOAuthRequest *req;
    QString _currentPath;
    bool _statusInResponse;
    QString _filePath;

    QString _root;

    QString _oauthToken;
    QString _oauthTokenSecret;

    void executeRequest(const QString &protocol,
                        const QString &host,
                        const QString &path,
                        const KQOAuthParameters *params = 0,
                        KQOAuthRequest::RequestHttpMethod httpMethod = KQOAuthRequest::POST,
                        KQOAuthRequest::RequestType requestType = KQOAuthRequest::AuthorizedRequest);
};

#endif // DBRESTCLIENT_H
