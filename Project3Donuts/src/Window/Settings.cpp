#include "Settings.hpp"
#include <QColorDialog>
#include "Scene.hpp"
#include "SceneRenderer.hpp"

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    setWindowModality (Qt::ApplicationModal);
}

Settings::~Settings()
{
    delete ui;
}

void Settings::changecolor()
{
    QColor _color = QColorDialog::getColor(Qt::green, this, "Select Color", QColorDialog::DontUseNativeDialog);

    if (_color.isValid()) {
        ui->colorLabel->setPalette(QPalette(_color));
        ui->colorLabel->setAutoFillBackground(true);
    }

}

void Settings::editparameters()
{
    QSettings settings("settings.ini", QSettings::IniFormat);

    //resolution
    settings.setValue("General/prog_x",ui->ResBox_x->value());
    settings.setValue("General/prog_y",ui->ResBox_y->value());

    //window position
    settings.setValue("General/invertedwindows",ui->WindowBox->isChecked());

    //background color
    QColor _color = ui->colorLabel->palette().color(QPalette::Window);
    settings.setValue("Viewer/background_color",_color);
    Scene::getScene()->getSceneRenderer()->ChangeBackground(_color);

    //shortcuts
    settings.setValue("Shortcuts/render", ui->ColorMap_keySequenceEdit->keySequence());
    settings.setValue("Shortcuts/anaglyphes", ui->Anaglyphe_keySequenceEdit->keySequence());
    settings.setValue("Shortcuts/autostereogramme", ui->AutoStereogramme_keySequenceEdit->keySequence());
    settings.setValue("Shortcuts/flipbook", ui->Flipbook_keySequenceEdit->keySequence());
    settings.setValue("Shortcuts/translate", ui->Translate_keySequenceEdit->keySequence());
    settings.setValue("Shortcuts/rotate", ui->Rotate_keySequenceEdit->keySequence());
    settings.setValue("Shortcuts/scale", ui->Scale_keySequenceEdit->keySequence());

}

void Settings::resetparameters()
{
    QSettings settings("settings.ini", QSettings::IniFormat);

    //resolution
    ui->ResBox_x->setValue(settings.value("General/prog_x", 782).toInt());
    ui->ResBox_y->setValue(settings.value("General/prog_y", 486).toInt());

    //window position
    ui->WindowBox->setChecked(settings.value("General/invertedwindows",false).toBool());

    //background color
    ui->colorLabel->setPalette(QPalette(settings.value("Viewer/background_color",QColor(0,0,102)).value<QColor>()));

    //shortcuts
    ui->ColorMap_keySequenceEdit->setKeySequence(settings.value("Shortcuts/render", QKeySequence("P")).value<QKeySequence>());
    ui->Anaglyphe_keySequenceEdit->setKeySequence(settings.value("Shortcuts/anaglyphes", QKeySequence("N")).value<QKeySequence>());
    ui->AutoStereogramme_keySequenceEdit->setKeySequence(settings.value("Shortcuts/autostereogramme", QKeySequence("U")).value<QKeySequence>());
    ui->Flipbook_keySequenceEdit->setKeySequence(settings.value("Shortcuts/flipbook",QKeySequence("F")).value<QKeySequence>());
    ui->Translate_keySequenceEdit->setKeySequence(settings.value("Shortcuts/translate",QKeySequence("T")).value<QKeySequence>());
    ui->Rotate_keySequenceEdit->setKeySequence(settings.value("Shortcuts/rotate",QKeySequence("R")).value<QKeySequence>());
    ui->Scale_keySequenceEdit->setKeySequence(settings.value("Shortcuts/scale",QKeySequence("S")).value<QKeySequence>());
}

void Settings::generaltodefault()
{
    int ret = QMessageBox::question(this, tr("Project3Donut"),
                                   tr("Etes vous sûr de vouloir restaurer les valeurs par défaut ?\n"),
                                   QMessageBox::Yes | QMessageBox::No);
    switch (ret) {
      case QMessageBox::No:
          break;
      case QMessageBox::Yes:

        //resolution
        ui->ResBox_x->setValue(782);
        ui->ResBox_y->setValue(486);

        //window position
        ui->WindowBox->setChecked(false);

        //background color
        ui->colorLabel->setPalette(QColor(0,0,102));

        break;
      default:
        break;
    }

}

void Settings::shortcutstodefault()
{
    int ret = QMessageBox::question(this, tr("Project3Donut"),
                                   tr("Etes vous sûr de vouloir restaurer les raccourcis par défaut ?\n"),
                                   QMessageBox::Yes | QMessageBox::No);
    switch (ret) {
      case QMessageBox::No:
          break;
      case QMessageBox::Yes:
        ui->ColorMap_keySequenceEdit->setKeySequence(QKeySequence("P"));
        ui->Anaglyphe_keySequenceEdit->setKeySequence(QKeySequence("N"));
        ui->AutoStereogramme_keySequenceEdit->setKeySequence(QKeySequence("U"));
        ui->Flipbook_keySequenceEdit->setKeySequence(QKeySequence("F"));
        ui->Translate_keySequenceEdit->setKeySequence(QKeySequence("T"));
        ui->Rotate_keySequenceEdit->setKeySequence(QKeySequence("R"));
        ui->Scale_keySequenceEdit->setKeySequence(QKeySequence("S"));
        break;
      default:
        break;
    }
}
