#include "articlepublishingclient.h"
#include <QtNetwork>
#include <qjson/parser.h>

ArticlePublishingClient::ArticlePublishingClient(QObject *parent) :
    QObject(parent),
    _infoTimestamp(0.0)
{
}

double ArticlePublishingClient::infoTimestamp() const
{
    return _infoTimestamp;
}

void ArticlePublishingClient::requestInfo()
{
    responseData.clear();

    reply = qnam.get(QNetworkRequest(QUrl("http://bma-cms.appspot.com/info")));
    connect(reply, SIGNAL(finished()),
            this, SLOT(httpFinished()));
    connect(reply, SIGNAL(readyRead()),
            this, SLOT(httpReadyRead()));
    connect(reply, SIGNAL(downloadProgress(qint64,qint64)),
            this, SLOT(updateDataReadProgress(qint64,qint64)));
}

void ArticlePublishingClient::httpFinished()
{
    QJson::Parser parser;
    bool ok;

    QVariant result = parser.parse(responseData, &ok);
    QMap<QString, QVariant> resultMap = result.toMap();
    QVariant timestamp = resultMap["last_update_timestamp"];
    _infoTimestamp = timestamp.toDouble();
    emit infoUpdated();
}

void ArticlePublishingClient::httpReadyRead()
{
    responseData.append(reply->readAll());
}

void ArticlePublishingClient::updateDataReadProgress(qint64 bytesRead, qint64 totalBytes)
{
}
