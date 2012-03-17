#ifndef ARTICLESTORE_H
#define ARTICLESTORE_H

#include <QObject>

class ArticleStore : public QObject
{
    Q_OBJECT
public:
    explicit ArticleStore(QObject *parent = 0);

signals:

public slots:

};

#endif // ARTICLESTORE_H
