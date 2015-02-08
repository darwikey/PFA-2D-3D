/********************************************************************************
** Form generated from reading UI file 'fileexplorer.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef FILEEXPLORER_H
#define FILEEXPLORER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_fileexplorer
{
public:
    QAction *actionGetParent;
    QAction *actionCreateDirectory;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QListView *listView;
    QDialogButtonBox *buttonBox;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(691, 520);
        actionGetParent = new QAction(MainWindow);
        actionGetParent->setObjectName(QStringLiteral("actionGetParent"));
        /* Keep for save as
        actionCreateDirectory = new QAction(MainWindow);
        actionCreateDirectory->setObjectName(QStringLiteral("New Directory"));
        * */
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        listView = new QListView(centralwidget);
        listView->setObjectName(QStringLiteral("listView"));

        verticalLayout->addWidget(listView);

        buttonBox = new QDialogButtonBox(centralwidget);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        verticalLayout_2->addLayout(verticalLayout);

        MainWindow->setCentralWidget(centralwidget);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        toolBar->addAction(actionGetParent);
		//toolBar->addAction(actionCreateDirectory);
		
        retranslateUi(MainWindow);
        QObject::connect(listView, SIGNAL(clicked(QModelIndex)), MainWindow, SLOT(on_listView_clicked(QModelIndex)));
        QObject::connect(buttonBox, SIGNAL(accepted()), MainWindow, SLOT(button_ok_create_selected()));
        QObject::connect(actionGetParent, SIGNAL(triggered()), MainWindow, SLOT(actionGetParent()));
        //QObject::connect(actionCreateDirectory, SIGNAL(triggered()), MainWindow, SLOT(actionCreateDirectory()));
        QObject::connect(buttonBox, SIGNAL(rejected()), MainWindow, SLOT(close()));
        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "File Explorer", 0));
        actionGetParent->setText(QApplication::translate("MainWindow", "Parent", 0));
        actionGetParent->setShortcut(QApplication::translate("MainWindow", "Backspace", 0));
        //actionCreateDirectory->setText(QApplication::translate("MainWindow", "New Directory", 0));
        //actionCreateDirectory->setShortcut(QApplication::translate("MainWindow", "Backspace", 0));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0));
    } // retranslateUi

};

namespace Ui {
    class FileExplorer: public Ui_fileexplorer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // FILEEXPLORER_H
