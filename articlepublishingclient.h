#ifndef ARTICLEPUBLISHINGCLIENT_H
#define ARTICLEPUBLISHINGCLIENT_H

#include <QObject>
#include <QNetworkAccessManager>

class QNetworkReply;

class ArticlePublishingClient : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double infoTimestamp READ infoTimestamp NOTIFY infoUpdated)

public:
    explicit ArticlePublishingClient(QObject *parent = 0);

signals:
    void infoUpdated();

public slots:
    void requestInfo();

public:
    double infoTimestamp() const;

private slots:
//    void downloadFile();
//    void cancelDownload();
    void httpFinished();
    void httpReadyRead();
    void updateDataReadProgress(qint64 bytesRead, qint64 totalBytes);

private:
    double _infoTimestamp;
    QNetworkAccessManager qnam;
    QNetworkReply *reply;
    QByteArray responseData;
};

#endif // ARTICLEPUBLISHINGCLIENT_H
