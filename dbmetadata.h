#ifndef DBMETADATA_H
#define DBMETADATA_H

#include <QObject>

class DBMetadata
{
public:
    DBMetadata(QVariant result);

    QString path() const;
    bool isDir() const;
    QList<DBMetadata> contents() const;

private:
    QString _path;
    bool _isDir;
    QList<DBMetadata> _contents;
};

#endif // DBMETADATA_H
