#include "accessibletableview.h"
#include <QAccessible>
#include <QAccessibleTableCellInterface>

class TableCellAccessible : public QAccessibleTableCellInterface {
public:
    TableCellAccessible(QAccessible::Role role, QTableView *view, const QModelIndex &index)
        : QAccessibleInterface(QAccessible::RoleTableCell), m_view(view), m_index(index) {}

    QString text(QAccessible::Text t) override {
        if (t == QAccessible::Name) {
            return QString("Cell %1,%2").arg(m_index.row() + 1).arg(m_index.column() + 1);
        }
        return QString();
    }

    // Implement other virtual functions as needed
    // For simplicity, they're omitted here

private:
    QTableView *m_view;
    QModelIndex m_index;
};

AccessibleTableView::AccessibleTableView(QWidget *parent)
    : QTableView(parent)
{
    // No additional implementation needed for now
}

// You may need to override accessibility interfaces if deeper customization is required
