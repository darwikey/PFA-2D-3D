#include "MainWindow.hpp"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include "Scene.hpp"
#include "TransformWidget.hpp"
#include "Loader.hpp"
#include "Object.hpp"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QSettings settings("settings.ini", QSettings::IniFormat);
    ui->setupUi(this);
    if(settings.value("General/invertedwindows",false).toBool())
        ui->actionInverser_les_positions_des_fen_tres->toggle();
    ui->actionTranslate->toggle();

    QStringListModel* modelList = Scene::getScene()->getListObjects();
    ui->listView->setModel(modelList);
    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //ui->listView->setSelectionMode(QAbstractItemView::MultiSelection );
    win_about = new QMainWindow();
    win_about->setWindowFlags(Qt::WindowStaysOnTopHint);
    win_about->setWindowModality (Qt::ApplicationModal);
    _about_ui = new Ui::About();
    _about_ui->setupUi(win_about);
    _settingsWindow = new Settings(this);
    QObject::connect(_settingsWindow, SIGNAL(finished (int)), this, SLOT(checkSettings(int)));
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
	Scene::getScene()->clearScene();
    //refresh widget
    ui->widget->update();
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
        Scene::getScene()->clearScene();
        Scene::getScene()->createScene(_qfile);
    }
}

void MainWindow::revertPreviousAction()
{
    Scene::getScene()->revertPreviousAction();
    ui->widget->update();
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
   ui->widget->update();
}

void MainWindow::deleteSelectedObject()
{
    std::cout<<"deleting..."<<std::endl;
    QModelIndexList localList =ui->listView->selectionModel()->selectedIndexes();
    QStringList stringList;
    foreach(const QModelIndex &index, localList){
        stringList.append( index.data(Qt::DisplayRole ).toString());
    }
    Scene::getScene()->deleteObjectsByName(stringList);
    //refresh widget
    ui->widget->update();
}

void MainWindow::changeObjectColor(){
	QColor _colorRGB = QColorDialog::getColor(QColor(128, 128, 128), nullptr, "Select Color", QColorDialog::DontUseNativeDialog);
	QVector3D _color(_colorRGB.red(), _colorRGB.green(), _colorRGB.blue());
	
	Object* _selectedObject = Scene::getScene()->getObject(Scene::getScene()->getNameSelectedObject());
	if (_selectedObject){
		_selectedObject->setGlobalColor(_color / 255.f);
	}
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
    _settingsWindow->exec();
}

void MainWindow::about()
{
    win_about->show();
}

void MainWindow::checkSettings(int result){ //this is a slot
   if(result == QDialog::Accepted){
       //change keyboard bindings
       QSettings settings("settings.ini", QSettings::IniFormat);
       ui->actionEffectuer_un_rendu->setShortcut(settings.value("Shortcuts/render", QKeySequence("P")).value<QKeySequence>());
       ui->actionAnaglyphes->setShortcut(settings.value("Shortcuts/anaglyphes",QKeySequence("N")).value<QKeySequence>());
       ui->actionAuto_st_r_ogrammes->setShortcut(settings.value("Shortcuts/autostereogramme",QKeySequence("U")).value<QKeySequence>());
       ui->actionFlipbook->setShortcut(settings.value("Shortcuts/flipbook",QKeySequence("F")).value<QKeySequence>());
       ui->actionTranslate->setShortcut(settings.value("Shortcuts/translate",QKeySequence("T")).value<QKeySequence>());
       ui->actionRotate->setShortcut(settings.value("Shortcuts/rotate",QKeySequence("R")).value<QKeySequence>());
       ui->actionScale->setShortcut(settings.value("Shortcuts/scale",QKeySequence("S")).value<QKeySequence>());
   }
}

void MainWindow::changeModeToTranslate()
{
    Scene::getScene()->getTransformWidget()->changeState(TransformWidget::State::TRANSLATION);
    ui->actionTranslate->setChecked(true);
    ui->actionRotate->setChecked(false);
    ui->actionScale->setChecked(false);
}

void MainWindow::changeModeToRotate()
{
    Scene::getScene()->getTransformWidget()->changeState(TransformWidget::State::ROTATION);
    ui->actionTranslate->setChecked(false);
    ui->actionRotate->setChecked(true);
    ui->actionScale->setChecked(false);
}

void MainWindow::changeModeToScale()
{
    Scene::getScene()->getTransformWidget()->changeState(TransformWidget::State::SCALE);
    ui->actionTranslate->setChecked(false);
    ui->actionRotate->setChecked(false);
    ui->actionScale->setChecked(true);
}
