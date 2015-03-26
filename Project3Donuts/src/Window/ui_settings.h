/********************************************************************************
** Form generated from reading UI file 'preferences.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGS2_H
#define UI_SETTINGS2_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QKeySequenceEdit>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "ClickLabel.hpp"

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *General;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QSpinBox *ResBox_x;
    QLabel *label_3;
    QSpinBox *ResBox_y;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QLabel *label_5;
    QCheckBox *WindowBox;
    QSpinBox *autoTimer;
    QLabel *label_16;
    QLabel *label_17;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QSpinBox *ObjectLimitBox;
    QLabel *label_2;
    QLabel *label_6;
    QLabel *label_7;
    QToolButton *BrowseButton;
    QLabel *fileLabel;
    QLabel *label_4;
    ClickLabel *colorLabel;
    QPushButton *DefaultGeneralButton;
    QWidget *shortcuts;
    QFormLayout *formLayout;
    QLabel *label_9;
    QKeySequenceEdit *Translate_keySequenceEdit;
    QLabel *label_10;
    QKeySequenceEdit *Rotate_keySequenceEdit;
    QLabel *label_11;
    QKeySequenceEdit *Scale_keySequenceEdit;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_14;
    QKeySequenceEdit *ColorMap_keySequenceEdit;
    QKeySequenceEdit *AutoStereogramme_keySequenceEdit;
    QKeySequenceEdit *Anaglyphe_keySequenceEdit;
    QLabel *label_15;
    QKeySequenceEdit *Flipbook_keySequenceEdit;
    QPushButton *DefaultShortcutsButton;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
            
        QSettings settings("settings.ini", QSettings::IniFormat);
        
        Dialog->resize(687, 603);
        verticalLayout = new QVBoxLayout(Dialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        tabWidget = new QTabWidget(Dialog);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy);
        General = new QWidget();
        General->setObjectName(QStringLiteral("General"));
        verticalLayout_2 = new QVBoxLayout(General);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        groupBox = new QGroupBox(General);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        widget = new QWidget(groupBox);
        widget->setObjectName(QStringLiteral("widget"));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        
        ResBox_x = new QSpinBox(widget);
        ResBox_x->setObjectName(QStringLiteral("ResBox_x"));
		ResBox_x->setRange(0,4000);
		ResBox_x->setValue(settings.value("General/prog_x", 782).toInt());
		
        horizontalLayout_2->addWidget(ResBox_x);

        label_3 = new QLabel(widget);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_2->addWidget(label_3, 0, Qt::AlignHCenter);

        ResBox_y = new QSpinBox(widget);
        ResBox_y->setObjectName(QStringLiteral("ResBox_y"));
		ResBox_y->setRange(0,4000);
		ResBox_y->setValue(settings.value("General/prog_y", 486).toInt());
		
        horizontalLayout_2->addWidget(ResBox_y);


        gridLayout->addWidget(widget, 0, 1, 1, 1);

        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 2, 1, 1);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 2, 0, 1, 1);

        WindowBox = new QCheckBox(groupBox);
        WindowBox->setObjectName(QStringLiteral("WindowBox"));
        WindowBox->setChecked(settings.value("General/invertedwindows",false).toBool());

        gridLayout->addWidget(WindowBox, 2, 1, 1, 1);

        autoTimer = new QSpinBox(groupBox);
        autoTimer->setObjectName(QStringLiteral("autoTimer"));
        autoTimer->setRange(1,3600);
        autoTimer->setValue(settings.value("General/timeautosave", 60).toInt());

        gridLayout->addWidget(autoTimer, 1, 1, 1, 1);

        label_16 = new QLabel(groupBox);
        label_16->setObjectName(QStringLiteral("label_16"));

        gridLayout->addWidget(label_16, 1, 0, 1, 1);

        label_17 = new QLabel(groupBox);
        label_17->setObjectName(QStringLiteral("label_17"));

        gridLayout->addWidget(label_17, 1, 2, 1, 1);

        verticalLayout_2->addWidget(groupBox);

        groupBox_2 = new QGroupBox(General);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        ObjectLimitBox = new QSpinBox(groupBox_2);
        ObjectLimitBox->setObjectName(QStringLiteral("ObjectLimitBox"));
		ObjectLimitBox->setRange(0,1000000);
        ObjectLimitBox->setValue(settings.value("Viewer/FaceNumberMax",200000).toInt());


        gridLayout_2->addWidget(ObjectLimitBox, 1, 2, 1, 1);

        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_2->addWidget(label_2, 1, 0, 1, 1);

        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout_2->addWidget(label_6, 1, 3, 1, 1);

        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout_2->addWidget(label_7, 3, 0, 1, 1);

        BrowseButton = new QToolButton(groupBox_2);
        BrowseButton->setObjectName(QStringLiteral("BrowseButton"));

        gridLayout_2->addWidget(BrowseButton, 3, 3, 1, 1);

        fileLabel = new QLabel(groupBox_2);
        fileLabel->setObjectName(QStringLiteral("fileLabel"));

        gridLayout_2->addWidget(fileLabel, 3, 2, 1, 1);

        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_2->addWidget(label_4, 0, 0, 1, 1);

        colorLabel = new ClickLabel(QPalette(Qt::black),groupBox_2);
        colorLabel->setObjectName(QStringLiteral("colorLabel"));

        QColor _color = settings.value("Viewer/background_color",QColor(0,0,102)).value<QColor>();
        colorLabel->setPalette(QPalette(_color));
        colorLabel->setAutoFillBackground(true);

        gridLayout_2->addWidget(colorLabel, 0, 2, 1, 1);


        verticalLayout_2->addWidget(groupBox_2);

        DefaultGeneralButton = new QPushButton(General);
        DefaultGeneralButton->setObjectName(QStringLiteral("DefaultGeneralButton"));

        verticalLayout_2->addWidget(DefaultGeneralButton, 0, Qt::AlignRight);

        tabWidget->addTab(General, QString());
        shortcuts = new QWidget();
        shortcuts->setObjectName(QStringLiteral("shortcuts"));
        formLayout = new QFormLayout(shortcuts);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        label_9 = new QLabel(shortcuts);
        label_9->setObjectName(QStringLiteral("label_9"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_9);

        Translate_keySequenceEdit = new QKeySequenceEdit(shortcuts);
        Translate_keySequenceEdit->setObjectName(QStringLiteral("Translate_keySequenceEdit"));
        Translate_keySequenceEdit->setKeySequence(settings.value("Shortcuts/translate",QKeySequence("T")).value<QKeySequence>());

        formLayout->setWidget(0, QFormLayout::FieldRole, Translate_keySequenceEdit);

        label_10 = new QLabel(shortcuts);
        label_10->setObjectName(QStringLiteral("label_10"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_10);

        Rotate_keySequenceEdit = new QKeySequenceEdit(shortcuts);
        Rotate_keySequenceEdit->setObjectName(QStringLiteral("Rotate_keySequenceEdit"));
        Rotate_keySequenceEdit->setKeySequence(settings.value("Shortcuts/rotate",QKeySequence("R")).value<QKeySequence>());

        formLayout->setWidget(1, QFormLayout::FieldRole, Rotate_keySequenceEdit);

        label_11 = new QLabel(shortcuts);
        label_11->setObjectName(QStringLiteral("label_11"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_11);

        Scale_keySequenceEdit = new QKeySequenceEdit(shortcuts);
        Scale_keySequenceEdit->setObjectName(QStringLiteral("Scale_keySequenceEdit"));
        Scale_keySequenceEdit->setKeySequence(settings.value("Shortcuts/scale",QKeySequence("S")).value<QKeySequence>());

        formLayout->setWidget(2, QFormLayout::FieldRole, Scale_keySequenceEdit);

        label_12 = new QLabel(shortcuts);
        label_12->setObjectName(QStringLiteral("label_12"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_12);

        label_13 = new QLabel(shortcuts);
        label_13->setObjectName(QStringLiteral("label_13"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_13);

        label_14 = new QLabel(shortcuts);
        label_14->setObjectName(QStringLiteral("label_14"));

        formLayout->setWidget(6, QFormLayout::LabelRole, label_14);

        ColorMap_keySequenceEdit = new QKeySequenceEdit(shortcuts);
        ColorMap_keySequenceEdit->setObjectName(QStringLiteral("ColorMap_keySequenceEdit"));
        ColorMap_keySequenceEdit->setKeySequence(settings.value("Shortcuts/render",QKeySequence("P")).value<QKeySequence>());

        formLayout->setWidget(3, QFormLayout::FieldRole, ColorMap_keySequenceEdit);

        AutoStereogramme_keySequenceEdit = new QKeySequenceEdit(shortcuts);
        AutoStereogramme_keySequenceEdit->setObjectName(QStringLiteral("AutoStereogramme_keySequenceEdit"));
        AutoStereogramme_keySequenceEdit->setKeySequence(settings.value("Shortcuts/autostereogramme",QKeySequence("U")).value<QKeySequence>());

        formLayout->setWidget(6, QFormLayout::FieldRole, AutoStereogramme_keySequenceEdit);

        Anaglyphe_keySequenceEdit = new QKeySequenceEdit(shortcuts);
        Anaglyphe_keySequenceEdit->setObjectName(QStringLiteral("Anaglyphe_keySequenceEdit"));
        Anaglyphe_keySequenceEdit->setKeySequence(settings.value("Shortcuts/anaglyphes",QKeySequence("N")).value<QKeySequence>());

        formLayout->setWidget(4, QFormLayout::FieldRole, Anaglyphe_keySequenceEdit);

        label_15 = new QLabel(shortcuts);
        label_15->setObjectName(QStringLiteral("label_15"));

        formLayout->setWidget(7, QFormLayout::LabelRole, label_15);

        Flipbook_keySequenceEdit = new QKeySequenceEdit(shortcuts);
        Flipbook_keySequenceEdit->setObjectName(QStringLiteral("Flipbook_keySequenceEdit"));
        Flipbook_keySequenceEdit->setKeySequence(settings.value("Shortcuts/flipbook",QKeySequence("F")).value<QKeySequence>());

        formLayout->setWidget(7, QFormLayout::FieldRole, Flipbook_keySequenceEdit);

        DefaultShortcutsButton = new QPushButton(shortcuts);
        DefaultShortcutsButton->setObjectName(QStringLiteral("DefaultShortcutsButton"));

        formLayout->setWidget(8, QFormLayout::FieldRole, DefaultShortcutsButton);

        tabWidget->addTab(shortcuts, QString());

        verticalLayout->addWidget(tabWidget);

        buttonBox = new QDialogButtonBox(Dialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        buttonBox->button(QDialogButtonBox::Cancel)->setText("Annuler");

        verticalLayout->addWidget(buttonBox);


        retranslateUi(Dialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), Dialog, SLOT(editparameters()));
        QObject::connect(buttonBox, SIGNAL(accepted()), Dialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Dialog, SLOT(resetparameters()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Dialog, SLOT(reject()));
		QObject::connect(colorLabel, SIGNAL(clicked()), Dialog, SLOT(changecolor()));
		QObject::connect(DefaultGeneralButton, SIGNAL(clicked()), Dialog, SLOT(generaltodefault()));
        QObject::connect(DefaultShortcutsButton, SIGNAL(clicked()), Dialog, SLOT(shortcutstodefault()));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Pr\303\251f\303\251rences", 0));
        groupBox->setTitle(QApplication::translate("Dialog", "Affichage", 0));
        label_3->setText(QApplication::translate("Dialog", "x", 0));
        label->setText(QApplication::translate("Dialog", "R\303\251solution au d\303\251marrage", 0));
        label_5->setText(QApplication::translate("Dialog", "Mettre la fen\303\252tre de visualisation \303\240 gauche au d\303\251marrage", 0));
        WindowBox->setText(QString());

        label_16->setText(QApplication::translate("Dialog", "Temps entre deux sauvegardes automatiques ", 0));
        label_17->setText(QApplication::translate("Dialog", "secondes", 0));
        groupBox_2->setTitle(QApplication::translate("Dialog", "Visualiseur", 0));
        label_2->setText(QApplication::translate("Dialog", "Proposer la d\303\251gradation d'objets \303\240 partir de :", 0));
        label_6->setText(QApplication::translate("Dialog", "sommets", 0));
        label_7->setText(QApplication::translate("Dialog", "Emplacement de la biblioth\303\250que d'objets", 0));
        BrowseButton->setText(QApplication::translate("Dialog", "parcourir", 0));
        fileLabel->setText(QApplication::translate("Dialog", "TextLabel", 0));
        label_4->setText(QApplication::translate("Dialog", "Couleur de fond", 0));
        colorLabel->setText(QApplication::translate("Dialog", "", 0));
        DefaultGeneralButton->setText(QApplication::translate("Dialog", "Restaurer les valeurs par d\303\251faut", 0));
        tabWidget->setTabText(tabWidget->indexOf(General), QApplication::translate("Dialog", "G\303\251n\303\251ral", 0));
        label_9->setText(QApplication::translate("Dialog", "Mode Translation", 0));
        label_10->setText(QApplication::translate("Dialog", "Mode Rotation", 0));
        label_11->setText(QApplication::translate("Dialog", "Mode Mise \303\240 l'\303\251chelle", 0));
        label_12->setText(QApplication::translate("Dialog", "Effectuer un rendu de la sc\303\250ne", 0));
        label_13->setText(QApplication::translate("Dialog", "Calculer un anaglyphe \303\240 partir de la sc\303\250ne", 0));
        label_14->setText(QApplication::translate("Dialog", "Calculer un auto st\303\251r\303\251ogramme \303\240 partir de la sc\303\250ne", 0));
        label_15->setText(QApplication::translate("Dialog", "R\303\251aliser un flipbook", 0));
        DefaultShortcutsButton->setText(QApplication::translate("Dialog", "Restaurer les valeurs par d\303\251faut", 0));
        tabWidget->setTabText(tabWidget->indexOf(shortcuts), QApplication::translate("Dialog", "Raccourcis", 0));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGS2_H
