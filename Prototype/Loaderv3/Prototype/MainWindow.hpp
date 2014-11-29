#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include "QFileSystemModelDialog.hpp"
#include "singleton.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, public Singleton<MainWindow>
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Ui::MainWindow *ui;

private:
    QFileSystemModelDialog mOpen;

public slots:
   void openfile();
};

#endif // MAINWINDOW_HPP
