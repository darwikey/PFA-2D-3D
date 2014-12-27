/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include "MainWindow.hpp"
#include "QFileSystemModelDialog.hpp"

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QWidget>
#include <QGLWidget>


QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOuvrir;
    QAction *actionQuitter;
    QAction *actionDegrader;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QListView *listView;
    QMenuBar *menubar;
    QMenu *menuFichier;
    QMenu *menuEditer;

    void setupUi(MainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(782, 486);
        actionOuvrir = new QAction(MainWindow);
        actionOuvrir->setObjectName(QStringLiteral("actionOuvrir"));
        actionOuvrir->setMenuRole(QAction::ApplicationSpecificRole);
        actionQuitter = new QAction(MainWindow);
        actionQuitter->setObjectName(QStringLiteral("actionQuitter"));
        actionDegrader = new QAction(MainWindow);
        actionDegrader->setObjectName(QStringLiteral("actionDegrader"));
        actionDegrader->setCheckable(true);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        /*widget = QWidget::createWindowContainer(new SceneRenderer(),centralwidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setMinimumSize(QSize(600, 0));

        horizontalLayout->addWidget(widget);*/

        listView = new QListView(centralwidget);
        listView->setObjectName(QStringLiteral("listView"));
        listView->setMaximumSize(QSize(228, 16777215));

        horizontalLayout->addWidget(listView);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 782, 21));
        menuFichier = new QMenu(menubar);
        menuFichier->setObjectName(QStringLiteral("menuFichier"));
        menuEditer = new QMenu(menubar);
        menuEditer->setObjectName(QStringLiteral("menuEditer"));
        MainWindow->setMenuBar(menubar);

        menubar->addAction(menuFichier->menuAction());
        menubar->addAction(menuEditer->menuAction());
        menuFichier->addAction(actionOuvrir);
        menuFichier->addAction(actionQuitter);
        menuEditer->addAction(actionDegrader);

        retranslateUi(MainWindow);
        QObject::connect(actionQuitter, SIGNAL(triggered()), MainWindow, SLOT(close()));
        QObject::connect(actionOuvrir, SIGNAL(triggered()), MainWindow, SLOT(openfile()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionOuvrir->setText(QApplication::translate("MainWindow", "Ouvrir", 0));
        actionQuitter->setText(QApplication::translate("MainWindow", "Quitter", 0));
        actionDegrader->setText(QApplication::translate("MainWindow", "Degrader", 0));
        menuFichier->setTitle(QApplication::translate("MainWindow", "Fichier", 0));
        menuEditer->setTitle(QApplication::translate("MainWindow", "Editer", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
