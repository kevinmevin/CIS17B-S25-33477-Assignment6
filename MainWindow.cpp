#include "MainWindow.h"
#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QMenuBar>
#include <QAction>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    createMenus();
    createWidgets();
    setupLayout();

    setWindowTitle("Congo Inventory Management");
    updateItemList();
}

MainWindow::~MainWindow() {}

void MainWindow::createMenus() {
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    QAction *exitAction = fileMenu->addAction(tr("E&xit"));
    connect(exitAction, &QAction::triggered, this, &QWidget::close);

    QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));
    QAction *aboutAction = helpMenu->addAction(tr("&About"));
    connect(aboutAction, &QAction::triggered, this, &MainWindow::about);
}

void MainWindow::createWidgets() {
    idInput = new QLineEdit;
    descInput = new QLineEdit;
    locInput = new QLineEdit;
    findIdInput = new QLineEdit;
    removeIdInput = new QLineEdit;
    itemList = new QListWidget;
}

void MainWindow::setupLayout() {
    QWidget *centralWidget = new QWidget;
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // Add Item Form
    QFormLayout *addFormLayout = new QFormLayout;
    addFormLayout->addRow("ID:", idInput);
    addFormLayout->addRow("Description:", descInput);
    addFormLayout->addRow("Location:", locInput);
    QPushButton *addButton = new QPushButton("Add Item");
    addFormLayout->addWidget(addButton);
    connect(addButton, &QPushButton::clicked, this, &MainWindow::onAddItemClicked);

    // Find Item
    QHBoxLayout *findLayout = new QHBoxLayout;
    findLayout->addWidget(new QLabel("Find by ID:"));
    findLayout->addWidget(findIdInput);
    QPushButton *findButton = new QPushButton("Find");
    findLayout->addWidget(findButton);
    connect(findButton, &QPushButton::clicked, this, &MainWindow::onFindItemClicked);

    // Remove Item
    QHBoxLayout *removeLayout = new QHBoxLayout;
    removeLayout->addWidget(new QLabel("Remove by ID:"));
    removeLayout->addWidget(removeIdInput);
    QPushButton *removeButton = new QPushButton("Remove");
    removeLayout->addWidget(removeButton);
    connect(removeButton, &QPushButton::clicked, this, &MainWindow::onRemoveItemClicked);

    mainLayout->addLayout(addFormLayout);
    mainLayout->addLayout(findLayout);
    mainLayout->addLayout(removeLayout);
    mainLayout->addWidget(new QLabel("Items (Sorted by Description):"));
    mainLayout->addWidget(itemList);

    setCentralWidget(centralWidget);
}

void MainWindow::onAddItemClicked() {
    try {
        bool ok;
        int id = idInput->text().toInt(&ok);
        if (!ok) {
            QMessageBox::critical(this, "Error", "Invalid ID. Please enter a number.");
            return;
        }
        std::string desc = descInput->text().toStdString();
        std::string loc = locInput->text().toStdString();

        if (desc.empty() || loc.empty()) {
            QMessageBox::critical(this, "Error", "Description and Location cannot be empty.");
            return;
        }

        manager.addItem(id, desc, loc);
        updateItemList();
        idInput->clear();
        descInput->clear();
        locInput->clear();
    } catch (const DuplicateItemException& e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}

void MainWindow::onFindItemClicked() {
    try {
        bool ok;
        int id = findIdInput->text().toInt(&ok);
        if (!ok) {
            QMessageBox::critical(this, "Error", "Invalid ID. Please enter a number.");
            return;
        }
        auto item = manager.findById(id);
        QString message = QString("ID: %1\nDescription: %2\nLocation: %3")
                              .arg(item->id)
                              .arg(QString::fromStdString(item->description))
                              .arg(QString::fromStdString(item->location));
        QMessageBox::information(this, "Item Found", message);
        findIdInput->clear();
    } catch (const ItemNotFoundException& e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}

void MainWindow::onRemoveItemClicked() {
    try {
        bool ok;
        int id = removeIdInput->text().toInt(&ok);
        if (!ok) {
            QMessageBox::critical(this, "Error", "Invalid ID. Please enter a number.");
            return;
        }
        manager.removeItem(id);
        updateItemList();
        removeIdInput->clear();
    } catch (const ItemNotFoundException& e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}

void MainWindow::about() {
    QMessageBox::about(this, "About Congo GUI", "Congo Inventory Management System\nBy: Kevin Grissom");
}

void MainWindow::updateItemList() {
    itemList->clear();
    auto sortedItems = manager.listItemsByDescription();
    for (const auto& pair : sortedItems) {
        QString itemText = QString("ID: %1, Desc: %2, Loc: %3")
        .arg(pair.second->id)
            .arg(QString::fromStdString(pair.second->description))
            .arg(QString::fromStdString(pair.second->location));
        itemList->addItem(itemText);
    }
}
