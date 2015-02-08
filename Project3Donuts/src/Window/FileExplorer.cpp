#include "FileExplorer.hpp"
#include "ui_fileexplorer.h"
#include <iostream>
#include <string>
#include "Scene.hpp"
#include "Loader.hpp"
#include <QDebug>

FileExplorer::FileExplorer(QWidget *parent) :
    QMainWindow(parent,Qt::WindowStaysOnTopHint),
    ui(new Ui::FileExplorer)
{
    setWindowModality (Qt::ApplicationModal);
    ui->setupUi(this);

    // Creates our new model and populate
    QString mPath = "";
    mCurrentPath = mPath;
    mValidPath = mPath;

    // FILES
    fileModel = new QFileSystemModel(this);

    // Set filter
    fileModel->setFilter(QDir::NoDotAndDotDot |
                        QDir::Files|
                         QDir::AllDirs);

    // QFileSystemModel requires root path
    fileModel->setRootPath(mPath);

    // Attach the file model to the view
    ui->listView->setModel(fileModel);

}
FileExplorer::~FileExplorer()
{
    delete ui;
}

void FileExplorer::on_listView_clicked(const QModelIndex &index)
{
    if(fileModel->isDir(index)||mCurrentPath == "")
    {
        // ListView clicked, new file selected
        qDebug() << mCurrentPath;
        mCurrentPath = fileModel->fileInfo(index).absoluteFilePath();
        ui->listView->setRootIndex(fileModel->setRootPath(mCurrentPath));
        ui->listView->setModel(fileModel);
    }

}


void FileExplorer::button_ok_create_selected()
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
        std::string pathString(mCurrentPath.toStdString());
        if(!pathString.empty() && pathString.back() != '/')
            pathString.append("/");
        pathString.append(localString);
        Scene::getScene()->getLoader()->loadObject(pathString, "d");
    }

}

void FileExplorer::actionGetParent()
{
    if(mCurrentPath != "")
    {
        int i=mCurrentPath.length()-1;
        do{
            mCurrentPath.remove(i,1);
            i--;
        }
        while(mCurrentPath[i]!='/'&&i>=0);
        ui->listView->setRootIndex(fileModel->setRootPath(mCurrentPath));
        ui->listView->setModel(fileModel);
    }
}
/* for save as
void FileExplorer::actionCreateDirectory()
{
     QString text = QInputDialog::getText(this, tr("Name"),
                                          tr("Directory name:"), QLineEdit::Normal,
                                          QDir::home().dirName(), &ok);
        fileModel->mkdir(ui->listView->currentIndex(), text);
}
*/
