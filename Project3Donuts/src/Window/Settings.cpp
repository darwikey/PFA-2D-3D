#include "Settings.hpp"
#include <QColorDialog>

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Settings::~Settings()
{
    delete ui;
}

void Settings::changecolor()
{
    QColor color;
        color = QColorDialog::getColor(Qt::green, this, "Select Color", QColorDialog::DontUseNativeDialog);

    if (color.isValid()) {
        ui->colorLabel->setPalette(QPalette(color));
        ui->colorLabel->setAutoFillBackground(true);
    }

}
