#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include "FileExplorer.hpp"

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

private:
    FileExplorer mOpen;

public slots:
   void openfile();
   void selectObject(const QModelIndex &index);
};
#endif // MAINWINDOW_HPP
