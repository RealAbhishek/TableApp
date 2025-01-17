#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QHeaderView>
#include <QIntValidator>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    model(nullptr)
{
    // Central widget
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // Layouts
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    QHBoxLayout *inputLayout = new QHBoxLayout();

    // Row input
    QLabel *rowsLabel = new QLabel("Rows:", this);
    rowsEdit = new QLineEdit(this);
    rowsEdit->setValidator(new QIntValidator(1, 1000000, this));
    inputLayout->addWidget(rowsLabel);
    inputLayout->addWidget(rowsEdit);

    // Column input
    QLabel *columnsLabel = new QLabel("Columns:", this);
    columnsEdit = new QLineEdit(this);
    columnsEdit->setValidator(new QIntValidator(1, 1000000, this));
    inputLayout->addWidget(columnsLabel);
    inputLayout->addWidget(columnsEdit);

    // Generate button
    generateButton = new QPushButton("Generate Table", this);
    inputLayout->addWidget(generateButton);

    mainLayout->addLayout(inputLayout);

    // Table view
    tableView = new QTableView(this);
    tableView->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView->setSelectionBehavior(QAbstractItemView::SelectItems);
    tableView->horizontalHeader()->setStretchLastSection(true);
    tableView->verticalHeader()->setStretchLastSection(true);
    mainLayout->addWidget(tableView);

    // Connect button
    connect(generateButton, &QPushButton::clicked, this, &MainWindow::generateTable);

    setWindowTitle("Large Table Accessibility Demo");
    resize(800, 600);
}

MainWindow::~MainWindow()
{
    if (model) {
        delete model;
    }
}

void MainWindow::generateTable()
{
    bool okRows, okColumns;
    int rows = rowsEdit->text().toInt(&okRows);
    int columns = columnsEdit->text().toInt(&okColumns);

    if (!okRows || !okColumns || rows <= 0 || columns <= 0) {
        QMessageBox::warning(this, "Invalid Input", "Please enter valid positive integers for rows and columns.");
        return;
    }

    if (model) {
        delete model;
    }

    model = new LargeTableModel(rows, columns, this);
    tableView->setModel(model);

    // Adjust headers for better performance
    tableView->horizontalHeader()->setDefaultSectionSize(100);
    tableView->verticalHeader()->setDefaultSectionSize(25);

    // Optional: Resize table to fit the viewport to enhance performance
    tableView->resizeColumnsToContents();
    tableView->resizeRowsToContents();
}
