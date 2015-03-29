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
#include <QSettings>
#include "SceneRenderer.hpp"
#include "Scene.hpp"
#include "Creator.hpp"


QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOuvrir;
    QAction *actionQuitter;
    QAction *actionDegrader;
    QAction *actionNouveau;
    QAction *actionEnregistrer;
    QAction *actionEnregistrer_sous;
    QAction * actionUndo;

    QAction *actionDepuis_la_bibliotheque;
    QAction *actionDepuis_le_disque_dur;
	QAction* action_changer_couleur;
    QAction *actionPr_f_rences;
    QAction *actionA_propos;
    QAction *actionNotice_utilisation;
    QAction *actionEffectuer_un_rendu;
	QAction *actionAnaglyphes;
    QAction *actionAuto_st_r_ogrammes;
    QAction *actionFlipbook;
    QAction *actionInverser_les_positions_des_fen_tres;

	QAction * actionTranslate;
    QAction * actionRotate;
    QAction * actionScale;
    QAction * transCamZero;

    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
	
	QSplitter *splitter;
    SceneRenderer *widget;
    QListView *listView;
    QAction * deleteObject;
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
            
        QSettings settings("settings.ini", QSettings::IniFormat);    
        
        int res_x = settings.value("General/prog_x", 0).toInt();
        if(res_x == 0)
        {
			settings.setValue("General/prog_x",782);
			res_x=782;
		}
		
        int res_y = settings.value("General/prog_y", 0).toInt();
        if(res_y == 0)
        {
			settings.setValue("General/prog_y",486);
			res_y=486;
		}
        
        MainWindow->resize(res_x, res_y);

        QCommonStyle* windowStyle = new QCommonStyle;


        actionOuvrir = new QAction(MainWindow);
        actionOuvrir->setObjectName(QStringLiteral("actionOuvrir"));
        actionOuvrir->setMenuRole(QAction::ApplicationSpecificRole);
        actionOuvrir->setShortcut(QKeySequence::Open);
        actionOuvrir->setIcon(windowStyle->standardIcon(QStyle::SP_DialogOpenButton));
        
        actionQuitter = new QAction(MainWindow);
        actionQuitter->setObjectName(QStringLiteral("actionQuitter"));
        actionQuitter->setShortcut(QKeySequence::Quit);
        
        actionNouveau = new QAction(MainWindow);
        actionNouveau->setObjectName(QStringLiteral("actionNouveau"));
        actionNouveau->setShortcut(QKeySequence::New);
        QIcon icon_new;
        icon_new.addFile(QStringLiteral("resources/icones/icone_nouveau.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNouveau->setIcon(icon_new);
        
        actionEnregistrer = new QAction(MainWindow);
        actionEnregistrer->setObjectName(QStringLiteral("actionEnregistrer"));
        actionEnregistrer->setShortcut(QKeySequence::Save);
        actionEnregistrer->setIcon(windowStyle->standardIcon(QStyle::SP_DialogSaveButton));
        
        actionEnregistrer_sous = new QAction(MainWindow);
        actionEnregistrer_sous->setObjectName(QStringLiteral("actionEnregistrer_sous"));
        actionEnregistrer_sous->setShortcut(QKeySequence::SaveAs);
        
        actionUndo = new QAction(MainWindow);
        actionUndo->setObjectName(QStringLiteral("actionUndo"));
        actionUndo->setShortcut(QKeySequence::Undo);
        actionUndo->setIcon(windowStyle->standardIcon(QStyle::SP_FileDialogBack));

        actionDepuis_la_bibliotheque = new QAction(MainWindow);
        actionDepuis_la_bibliotheque->setObjectName(QStringLiteral("actionDepuis_la_bibliotheque"));
        actionDepuis_la_bibliotheque->setShortcut(QKeySequence("CTRL+I"));
        actionDepuis_la_bibliotheque->setIcon(windowStyle->standardIcon(QStyle::SP_DirHomeIcon));
        
        actionDepuis_le_disque_dur = new QAction(MainWindow);
        actionDepuis_le_disque_dur->setObjectName(QStringLiteral("actionDepuis_le_disque_dur"));
        actionDepuis_le_disque_dur->setShortcut(settings.value("Shortcuts/import",QKeySequence("I")).value<QKeySequence>());
        
        action_changer_couleur = new QAction(MainWindow);
        action_changer_couleur->setObjectName(QStringLiteral("action_changer_couleur"));
		
        actionPr_f_rences = new QAction(MainWindow);
        actionPr_f_rences->setObjectName(QStringLiteral("actionPr_f_rences"));
        actionPr_f_rences->setShortcut(QKeySequence::Preferences);
        
        actionA_propos = new QAction(MainWindow);
        actionA_propos->setObjectName(QStringLiteral("actionA_propos"));

        actionNotice_utilisation = new QAction(MainWindow);
        actionNotice_utilisation->setObjectName(QStringLiteral("actionNotice_utilisation"));
        actionNotice_utilisation->setShortcut(QKeySequence::HelpContents);
        
        actionEffectuer_un_rendu = new QAction(MainWindow);
        actionEffectuer_un_rendu->setObjectName(QStringLiteral("actionEffectuer_un_rendu"));
        actionEffectuer_un_rendu->setShortcut(settings.value("Shortcuts/render",QKeySequence("P")).value<QKeySequence>());
        QIcon icon_color;
        icon_color.addFile(QStringLiteral("resources/icones/base_donut.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionEffectuer_un_rendu->setIcon(icon_color);
        
        actionInverser_les_positions_des_fen_tres = new QAction(MainWindow);
        actionInverser_les_positions_des_fen_tres->setObjectName(QStringLiteral("actionInverser_les_positions_des_fen_tres"));
        actionInverser_les_positions_des_fen_tres->setCheckable(true);
        
        actionAnaglyphes = new QAction(MainWindow);
        actionAnaglyphes->setObjectName(QStringLiteral("actionAnaglyphes"));
        actionAnaglyphes->setShortcut(settings.value("Shortcuts/anaglyphes",QKeySequence("N")).value<QKeySequence>());
        QIcon icon_anagl;
        icon_anagl.addFile(QStringLiteral("resources/icones/icone_anaglyphe.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAnaglyphes->setIcon(icon_anagl);
        
        actionAuto_st_r_ogrammes = new QAction(MainWindow);
        actionAuto_st_r_ogrammes->setObjectName(QStringLiteral("actionAuto_st_r_ogrammes"));
        actionAuto_st_r_ogrammes->setShortcut(settings.value("Shortcuts/autostereogramme",QKeySequence("U")).value<QKeySequence>());
        QIcon icon_auto;
        icon_auto.addFile(QStringLiteral("resources/icones/icone_autostereogramme.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAuto_st_r_ogrammes->setIcon(icon_auto);
        
        actionFlipbook = new QAction(MainWindow);
        actionFlipbook->setObjectName(QStringLiteral("actionFlipbook"));
        actionFlipbook->setShortcut(settings.value("Shortcuts/flipbook",QKeySequence("F")).value<QKeySequence>());
        QIcon icon_flip;
        icon_flip.addFile(QStringLiteral("resources/icones/icone_flipbook.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionFlipbook->setIcon(icon_flip);
        
        actionTranslate = new QAction(MainWindow);
        actionTranslate->setObjectName(QStringLiteral("actionTranslate"));
        actionTranslate->setCheckable(true);
        actionTranslate->setShortcut(settings.value("Shortcuts/translate",QKeySequence("T")).value<QKeySequence>());
        QIcon icon_t;
        icon_t.addFile(QStringLiteral("resources/icones/icone_transl.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionTranslate->setIcon(icon_t);
        
        actionRotate = new QAction(MainWindow);
        actionRotate->setObjectName(QStringLiteral("actionRotate"));
        actionRotate->setCheckable(true);
        actionRotate->setShortcut(settings.value("Shortcuts/rotate",QKeySequence("R")).value<QKeySequence>());
        QIcon icon_r;
        icon_r.addFile(QStringLiteral("resources/icones/icone_rotation.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRotate->setIcon(icon_r);
        
        actionScale = new QAction(MainWindow);
        actionScale->setObjectName(QStringLiteral("actionScale"));
        actionScale->setCheckable(true);
        actionScale->setShortcut(settings.value("Shortcuts/scale",QKeySequence("S")).value<QKeySequence>());
        QIcon icon_s;
        icon_s.addFile(QStringLiteral("resources/icones/icone_scale.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionScale->setIcon(icon_s);

        transCamZero = new QAction(MainWindow);
        transCamZero->setObjectName(QStringLiteral("transCamZero"));
        transCamZero->setShortcut(settings.value("Shortcuts/cam_zero",QKeySequence("Z")).value<QKeySequence>());

        
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        splitter = new QSplitter(centralwidget);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Horizontal);		
        widget = new SceneRenderer(splitter);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setParentWindow(MainWindow);
		QList<int> sizes;
		sizes.append(600);
		sizes.append(182);
		splitter->setSizes(sizes);

        splitter->addWidget(widget);

        listView = new QListView(splitter);
        listView->setObjectName(QStringLiteral("listView"));


        deleteObject = new QAction(listView);
        deleteObject->setObjectName(QStringLiteral("deleteObject"));
        deleteObject->setShortcut(QKeySequence::Delete);
        deleteObject->setShortcutContext(Qt::WidgetShortcut);

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
        menuFichier->addAction(actionEnregistrer_sous);
        menuFichier->addAction(actionQuitter);
        menuImporter->addAction(actionDepuis_la_bibliotheque);
        menuImporter->addAction(actionDepuis_le_disque_dur);
		menuEditer->addAction(action_changer_couleur);
		menuEditer->addAction(actionPr_f_rences);
        menuAide->addAction(actionA_propos);
        menuAide->addAction(actionNotice_utilisation);
        menuOutils->addAction(actionEffectuer_un_rendu);
		menuOutils->addAction(actionAnaglyphes);
        menuOutils->addAction(actionAuto_st_r_ogrammes);
        menuOutils->addAction(actionFlipbook);
        menuFen_tre->addAction(actionInverser_les_positions_des_fen_tres);
        toolBar->addAction(actionNouveau);
        toolBar->addAction(actionOuvrir);
        toolBar->addAction(actionDepuis_la_bibliotheque);
        toolBar->addAction(actionEnregistrer);
        toolBar->addSeparator();
        toolBar->addAction(actionUndo);
        toolBar->addSeparator();
        toolBar->addAction(actionTranslate);
        toolBar->addAction(actionRotate);
        toolBar->addAction(actionScale);
        toolBar->addSeparator();
        toolBar->addAction(actionEffectuer_un_rendu);
        toolBar->addAction(actionAnaglyphes);
        toolBar->addAction(actionAuto_st_r_ogrammes);
        toolBar->addAction(actionFlipbook);
        listView->addAction(deleteObject);
        widget->addAction(transCamZero);
		
        retranslateUi(MainWindow);
        QObject::connect(actionQuitter, SIGNAL(triggered()), MainWindow, SLOT(close()));
        QObject::connect(actionNouveau, SIGNAL(triggered()), MainWindow, SLOT(newscene()));
        QObject::connect(actionUndo, SIGNAL(triggered()), MainWindow, SLOT(revertPreviousAction()));

        QObject::connect(actionDepuis_le_disque_dur, SIGNAL(triggered()), MainWindow, SLOT(openfile()));
        QObject::connect(actionDepuis_la_bibliotheque, SIGNAL(triggered()), MainWindow, SLOT(openlibfile()));
        QObject::connect(actionOuvrir, SIGNAL(triggered()), MainWindow, SLOT(open()));	
        QObject::connect(actionEnregistrer, SIGNAL(triggered()), MainWindow, SLOT(save()));	
        QObject::connect(actionEnregistrer_sous, SIGNAL(triggered()), MainWindow, SLOT(saveas()));		
        
		QObject::connect(action_changer_couleur, SIGNAL(triggered()), MainWindow, SLOT(changeObjectColor()));
        QObject::connect(actionPr_f_rences, SIGNAL(triggered()), MainWindow, SLOT(editsettings()));

        QObject::connect(actionA_propos, SIGNAL(triggered()), MainWindow, SLOT(about()));

        QObject::connect(actionNotice_utilisation, SIGNAL(triggered()), MainWindow, SLOT(notice()));
        	
        QObject::connect(listView, SIGNAL(doubleClicked(QModelIndex)), MainWindow, SLOT(selectObject(QModelIndex)));
        QObject::connect(deleteObject, SIGNAL(triggered()), MainWindow, SLOT(deleteSelectedObject()));
        //QObject::connect(listView, SIGNAL(clicked(QModelIndex)), MainWindow, SLOT(selectObject(QModelIndex)));
		
		QObject::connect(actionEffectuer_un_rendu, SIGNAL(triggered()), Creator::getCreator(), SLOT(launchPhotograph()));
		QObject::connect(actionAnaglyphes, SIGNAL(triggered()), Creator::getCreator(), SLOT(launchAnaglyph()));
		QObject::connect(actionAuto_st_r_ogrammes, SIGNAL(triggered()), Creator::getCreator(), SLOT(launchAutostereogram()));
		QObject::connect(actionFlipbook, SIGNAL(triggered()), Creator::getCreator(), SLOT(launchFlipbook()));

		QObject::connect(actionInverser_les_positions_des_fen_tres, SIGNAL(changed()), MainWindow, SLOT(invertwidgets()));
		
		
		QObject::connect(actionTranslate, SIGNAL(triggered()), MainWindow, SLOT(changeModeToTranslate()));
		QObject::connect(actionRotate, SIGNAL(triggered()), MainWindow, SLOT(changeModeToRotate()));
		QObject::connect(actionScale, SIGNAL(triggered()), MainWindow, SLOT(changeModeToScale()));

                QObject::connect(transCamZero, SIGNAL(triggered()), MainWindow, SLOT(translateCameraToZero()));
		
        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Project3Donut", 0));
        actionOuvrir->setText(QApplication::translate("MainWindow", "Ouvrir", 0));
        actionQuitter->setText(QApplication::translate("MainWindow", "Quitter", 0));

        actionNouveau->setText(QApplication::translate("MainWindow", "Nouveau", 0));
        actionEnregistrer->setText(QApplication::translate("MainWindow", "Enregistrer", 0));
        actionEnregistrer_sous->setText(QApplication::translate("MainWindow", "Enregistrer sous", 0));
        actionUndo->setText(QApplication::translate("MainWindow", "Annuler la derniere action", 0));
        actionDepuis_la_bibliotheque->setText(QApplication::translate("MainWindow", "Importer depuis la bibliotheque", 0));
        actionDepuis_le_disque_dur->setText(QApplication::translate("MainWindow", "Importer depuis le disque dur", 0));
		action_changer_couleur->setText(QApplication::translate("MainWindow", "Couleur de l'objet", 0));
		actionPr_f_rences->setText(QApplication::translate("MainWindow", "Pr\303\251f\303\251rences", 0));
        actionA_propos->setText(QApplication::translate("MainWindow", "A propos", 0));
        actionNotice_utilisation->setText(QApplication::translate("MainWindow", "Notice d'utilisation", 0));
        actionEffectuer_un_rendu->setText(QApplication::translate("MainWindow", "Effectuer un rendu", 0));
        actionInverser_les_positions_des_fen_tres->setText(QApplication::translate("MainWindow", "Mettre la fen\303\252tre de visualisation \303\240 gauche", 0));
        actionAnaglyphes->setText(QApplication::translate("MainWindow", "Anaglyphes", 0));
        actionAuto_st_r_ogrammes->setText(QApplication::translate("MainWindow", "Autost\303\251r\303\251ogrammes", 0));
        actionFlipbook->setText(QApplication::translate("MainWindow", "Flipbook", 0));
        menuFichier->setTitle(QApplication::translate("MainWindow", "Fichier", 0));
        menuImporter->setTitle(QApplication::translate("MainWindow", "Importer", 0));
        menuEditer->setTitle(QApplication::translate("MainWindow", "Editer", 0));
        menuAide->setTitle(QApplication::translate("MainWindow", "Aide", 0));
        menuOutils->setTitle(QApplication::translate("MainWindow", "Outils", 0));
        menuFen_tre->setTitle(QApplication::translate("MainWindow", "Fen\303\252tres", 0));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0));
        actionTranslate->setText(QApplication::translate("MainWindow", "Mode Translation", 0));
        actionRotate->setText(QApplication::translate("MainWindow", "Mode Rotation", 0));
        actionScale->setText(QApplication::translate("MainWindow", "Mode Redimensionnement", 0));
#ifndef QT_NO_TOOLTIP
        actionRotate->setToolTip(QApplication::translate("MainWindow", "Mode Rotation", 0));
#endif // QT_NO_TOOLTIP
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
