#include "MainWindow.hpp"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include "Scene.hpp"
#include "Loader.hpp"

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
    win_about = new QMainWindow();
    win_about->setWindowFlags(Qt::WindowStaysOnTopHint);
    win_about->setWindowModality (Qt::ApplicationModal);
    _about_ui = new Ui::About();
    _about_ui->setupUi(win_about);
}

MainWindow::~MainWindow()
{
    delete win_about;
    delete _about_ui;
    delete ui;
}

void MainWindow::openfile()
{
    QString _qfile = QFileDialog::getOpenFileName(0, "Importer", QString(), "Modeles (*.obj *.ply)");
    std::string _file = _qfile.toStdString();
    if(_file!="")
    {
        //now we computer the name of the object
        int _num=0;
        std::string  _num_name;
        std::cout<<_file<<std::endl;
        std::string _name = _file.substr(_file.find_last_of('/')+1);
        std::cout<<_name<<std::endl;
        _name = _name.substr(0,_name.find_last_of('.'));
        std::cout<<_name<<std::endl;
        do
        {
            _num_name=_name;
            if(_num==0)
            {
                if(Scene::getScene()->getObject(_num_name) == nullptr)
                    break;
            }
            _num++;
        }
        while(Scene::getScene()->getObject(_num_name.append(std::to_string(_num))) != nullptr);

        Scene::getScene()->getLoader()->loadObject(_file, _num_name);
    }
}

void MainWindow::newscene()
{
    QMessageBox::critical(0, "Error", "Not implemented yet");
}

void MainWindow::openlibfile()
{
    QMessageBox::critical(0, "Error", "Not implemented yet");

}

void MainWindow::open()
{
    QString _qfile = QFileDialog::getOpenFileName(0, "Ouvrir", QString(), "Scene (*.xml)");
    if(_qfile!="")
    {
        Scene::getScene()->createScene(_qfile);
    }
}

void MainWindow::save()
{


}

void MainWindow::saveas()
{
    QString _qfile = QFileDialog::getSaveFileName(0, "Sauvegarder", QString(), "Scene (*.xml)");
    std::string _file = _qfile.toStdString();
    if(_file!="")
    {
        Scene::getScene()->saveScene(_file);
    }
}

void MainWindow::selectObject(const QModelIndex &index)
{
    QModelIndexList localList =ui->listView->selectionModel()->selectedIndexes();
    QStringList stringList;
    foreach(const QModelIndex &index, localList){
        stringList.append( index.data(Qt::DisplayRole ).toString());
    }

    Scene::getScene()->selectObjectsByName(stringList);
    //refresh widget
    ui->widget->setFocus();
    //come back to the list
    ui->listView->setFocus();
}
void MainWindow::invertwidgets()
{
    if(ui->actionInverser_les_positions_des_fen_tres->isChecked())
    {
        QSplitter *splitter = ui->splitter;
        ui->splitter = new QSplitter(ui->centralwidget);
        ui->splitter->setObjectName(QStringLiteral("splitter"));
        ui->splitter->setOrientation(Qt::Horizontal);
        ui->listView->setParent(ui->splitter);
        ui->widget->setParent(ui->splitter);
        QList<int> sizes;
        sizes.append(182);
        sizes.append(600);

        ui->splitter->setSizes(sizes);
        ui->horizontalLayout->addWidget(ui->splitter);
        delete splitter;
    }
    else
    {
        QSplitter *splitter = ui->splitter;
        ui->splitter = new QSplitter(ui->centralwidget);
        ui->splitter->setObjectName(QStringLiteral("splitter"));
        ui->splitter->setOrientation(Qt::Horizontal);
        ui->widget->setParent(ui->splitter);
        ui->listView->setParent(ui->splitter);
        QList<int> sizes;
        sizes.append(600);
        sizes.append(182);
        ui->splitter->setSizes(sizes);
        ui->horizontalLayout->addWidget(ui->splitter);

        delete splitter;
    }
}

void MainWindow::editsettings()
{
    QMessageBox::critical(0, "Error", "Not implemented yet");
}

void MainWindow::about()
{
    win_about->show();
}
