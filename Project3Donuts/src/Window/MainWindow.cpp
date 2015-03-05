#include "MainWindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QStringListModel* modelList = Scene::getScene()->getListObjects();
    printf("count : %d\n", modelList->rowCount());
    ui->listView->setModel(modelList);
    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //ui->listView->setSelectionMode(QAbstractItemView::MultiSelection );
    ui->listView->installEventFilter(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openfile()
{
    mOpen.show();

}

void MainWindow::selectObject(const QModelIndex &index)
{
    QModelIndexList localList =ui->listView->selectionModel()->selectedIndexes();
    QStringList stringList;
    foreach(const QModelIndex &index, localList){
        stringList.append( index.data(Qt::DisplayRole ).toString());
    }

    Scene::getScene()->selectObjectsByName(stringList);
    //refresh widget
    ui->widget->setFocus();
    //come back to the list
    ui->listView->setFocus();
}


bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{

    if(event->type() == QEvent::KeyPress)
    {
        QKeyEvent *ke = static_cast<QKeyEvent*>(event);
        if(ke->key() == Qt::Key_Return)
        {

             /*not working edit failed error
            QModelIndex index = ui->listView->currentIndex();

            std::string old_name = index.data(Qt::DisplayRole).toString().toStdString();
            ui->listView->edit(index);
            std::string new_name = index.data(Qt::DisplayRole ).toString().toStdString();
            std::cout<<new_name<<std::endl;
            Scene::getScene()->mapChange_Key(old_name, new_name);
            */
            return true;
        }

    }
return false;
}
void MainWindow::invertwidgets()
{
    if(ui->actionInverser_les_positions_des_fen_tres->isChecked())
    {
        QSplitter *splitter = ui->splitter;
        ui->splitter = new QSplitter(ui->centralwidget);
        ui->splitter->setObjectName(QStringLiteral("splitter"));
        ui->splitter->setOrientation(Qt::Horizontal);
        ui->listView->setParent(ui->splitter);
        ui->widget->setParent(ui->splitter);
        QList<int> sizes;
        sizes.append(182);
        sizes.append(600);

        ui->splitter->setSizes(sizes);
        ui->horizontalLayout->addWidget(ui->splitter);
        delete splitter;
    }
    else
    {
        QSplitter *splitter = ui->splitter;
        ui->splitter = new QSplitter(ui->centralwidget);
        ui->splitter->setObjectName(QStringLiteral("splitter"));
        ui->splitter->setOrientation(Qt::Horizontal);
        ui->widget->setParent(ui->splitter);
        ui->listView->setParent(ui->splitter);
        QList<int> sizes;
        sizes.append(600);
        sizes.append(182);
        ui->splitter->setSizes(sizes);
        ui->horizontalLayout->addWidget(ui->splitter);

        delete splitter;
    }
}
