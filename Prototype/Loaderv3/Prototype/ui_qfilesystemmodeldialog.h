/********************************************************************************
** Form generated from reading UI file 'dialog_file_tree.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTFILESYSTEMMODELDIALOG_H
#define UI_QTFILESYSTEMMODELDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
//#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListView>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QFileSystemModelDialog
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QSplitter *splitter;

    QTreeView *treeView;
    QListView *listView;
    QDialogButtonBox *buttonBox;

    void setupUi(QFileSystemModelDialog *QFileSystemModelDialog)
    {
        if (QFileSystemModelDialog->objectName().isEmpty())
            QFileSystemModelDialog->setObjectName(QStringLiteral("QFileSystemModelDialog"));
        QFileSystemModelDialog->resize(674, 482);
        verticalLayout = new QVBoxLayout(QFileSystemModelDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        widget = new QWidget(QFileSystemModelDialog);
        widget->setObjectName(QStringLiteral("widget"));
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        splitter = new QSplitter(widget);

        treeView = new QTreeView(splitter);
        treeView->setObjectName(QStringLiteral("treeView"));

        splitter->addWidget(treeView);

        listView = new QListView(splitter);
        listView->setObjectName(QStringLiteral("listView"));

        splitter->addWidget(listView);

        verticalLayout_2->addWidget(splitter);


        verticalLayout->addWidget(widget);

        buttonBox = new QDialogButtonBox(QFileSystemModelDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(QFileSystemModelDialog);
        QObject::connect(listView, SIGNAL(clicked(QModelIndex)), QFileSystemModelDialog, SLOT(on_listView_clicked(QModelIndex)));
        QObject::connect(treeView, SIGNAL(clicked(QModelIndex)), QFileSystemModelDialog, SLOT(on_treeView_clicked(QModelIndex)));
        QObject::connect(buttonBox, SIGNAL(accepted()), QFileSystemModelDialog, SLOT(button_ok_create_selected()));
        QObject::connect(buttonBox, SIGNAL(accepted()), QFileSystemModelDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), QFileSystemModelDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(QFileSystemModelDialog);
    } // setupUi

    void retranslateUi(QDialog *QFileSystemModelDialog)
    {
        QFileSystemModelDialog->setWindowTitle(QApplication::translate("QFileSystemModelDialog", "Dialog", 0));
    } // retranslateUi

};

namespace Ui {
    class QFileSystemModelDialog: public Ui_QFileSystemModelDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTFILESYSTEMMODELDIALOG_H
