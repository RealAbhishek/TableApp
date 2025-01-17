#include "largetablemodel.h"

LargeTableModel::LargeTableModel(int rows, int columns, QObject *parent)
    : QAbstractTableModel(parent), m_rows(rows), m_columns(columns)
{
}

LargeTableModel::~LargeTableModel()
{
}

int LargeTableModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return m_rows;
}

int LargeTableModel::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return m_columns;
}

QVariant LargeTableModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid())
        return QVariant();

    int row = index.row();
    int column = index.column();

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        quint64 key = getKey(row, column);
        if (editedData.contains(key)) {
            return editedData.value(key);
        } else {
            return QString("Cell %1,%2").arg(row + 1).arg(column + 1);
        }
    }

    return QVariant();
}

bool LargeTableModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (role != Qt::EditRole || !index.isValid())
        return false;

    int row = index.row();
    int column = index.column();
    quint64 key = getKey(row, column);
    editedData[key] = value.toString();
    emit dataChanged(index, index, {Qt::DisplayRole, Qt::EditRole});
    return true;
}

Qt::ItemFlags LargeTableModel::flags(const QModelIndex &index) const {
    if (!index.isValid())
        return Qt::NoItemFlags;
    return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
}

QVariant LargeTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
        return QString("Col %1").arg(section + 1);
    else
        return QString("Row %1").arg(section + 1);
}
