#ifndef ACCESSIBLETABLEVIEW_H
#define ACCESSIBLETABLEVIEW_H

#include <QTableView>
#include <QAccessible>

class AccessibleTableView : public QTableView {
    Q_OBJECT

public:
    AccessibleTableView(QWidget *parent = nullptr);
};

#endif // ACCESSIBLETABLEVIEW_H
