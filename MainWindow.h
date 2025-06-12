#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include "StorageManager.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onAddItemClicked();
    void onFindItemClicked();
    void onRemoveItemClicked();
    void about();
    void updateItemList();

private:
    QLineEdit *idInput, *descInput, *locInput;
    QLineEdit *findIdInput, *removeIdInput;
    QListWidget *itemList;
    StorageManager manager;

    void createMenus();
    void createWidgets();
    void setupLayout();
};

#endif // MAINWINDOW_H
