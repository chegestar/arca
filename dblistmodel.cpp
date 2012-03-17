#include "dblistmodel.h"
#include "dbrestclient.h"

DBListModel::DBListModel(DBRestClient *dbRestClient, QObject *parent) : QAbstractListModel(parent), _dbRestClient(dbRestClient)
{
    QHash<int, QByteArray> roles;
    roles[PathRole] = "path";
    roles[IsDirRole] = "isDir";
    setRoleNames(roles);
//    connect(_dbRestClient,
//            SIGNAL(loadedMetadata(const DBMetadata *)),
//            SLOT(loadedMetadata(const DBMetadata *)));
}

int DBListModel::rowCount(const QModelIndex &parent) const
{
    _metadataList.count();
}

QVariant DBListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= _metadataList.size())
        return QVariant();

    const DBMetadata &dbm = _metadataList[index.row()];
    if (role == PathRole)
        return dbm.path();
    else if (role == IsDirRole)
        return dbm.isDir();

    return QVariant();
}

void DBListModel::loadedMetadata(const DBMetadata *metadata)
{
    beginResetModel();

    _metadataList.clear();
    if (metadata->isDir())
        foreach(const DBMetadata &subfile, metadata->contents())
            _metadataList << subfile;

    endResetModel();
}

void DBListModel::loadMetadata(QString path)
{
    beginResetModel();
    _metadataList.clear();
    endResetModel();

    _dbRestClient->loadMetadata(path);
}
