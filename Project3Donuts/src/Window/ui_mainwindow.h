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
#include <QtWidgets/QSplitter>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include <QGLWidget>
#include "SceneRenderer.hpp"
#include "Scene.hpp"


QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOuvrir;
    QAction *actionQuitter;
    QAction *actionDegrader;
    QAction *actionNouveau;
    QAction *actionEnregistrer;
    QAction *actionEnregister_sous;
    QAction *actionDepuis_la_bibliotheque;
    QAction *actionDepuis_le_disque_dur;
    QAction *actionPr_f_rences;
    QAction *actionA_propos;
    QAction *actionEffectuer_un_rendu;
    QAction *actionAfficher_la_carte_de_profondeur;
	QAction *actionAnaglyphes;
    QAction *actionAuto_st_r_ogrammes;
    QAction *actionFlipbook;
    QAction *actionInverser_les_positions_des_fen_tres;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
	
	QSplitter *splitter;
    SceneRenderer *widget;
    QListView *listView;
    QMenuBar *menubar;
    QMenu *menuFichier;
    QMenu *menuImporter;
    QMenu *menuEditer;
    QMenu *menuAide;
    QMenu *menuOutils;
    QMenu *menuFen_tre;
    QToolBar *toolBar;
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
        actionNouveau = new QAction(MainWindow);
        actionNouveau->setObjectName(QStringLiteral("actionNouveau"));
        actionEnregistrer = new QAction(MainWindow);
        actionEnregistrer->setObjectName(QStringLiteral("actionEnregistrer"));
        actionEnregister_sous = new QAction(MainWindow);
        actionEnregister_sous->setObjectName(QStringLiteral("actionEnregister_sous"));
        actionDepuis_la_bibliotheque = new QAction(MainWindow);
        actionDepuis_la_bibliotheque->setObjectName(QStringLiteral("actionDepuis_la_bibliotheque"));
        actionDepuis_le_disque_dur = new QAction(MainWindow);
        actionDepuis_le_disque_dur->setObjectName(QStringLiteral("actionDepuis_le_disque_dur"));
        actionPr_f_rences = new QAction(MainWindow);
        actionPr_f_rences->setObjectName(QStringLiteral("actionPr_f_rences"));
        actionA_propos = new QAction(MainWindow);
        actionA_propos->setObjectName(QStringLiteral("actionA_propos"));
        actionEffectuer_un_rendu = new QAction(MainWindow);
        actionEffectuer_un_rendu->setObjectName(QStringLiteral("actionEffectuer_un_rendu"));
        actionAfficher_la_carte_de_profondeur = new QAction(MainWindow);
        actionAfficher_la_carte_de_profondeur->setObjectName(QStringLiteral("actionAfficher_la_carte_de_profondeur"));
        actionInverser_les_positions_des_fen_tres = new QAction(MainWindow);
        actionInverser_les_positions_des_fen_tres->setObjectName(QStringLiteral("actionInverser_les_positions_des_fen_tres"));
        actionInverser_les_positions_des_fen_tres->setCheckable(true);
        actionAnaglyphes = new QAction(MainWindow);
        actionAnaglyphes->setObjectName(QStringLiteral("actionAnaglyphes"));
        actionAuto_st_r_ogrammes = new QAction(MainWindow);
        actionAuto_st_r_ogrammes->setObjectName(QStringLiteral("actionAuto_st_r_ogrammes"));
        actionFlipbook = new QAction(MainWindow);
        actionFlipbook->setObjectName(QStringLiteral("actionFlipbook"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        splitter = new QSplitter(centralwidget);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Horizontal);		
        widget = new SceneRenderer(splitter);
        widget->setObjectName(QStringLiteral("widget"));
		QList<int> sizes;
		sizes.append(600);
		sizes.append(182);
		splitter->setSizes(sizes);

        splitter->addWidget(widget);

        listView = new QListView(splitter);
        listView->setObjectName(QStringLiteral("listView"));

        horizontalLayout->addWidget(splitter);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 782, 21));
        menuFichier = new QMenu(menubar);
        menuFichier->setObjectName(QStringLiteral("menuFichier"));
        menuImporter = new QMenu(menuFichier);
        menuImporter->setObjectName(QStringLiteral("menuImporter"));
        menuEditer = new QMenu(menubar);
        menuEditer->setObjectName(QStringLiteral("menuEditer"));
        menuAide = new QMenu(menubar);
        menuAide->setObjectName(QStringLiteral("menuAide"));
        menuOutils = new QMenu(menubar);
        menuOutils->setObjectName(QStringLiteral("menuOutils"));
        menuFen_tre = new QMenu(menubar);
        menuFen_tre->setObjectName(QStringLiteral("menuFen_tre"));
        MainWindow->setMenuBar(menubar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);
        menubar->addAction(menuFichier->menuAction());
        menubar->addAction(menuEditer->menuAction());
        menubar->addAction(menuOutils->menuAction());
        menubar->addAction(menuFen_tre->menuAction());
        menubar->addAction(menuAide->menuAction());
        menuFichier->addAction(actionNouveau);
        menuFichier->addAction(actionOuvrir);
        menuFichier->addAction(menuImporter->menuAction());
        menuFichier->addAction(actionEnregistrer);
        menuFichier->addAction(actionEnregister_sous);
        menuFichier->addAction(actionQuitter);
        menuImporter->addAction(actionDepuis_la_bibliotheque);
        menuImporter->addAction(actionDepuis_le_disque_dur);
        menuEditer->addAction(actionPr_f_rences);
        menuAide->addAction(actionA_propos);
        menuOutils->addAction(actionEffectuer_un_rendu);
        menuOutils->addAction(actionAfficher_la_carte_de_profondeur);
		menuOutils->addAction(actionAnaglyphes);
        menuOutils->addAction(actionAuto_st_r_ogrammes);
        menuOutils->addAction(actionFlipbook);
        menuFen_tre->addAction(actionInverser_les_positions_des_fen_tres);
		
        retranslateUi(MainWindow);
        QObject::connect(actionQuitter, SIGNAL(triggered()), MainWindow, SLOT(close()));
        QObject::connect(actionDepuis_le_disque_dur, SIGNAL(triggered()), MainWindow, SLOT(openfile()));		
        QObject::connect(listView, SIGNAL(doubleClicked(QModelIndex)), MainWindow, SLOT(selectObject(QModelIndex)));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionOuvrir->setText(QApplication::translate("MainWindow", "Ouvrir", 0));
        actionQuitter->setText(QApplication::translate("MainWindow", "Quitter", 0));

        actionNouveau->setText(QApplication::translate("MainWindow", "Nouveau", 0));
        actionEnregistrer->setText(QApplication::translate("MainWindow", "Enregistrer", 0));
        actionEnregister_sous->setText(QApplication::translate("MainWindow", "Enregister sous", 0));
        actionDepuis_la_bibliotheque->setText(QApplication::translate("MainWindow", "depuis la bibliotheque", 0));
        actionDepuis_le_disque_dur->setText(QApplication::translate("MainWindow", "depuis le disque dur", 0));
        actionPr_f_rences->setText(QApplication::translate("MainWindow", "Pr\303\251f\303\251rences", 0));
        actionA_propos->setText(QApplication::translate("MainWindow", "A propos", 0));
        actionEffectuer_un_rendu->setText(QApplication::translate("MainWindow", "Effectuer un rendu", 0));
        actionAfficher_la_carte_de_profondeur->setText(QApplication::translate("MainWindow", "Afficher la carte de profondeur", 0));
        actionInverser_les_positions_des_fen_tres->setText(QApplication::translate("MainWindow", "Inverser les positions des fen\303\252tres", 0));
        actionAnaglyphes->setText(QApplication::translate("MainWindow", "Anaglyphes", 0));
        actionAuto_st_r_ogrammes->setText(QApplication::translate("MainWindow", "Autost\303\251r\303\251ogrammes", 0));
        actionFlipbook->setText(QApplication::translate("MainWindow", "flipbook", 0));
        menuFichier->setTitle(QApplication::translate("MainWindow", "Fichier", 0));
        menuImporter->setTitle(QApplication::translate("MainWindow", "Importer", 0));
        menuEditer->setTitle(QApplication::translate("MainWindow", "Editer", 0));
        menuAide->setTitle(QApplication::translate("MainWindow", "Aide", 0));
        menuOutils->setTitle(QApplication::translate("MainWindow", "Outils", 0));
        menuFen_tre->setTitle(QApplication::translate("MainWindow", "Fen\303\252tres", 0));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
