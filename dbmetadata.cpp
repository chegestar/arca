#include "dbmetadata.h"
#include <QVariant>

DBMetadata::DBMetadata(QVariant result)
{
    QMap<QString, QVariant> resultMap = result.toMap();
    _path = resultMap["path"].toString();
    _isDir = resultMap["is_dir"].toBool();

    if (_isDir)
    {
        QList<QVariant> contentList = resultMap["contents"].toList();
        foreach(QVariant item, contentList)
            _contents.append(DBMetadata(item));
    }
}

QString DBMetadata::path() const
{
    return _path;
}

bool DBMetadata::isDir() const
{
    return _isDir;
}

QList<DBMetadata> DBMetadata::contents() const
{
    return _contents;
}
