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
    mNeedSave = false;
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

    win_notice = new QMainWindow();
    win_notice->setWindowFlags(Qt::WindowStaysOnTopHint);
    win_notice->setWindowModality (Qt::ApplicationModal);
    _notice_ui = new Ui::Notice();
    _notice_ui->setupUi(win_notice);

    _settingsWindow = new Settings(this);
    QObject::connect(_settingsWindow, SIGNAL(finished (int)), this, SLOT(checkSettings(int)));

    Scene::getScene()->createScene("resources/example/maScene.xml");
    Scene::getScene()->setName("");
    Scene::getScene()->setPath("");
}

MainWindow::~MainWindow()
{
    delete win_about;
    delete _about_ui;
    delete win_notice;
    delete _notice_ui;
    delete ui;
}

void MainWindow::openfile()
{
    QString _qfile = QFileDialog::getOpenFileName(0, "Importer", QString(), "Modeles (*.obj *.ply)");
    std::string _file = _qfile.toStdString();
    int ret;
    if(_file!="")
    {
        QMessageBox _retBox(QMessageBox::Question, tr("Project3Donut"),
                                    tr("Souhaitez vous creer une copie du modèle dans le dossier du projet ?\n"),
                                    QMessageBox::Yes | QMessageBox::No, this);
        _retBox.setButtonText(QMessageBox::Yes, "Oui");
        _retBox.setButtonText(QMessageBox::No, "Non");
        ret = _retBox.exec();

        //now we computer the name of the object
        int _num=0;
        std::string  _num_name;
        std::string _name = _file.substr(_file.find_last_of('/')+1);
        _name = _name.substr(0,_name.find_last_of('.'));

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
        //we copy the file and set the path to local
        if (ret == QMessageBox::Yes) {
            QFile::copy(_qfile, QString((Scene::getScene()->getPath() + _file.substr(_file.find_last_of('/')+1)).c_str()));
            Scene::getScene()->getObject(_num_name)->setPath("#"+_file.substr(_file.find_last_of('/')+1));
        }
        //notify the window that a new change has yet to be saved
        newaction();
     }
}

void MainWindow::newscene()
{
    int ret;
    if(Scene::getScene()->hasName() && mNeedSave)
    {
        QMessageBox _retBox(QMessageBox::Question, tr("Project3Donut"),
                                    tr("Il y a des changements non enregistrés.\n"
                                       "Voulez vous enregistrer ces changements ?\n"),
                                    QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel,this);
        _retBox.setButtonText(QMessageBox::Save, "Oui");
        _retBox.setButtonText(QMessageBox::Discard, "Non");
        _retBox.setButtonText(QMessageBox::Cancel, "Annuler");
        ret = _retBox.exec();
        if(ret == QMessageBox::Save)
        {
            save();
        }
        else if(ret == QMessageBox::Discard)
        {

        }
        else
        {
            return;
        }
    }
    mNeedSave = false;
    setWindowTitle(QApplication::translate("MainWindow", "Project3Donut", 0));
    Scene::getScene()->clearScene();
    //refresh widget
    ui->widget->update();
}

void MainWindow::openlibfile()
{
    QSettings settings("settings.ini", QSettings::IniFormat);
    QString _dir = settings.value("General/libDir", QString("./resources/example")).toString();

    QString _qfile = QFileDialog::getOpenFileName(0, "Importer", _dir, "Modeles (*.obj *.ply)");
    std::string _file = _qfile.toStdString();
    int ret;
    if(_file!="")
    {
        QMessageBox _retBox(QMessageBox::Question, tr("Project3Donut"),
                                    tr("Souhaitez vous creer une copie du modèle dans le dossier du projet ?\n"),
                                    QMessageBox::Yes | QMessageBox::No, this);
        _retBox.setButtonText(QMessageBox::Yes, "Oui");
        _retBox.setButtonText(QMessageBox::No, "Non");
        ret = _retBox.exec();

        //now we computer the name of the object
        int _num=0;
        std::string  _num_name;
        std::string _name = _file.substr(_file.find_last_of('/')+1);
        _name = _name.substr(0,_name.find_last_of('.'));

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

        //we copy the file and set the path to local
        if (ret == QMessageBox::Yes) {
            QFile::copy(_qfile, QString((Scene::getScene()->getPath() + _file.substr(_file.find_last_of('/')+1)).c_str()));
            Scene::getScene()->getObject(_num_name)->setPath("#"+_file.substr(_file.find_last_of('/')+1));
        }
        //notify the window that a new change has yet to be saved
        newaction();
     }
}

void MainWindow::open()
{
    int ret;
    if(Scene::getScene()->hasName() && mNeedSave)
    {
        QMessageBox _retBox(QMessageBox::Question, tr("Project3Donut"),
                                    tr("Il y a des changements non enregistrés.\n"
                                       "Voulez vous enregistrer ces changements ?\n"),
                                    QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel,this);
        _retBox.setButtonText(QMessageBox::Save, "Oui");
        _retBox.setButtonText(QMessageBox::Discard, "Non");
        _retBox.setButtonText(QMessageBox::Cancel, "Annuler");
        ret = _retBox.exec();
        if(ret == QMessageBox::Save)
        {
            save();
        }
        else if(ret == QMessageBox::Discard)
        {

        }
        else
        {
            return;
        }
    }

    QString _qfile = QFileDialog::getOpenFileName(0, "Ouvrir", QString(), "Scene (*.xml)");
    if(_qfile!="")
    {
        Scene::getScene()->clearScene();
        Scene::getScene()->createScene(_qfile);
        std::string _winName = "Project3Donut - " + Scene::getScene()->getName();
        setWindowTitle(QApplication::translate("MainWindow", _winName.c_str(), 0));
        mNeedSave = false;
    }
}

