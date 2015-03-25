#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include "ui_about.h"
#include "ui_notice.h"
#include "Settings.hpp"

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
   void revertPreviousAction();
   void openlibfile();
   void open();
   void save();
   void saveas();

   void selectObject(const QModelIndex &index);
   void deleteSelectedObject();

   void changeObjectColor();
   void invertwidgets();

   void editsettings();
   void about();
   void notice();

   void checkSettings(int);
   void changeModeToTranslate();
   void changeModeToRotate();
   void changeModeToScale();

   void newaction();

private:
   bool mNeedSave;
   QMainWindow * win_about;
   QMainWindow * win_notice;
   Settings * _settingsWindow;
   Ui::About* _about_ui;
   Ui::Notice* _notice_ui;

protected:
   void closeEvent(QCloseEvent *event);

};
#endif // MAINWINDOW_HPP
