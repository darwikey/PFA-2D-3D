#ifndef QFILESYSTEMMODELDIALOG_HPP
#define QFILESYSTEMMODELDIALOG_HPP

#include <QDialog>
#include <QFileSystemModel>

namespace Ui {
class QFileSystemModelDialog;
}

class QFileSystemModelDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QFileSystemModelDialog(QWidget *parent = 0);
    ~QFileSystemModelDialog();

private slots:
    void on_treeView_clicked(const QModelIndex &index);
    void on_listView_clicked(const QModelIndex &index);
    void button_ok_create_selected();

private:
    Ui::QFileSystemModelDialog *ui;

    // Make two models instead of one
    // to filter them separately
    QFileSystemModel *dirModel;
    QFileSystemModel *fileModel;
    QString mCurrentPath;
    QString mValidPath;
};

#endif // QFILESYSTEMMODELDIALOG_HPP
