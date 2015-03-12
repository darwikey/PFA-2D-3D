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
}

void Settings::generaltodefault()
{
    int ret = QMessageBox::question(this, tr("Project3Donut"),
                                   tr("Etes vous sûr de vouloir restaurer les valeurs par défauts ?\n"),
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
