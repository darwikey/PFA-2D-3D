#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include "ui_settings.h"

//! \class Settings
//! \brief Settings (persistent parameters to reboot) window.
class Settings: public QDialog
{
    Q_OBJECT

public:
    //! \brief Constructor, setup the window using auto-generated code.
    explicit Settings(QWidget *parent = 0);

    ~Settings();
    Ui::Dialog *ui;
public slots:
    //! \brief Call the select a color window.
    void changecolor();

    //! \brief Change the settings in the ini file.
    void editparameters();

    //! \brief Reset the window with the parameters given in the ini file.
    void resetparameters();

    //! \brief Reset the first tab of the window with the default parameters.
    void generaltodefault();

    //! \brief Reset the second tab of the window with the default parameters.
    void shortcutstodefault();

    //! \brief Call the browse directories window to select a path.
    void browsedirectories();
};

#endif // SETTINGS_HPP
