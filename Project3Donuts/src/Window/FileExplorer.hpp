#ifndef FILEEXPLORER_HPP
#define FILEEXPLORER_HPP

#include <QMainWindow>
#include <QFileSystemModel>

namespace Ui {
class FileExplorer;
}


class FileExplorer: public QMainWindow
{
    Q_OBJECT

public:
    FileExplorer(QWidget *parent = 0);
    ~FileExplorer();
    Ui::FileExplorer *ui;

private:
    QFileSystemModel *fileModel;
    QString mCurrentPath;
    QString mValidPath;

private slots:
    void on_listView_clicked(const QModelIndex &index);
    void button_ok_create_selected();
    void actionGetParent();
    //void actionCreateDirectory();
};

#endif // FILEEXPLORER_HPP
