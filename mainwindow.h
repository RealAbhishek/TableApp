#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableView>
#include <QLineEdit>
#include <QPushButton>
#include "largetablemodel.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void generateTable();

private:
    QLineEdit *rowsEdit;
    QLineEdit *columnsEdit;
    QPushButton *generateButton;
    QTableView *tableView;
    LargeTableModel *model;
};

#endif // MAINWINDOW_H
