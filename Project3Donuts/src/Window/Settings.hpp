#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include "ui_settings.h"

class Settings: public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = 0);
    ~Settings();
    Ui::Dialog *ui;
public slots:
    void changecolor();
};

#endif // SETTINGS_HPP
