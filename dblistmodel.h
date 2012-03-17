#ifndef DBLISTMODEL_H
#define DBLISTMODEL_H

#include <QAbstractListModel>
#include "dbmetadata.h"

class DBRestClient;

class DBListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum DBListModelRoles
    {
        PathRole = Qt::UserRole + 1,
        IsDirRole
    };
    DBListModel(DBRestClient *dbRestClient, QObject *parent = 0);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

public slots:
    void loadedMetadata(const DBMetadata *metadata);

    void loadMetadata(QString path);

private:
    QList<DBMetadata> _metadataList;
    DBRestClient *_dbRestClient;
};

#endif // DBLISTMODEL_H
