#include "QFileSystemModelDialog.hpp"
#include "ui_qfilesystemmodeldialog.h"
#include <iostream>
#include <string>
#include "Scene.hpp"
#include "Loader.hpp"


QFileSystemModelDialog::QFileSystemModelDialog(QWidget *parent) :
    QDialog(parent,Qt::WindowStaysOnTopHint),
    ui(new Ui::QFileSystemModelDialog)
{
    setWindowModality (Qt::ApplicationModal);
    ui->setupUi(this);

    // Creates our new model and populate
    QString mPath = "";
    mCurrentPath = mPath;
    mValidPath = mPath;
    // DIRECTORIES

    dirModel = new QFileSystemModel(this);

    // Set filter
    dirModel->setFilter(QDir::NoDotAndDotDot |
                        QDir::AllDirs);

    // QFileSystemModel requires root path
    dirModel->setRootPath(mPath);

    // Attach the dir model to the view
    ui->treeView->setModel(dirModel);


    // FILES

    fileModel = new QFileSystemModel(this);

    // Set filter
    fileModel->setFilter(QDir::NoDotAndDotDot |
                        QDir::Files);

    // QFileSystemModel requires root path
    fileModel->setRootPath(mPath);

    // Attach the file model to the view
    ui->listView->setModel(fileModel);
}

QFileSystemModelDialog::~QFileSystemModelDialog()
{
    delete ui;
}

void QFileSystemModelDialog::on_listView_clicked(const QModelIndex &index) //index not used but necessary for slot purposes
{
    // ListView clicked, new file selected
    mValidPath=mCurrentPath;
}

void QFileSystemModelDialog::on_treeView_clicked(const QModelIndex &index)
{
    // TreeView clicked
    // 1. We need to extract path
    // 2. Set that path into our ListView

    // Get the full path of the item that's user clicked on
    QString mPath = dirModel->fileInfo(index).absoluteFilePath();
    ui->listView->setRootIndex(fileModel->setRootPath(mPath));
    ui->listView->setModel(fileModel);
    mCurrentPath = mPath;

}

void QFileSystemModelDialog::button_ok_create_selected()
{
    hide();

    // Button ok pressed, we create the models
    QModelIndexList localList =ui->listView->selectionModel()->selectedIndexes();

    QStringList stringList;
    foreach(const QModelIndex &index, localList){
        stringList.append( index.data(Qt::DisplayRole ).toString());
    }

    foreach(QString str, stringList)
    {
        std::string localString(str.toStdString());
        std::string pathString(mValidPath.toStdString());
        if(!pathString.empty() && pathString.back() != '/')
            pathString.append("/");
        pathString.append(localString);
        Scene::getScene()->getLoader()->loadObject(pathString, "d");
    }

}
