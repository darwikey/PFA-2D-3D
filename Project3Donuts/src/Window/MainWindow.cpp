#include "MainWindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QStringListModel* modelList = Scene::getScene()->getListObjects();
    printf("count : %d\n", modelList->rowCount());
    ui->listView->setModel(modelList);
    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //ui->listView->setSelectionMode(QAbstractItemView::MultiSelection );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openfile()
{
    mOpen.show();

}

void MainWindow::selectObject(const QModelIndex &index)
{
    QModelIndexList localList =ui->listView->selectionModel()->selectedIndexes();
    QStringList stringList;
    foreach(const QModelIndex &index, localList){
        stringList.append( index.data(Qt::DisplayRole ).toString());
    }

    Scene::getScene()->selectObjectsByName(stringList);
    ui->widget->setFocus();
}
