#ifndef LARGETABLEMODEL_H
#define LARGETABLEMODEL_H

#include <QAbstractTableModel>
#include <QHash>

class LargeTableModel : public QAbstractTableModel {
    Q_OBJECT

public:
    LargeTableModel(int rows, int columns, QObject *parent = nullptr);
    ~LargeTableModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

private:
    int m_rows;
    int m_columns;
    // To store edited cells
    QHash<quint64, QString> editedData;

    quint64 getKey(int row, int column) const {
        return (static_cast<quint64>(row) << 32) | static_cast<quint64>(column);
    }
};

#endif // LARGETABLEMODEL_H
