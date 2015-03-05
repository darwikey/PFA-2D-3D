#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include "ui_about.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Ui::MainWindow *ui;

public slots:
   void newscene();
   void openfile();
   void openlibfile();
   void open();
   void save();
   void saveas();

   void selectObject(const QModelIndex &index);
   void invertwidgets();

   void editsettings();
   void about();

private:
   QMainWindow * win_about;
   Ui::About* _about_ui;

};
#endif // MAINWINDOW_HPP
