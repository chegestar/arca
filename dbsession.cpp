#include "dbsession.h"

const QString kDBDropboxAPIHost = "api.dropbox.com";
const QString kDBDropboxAPIContentHost = "api-content.dropbox.com";

DBSession::DBSession(QObject *parent) :
    QObject(parent)
{
    if (_settings.contains("token"))
        _token = _settings.value("token").toString();
    if (_settings.contains("secret"))
        _tokenSecret = _settings.value("secret").toString();

    qDebug("OAuth token: %s", (const char *)_token.toAscii());
    qDebug("OAuth secret: %s", (const char *)_tokenSecret.toAscii());
}

void DBSession::setToken(const QString& token)
{
    _token = token;

    _settings.setValue("token", token);
    qDebug("Saving OAuth token: %s", (const char *)_token.toAscii());
}

void DBSession::setTokenSecret(const QString& tokenSecret)
{
    _tokenSecret = tokenSecret;

    _settings.setValue("secret", tokenSecret);
    qDebug("Saving OAuth secret: %s", (const char *)_tokenSecret.toAscii());
}

bool DBSession::hasCredentials() const
{
    return (_token.size() && _tokenSecret.size());
}
