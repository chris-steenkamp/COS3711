#include "album.h"
#include "albumlistmodel.h"

AlbumListModel::AlbumListModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    m_ColumnHeaders
            << "Composer/Artist"
            << "Album Title"
            << "Replacement Value (R)"
            << "Rating";
}

int AlbumListModel::columnCount(const QModelIndex&) const
{
    return m_ColumnHeaders.count();
}

QVariant AlbumListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Horizontal) {
            return m_ColumnHeaders[section];
        }
    }

    return QVariant();
}

Qt::ItemFlags AlbumListModel::flags(const QModelIndex &index) const
{
    if (index.isValid()) {
        return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
    }

    return  Qt::ItemIsEnabled;
}

void AlbumListModel::addAlbum(QString composer, QString name, float value, int rating)
{
    //Indicate to attached views that we are inserting a new record
    beginInsertRows(QModelIndex(), 0, 0);
    m_AlbumList.append(QSharedPointer<Album>(new Album(composer, name, value, rating)));
    endInsertRows();
}


QVariant AlbumListModel::data(const QModelIndex &index, int role) const
{
    if (index.isValid()) {
        int row = index.row();
        int col = index.column();

        if (row >= rowCount() || row < 0 || col >= columnCount() || col < 0) {
            return QVariant();
        }

        QSharedPointer<Album> album = m_AlbumList[row];

        if (role == Qt::DisplayRole || role == Qt::EditRole) {
            switch (col) {
            case 0: return album->composer();
            case 1: return album->name();
            case 2:
            {
                double val = static_cast<double>(album->replacementValue());
                //For display purposes we return a nice formatted string
                if (role == Qt::DisplayRole) {
                    return QString::number(val, 'f', 2);
                }
                //For editing we want a double spin box so we return the value
                else {
                      return val;
                }
            }
            case 3: return album->rating();
            }
        }
    }

    return QVariant();
}

bool AlbumListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role != Qt::EditRole || !index.isValid()) {
        return false;
    }

    int row = index.row();
    int col = index.column();

    if (row < 0 || row >= rowCount()) {
        return false;
    }

    QSharedPointer<Album> album = m_AlbumList[row];

    switch (col) {
    case 0: album->setComposer(value.toString()); break;
    case 1: album->setName(value.toString()); break;
    case 2:
    {
        float val = value.toFloat();
        //Don't allow illegal values to be captured
        if (val < 0 || val > 9999) {
            return false;
        }
        album->setReplacementValue(val);
        break;
    }
    case 3:
    {
        int val = value.toInt();
        //Don't allow illegal values to be captured
        if(val < 0 || val > 100) {
            return false;
        }
        album->setRating(value.toInt());
        break;
    }
    default: return false;
    }

    emit dataChanged(index, index);

    return true;
}

int AlbumListModel::rowCount(const QModelIndex&) const
{
    return m_AlbumList.size();
}
