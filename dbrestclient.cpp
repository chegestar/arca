#include "dbrestclient.h"
#include <QtNetwork>
//#include <QByteArray>
#include "kqoauthmanager.h"
#include <qjson/parser.h>
#include "dbmetadata.h"
#include <contentaction/contentaction.h>

const QString kDBProtocolHTTP = "http";
const QString kDBProtocolHTTPS = "https";

DBRestClient::DBRestClient(DBSession &session, QObject *parent) :
    QObject(parent),
    _session(session),
    _root("dropbox")
{
    manager = new KQOAuthManager(this);
    connect(manager, SIGNAL(requestReady(QByteArray)), SLOT(requestReady(QByteArray)));

    req = new KQOAuthRequest(this);
    req->setEnableDebugOutput(true);

    QNetworkConfiguration config;
    QNetworkConfigurationManager mgr;
    QList<QNetworkConfiguration> activeConfigs = mgr.allConfigurations(QNetworkConfiguration::Active);

    if (activeConfigs.count())
        config = activeConfigs[0];
    else
        config = mgr.defaultConfiguration();

    _networkSession = new QNetworkSession(config);
    connect(_networkSession, SIGNAL(opened()), SLOT(onOpened()));
}

DBSession *DBRestClient::session()
{
    return &_session;
}

bool DBRestClient::hasCredentials() const
{
    return _session.hasCredentials();
}

void DBRestClient::openNetworkSession()
{
    if (!_networkSession->isOpen())
    {
        qDebug("Opening network session");
        _networkSession->open();
    }
}

void DBRestClient::login(const QString &email, const QString &password)
{
    KQOAuthParameters params;
    params.insert("email", email);
    params.insert("password", password);
    executeRequest(kDBProtocolHTTPS, kDBDropboxAPIHost, "/token", &params, KQOAuthRequest::POST, KQOAuthRequest::TemporaryCredentials);
}

void DBRestClient::loadFile(const QString &path)
{
    QString fullPath = QString("/files/%1%2")
            .arg(_root)
            .arg(path);
    executeRequest(kDBProtocolHTTPS, kDBDropboxAPIContentHost, fullPath, 0, KQOAuthRequest::GET);
}

void DBRestClient::loadMetadata(const QString &path)
{
    _filePath = path;
    QString fullPath = QString("/metadata/%1%2")
            .arg(_root)
            .arg(path);
    executeRequest(kDBProtocolHTTP, kDBDropboxAPIHost, fullPath, 0, KQOAuthRequest::GET);
}

void DBRestClient::loadAccountInfo()
{
    executeRequest(kDBProtocolHTTP, kDBDropboxAPIHost, "/account/info");
}

void DBRestClient::requestReady(QByteArray networkReply)
{
    qDebug("REQUEST READY");

    if (manager->lastError() != KQOAuthManager::NoError)
    {
        emit error(networkReply);
        return;
    }

    QString replyPath = _currentPath;
    _currentPath.clear();

    if (_statusInResponse)
    {
        QJson::Parser parser;
        bool ok;

        QVariant result = parser.parse(networkReply, &ok);
        QMap<QString, QVariant> resultMap = result.toMap();

        uint status = resultMap["status"].toUInt();
        if (status == 401)
        {
            emit needAuthorization();
            return;
        }

        QMap<QString, QVariant> bodyMap = resultMap["body"].toMap();

        if (replyPath == "/token")
        {
            QVariant token = bodyMap["token"];
            _session.setToken(token.toString());
            QVariant tokenSecret = bodyMap["secret"];
            _session.setTokenSecret(tokenSecret.toString());

            emit authorized();
        }
        else if (replyPath.startsWith("/metadata"))
        {
            QString replyString(networkReply);
            emit loadedMetadata(replyString);
        }
        else if (replyPath == "/account/info")
        {
            QVariant displayName = bodyMap["display_name"];
            qDebug() << displayName.toString();
        }
    }
    else
    {
        if (replyPath.startsWith("/files"))
        {

            QString fullPath = QDir::tempPath() + _filePath;
            QFile file(fullPath);
            file.write(networkReply);
            emit loadedFile(networkReply);
        }
    }
}

void DBRestClient::showFile()
{
    ContentAction::Action action = ContentAction::Action::defaultActionForFile(QUrl("file:///home/user/MyDocs/DCIM/20110719_001.jpg"));
    if (action.isValid())
    {
        qDebug() << "Valid action, name: " << action.name();
        action.trigger();
    }
    else
    {
        qDebug("Invalid action");
    }
}

void DBRestClient::onOpened()
{
    qDebug("Opened network session");
    emit online();
}

void DBRestClient::executeRequest(const QString &protocol,
                                  const QString &host,
                                  const QString &path,
                                  const KQOAuthParameters *params,
                                  KQOAuthRequest::RequestHttpMethod httpMethod,
                                  KQOAuthRequest::RequestType requestType)
{
    QString escapedPath = QString(QUrl::toPercentEncoding(path, "/", ":?=,!$&'()*+;[]@#~"));

    QString urlString = QString("%1://%2/%3%4")
            .arg(protocol)
            .arg(host)
            .arg(kDBDropboxAPIVersion)
            .arg(escapedPath);
    QUrl url(urlString);

    qDebug() << urlString;

    if (!url.isValid())
        qDebug() << "WARNING: Invalid URL";

    _currentPath = path;

    req->initRequest(requestType, url);
    req->setHttpMethod(httpMethod);
    req->setConsumerKey(_session.consumerKey());
    req->setConsumerSecretKey(_session.consumerSecret());
    if (requestType == KQOAuthRequest::AuthorizedRequest)
    {
        req->setToken(_session.token());
        req->setTokenSecret(_session.tokenSecret());
    }

    KQOAuthParameters additionalParams;
    if (!path.startsWith("/files"))
    {
        additionalParams.insert("status_in_response", "true");
        _statusInResponse = true;
    }
    else
        _statusInResponse = false;

    if (params)
        additionalParams += *params;
    req->setAdditionalParameters(additionalParams);

    manager->executeRequest(req);
}
