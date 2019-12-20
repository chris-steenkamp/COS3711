#ifndef ALBUMLISTMODEL_H
#define ALBUMLISTMODEL_H

#include <QAbstractTableModel>
#include <QList>
#include <QModelIndex>
#include <QSharedPointer>
#include <QString>
#include <QVariant>

#include "album.h"

class AlbumListModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit AlbumListModel(QObject *parent = 0);
    int rowCount(const QModelIndex& = QModelIndex()) const;
    int columnCount(const QModelIndex& = QModelIndex()) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex& index) const;

    void addAlbum(QString composer, QString name, float value, int rating);
private:
    QList<QSharedPointer<Album> > m_AlbumList;
    QStringList m_ColumnHeaders;
};

#endif // ALBUMLISTMODEL_H