void MainWindow::revertPreviousAction()
{
    Scene::getScene()->revertPreviousAction();
    ui->widget->update();
    newaction();
}

void MainWindow::save()
{
    if(!Scene::getScene()->hasName()){
        saveas();
    }
    else
    {
        std::string _path;
        std::string _name = Scene::getScene()->getName();
        _path = Scene::getScene()->getPath() +_name + ".xml";
        Scene::getScene()->saveScene(_path);
        std::string _winName = "Project3Donut - " + Scene::getScene()->getName();
        setWindowTitle(QApplication::translate("MainWindow", _winName.c_str(), 0));
        mNeedSave = false;
    }
}

void MainWindow::saveas()
{
    QString _qfile = QFileDialog::getSaveFileName(0, "Sauvegarder", QString(), "Scene (*.xml)");
    std::string _file = _qfile.toStdString();

    std::vector<std::string> _pathList;

    if(_file!="")
    {
        _pathList = Scene::getScene()->getLocalObjects();
        std::size_t _begin = _file.find_last_of('/') + 1;
        std::size_t _end = _file.find_last_of('.');

        if(_pathList.size()>0 && _file.substr(0,_begin)!=Scene::getScene()->getPath())
        {
            int ret;
            QMessageBox _retBox(QMessageBox::Question, tr("Project3Donut"),
                                        tr("Votre scene contient des objets sauvegardés dans le dossier du projet\nSouhaitez vous les copier dans le nouveau dossier ?\n"),
                                        QMessageBox::Yes | QMessageBox::No, this);
            _retBox.setButtonText(QMessageBox::Yes, "Oui");
            _retBox.setButtonText(QMessageBox::No, "Non");
            ret = _retBox.exec();

            std::string _localPath;
            std::string _realPath;
            std::string _newPath;

            if (ret == QMessageBox::Yes) {

                for (unsigned int i=0; i<_pathList.size();i++)
                {
                    _localPath = Scene::getScene()->getObject(_pathList[i])->getPath();
                    _realPath = Scene::getScene()->getPath() + _localPath.substr(_localPath.find_last_of('#') + 1);
                    _newPath = _file.substr(0,_begin) + _localPath.substr(_localPath.find_last_of('#') + 1);
                    QFile::copy(QString(_realPath.c_str()), QString(_newPath.c_str()));

                }
            }
            else
            {
                for (unsigned int i=0; i<_pathList.size();i++)
                {
                    _localPath = Scene::getScene()->getObject(_pathList[i])->getPath();
                    _realPath = Scene::getScene()->getPath() + _localPath.substr(_localPath.find_last_of('#') + 1);
                    Scene::getScene()->getObject(_pathList[i])->setPath(_realPath);
                }

            }

        }

        Scene::getScene()->saveScene(_file);
        Scene::getScene()->setName(_file.substr(_begin, _end-_begin));
        Scene::getScene()->setPath(_file.substr(0,_begin));
        std::string _winName = "Project3Donut - " + _file.substr(_begin, _end-_begin);
        setWindowTitle(QApplication::translate("MainWindow", _winName.c_str(), 0));
        mNeedSave = false;
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
    newaction();
}

void MainWindow::changeObjectColor(){
    QColor _colorRGB = QColorDialog::getColor(QColor(128, 128, 128), nullptr, "Choisir une couleur", QColorDialog::DontUseNativeDialog);
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

void MainWindow::notice()
{
    win_notice->show();
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

void MainWindow::newaction()
{
    if(Scene::getScene()->hasName())
    {
        mNeedSave = true;
        std::string _winName = "Project3Donut - " + Scene::getScene()->getName() + " *";
        setWindowTitle(QApplication::translate("MainWindow", _winName.c_str(), 0));
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    int ret;
    if(Scene::getScene()->hasName() && mNeedSave)
    {
        QMessageBox _retBox(QMessageBox::Question, tr("Project3Donut"),
                                    tr("Il y a des changements non enregistrés.\n"
                                       "Voulez vous enregistrer ces changements ?\n"),
                                    QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel,this);
        _retBox.setButtonText(QMessageBox::Save, "Sauvegarder");
        _retBox.setButtonText(QMessageBox::Discard, "Quitter sans sauvegarder");
        _retBox.setButtonText(QMessageBox::Cancel, "Annuler");
        ret = _retBox.exec();
        if(ret == QMessageBox::Save)
        {
            save();
            event->accept();
        }
        else if(ret == QMessageBox::Discard)
        {
            event->accept();
        }
        else
        {
            event->ignore();
        }
    }
    else
    {
        QMessageBox _retBox(QMessageBox::Question, tr("Project3Donut"),
                                    tr("Etes-vous sûr de vouloir quitter ?\n"),
                                    QMessageBox::Yes | QMessageBox::No, this);
        _retBox.setButtonText(QMessageBox::Yes, "Oui");
        _retBox.setButtonText(QMessageBox::No, "Non");
        ret = _retBox.exec();
        if (ret == QMessageBox::Yes) {
            event->accept();
        }
        else{
            event->ignore();
        }
    }
}
