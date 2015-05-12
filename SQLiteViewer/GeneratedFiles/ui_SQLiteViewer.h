/********************************************************************************
** Form generated from reading UI file 'SQLiteViewer.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SQLITEVIEWER_H
#define UI_SQLITEVIEWER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SQLiteViewerClass
{
public:
    QAction *actionOpen_DB;
    QAction *actionClose_DB;
    QAction *actionCreate_DemoDB01;
    QAction *actionCreate_DemoDB02;
    QAction *actionCreate_DemoDB03;
    QWidget *centralWidget;
    QListView *lstTableNames;
    QPushButton *cmdShowTable;
    QTableView *tblRecords;
    QPushButton *cmdUpdateAll;
    QPushButton *cmdCommitAll;
    QPushButton *cmdAddRecord;
    QPushButton *cmdDeleteRecord;
    QPushButton *cmdDeleteAllRecords;
    QPushButton *cmdUnDeleteRecord;
    QPushButton *cmdUnDeleteAllRecords;
    QPushButton *cmdHideTable;
    QPushButton *cmdUndoRevert;
    QLabel *lblTableNames;
    QLabel *lblDataNames;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuDemo;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *SQLiteViewerClass)
    {
        if (SQLiteViewerClass->objectName().isEmpty())
            SQLiteViewerClass->setObjectName(QStringLiteral("SQLiteViewerClass"));
        SQLiteViewerClass->resize(1178, 800);
        actionOpen_DB = new QAction(SQLiteViewerClass);
        actionOpen_DB->setObjectName(QStringLiteral("actionOpen_DB"));
        actionClose_DB = new QAction(SQLiteViewerClass);
        actionClose_DB->setObjectName(QStringLiteral("actionClose_DB"));
        actionCreate_DemoDB01 = new QAction(SQLiteViewerClass);
        actionCreate_DemoDB01->setObjectName(QStringLiteral("actionCreate_DemoDB01"));
        actionCreate_DemoDB02 = new QAction(SQLiteViewerClass);
        actionCreate_DemoDB02->setObjectName(QStringLiteral("actionCreate_DemoDB02"));
        actionCreate_DemoDB03 = new QAction(SQLiteViewerClass);
        actionCreate_DemoDB03->setObjectName(QStringLiteral("actionCreate_DemoDB03"));
        centralWidget = new QWidget(SQLiteViewerClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        lstTableNames = new QListView(centralWidget);
        lstTableNames->setObjectName(QStringLiteral("lstTableNames"));
        lstTableNames->setGeometry(QRect(10, 60, 221, 481));
        cmdShowTable = new QPushButton(centralWidget);
        cmdShowTable->setObjectName(QStringLiteral("cmdShowTable"));
        cmdShowTable->setGeometry(QRect(140, 540, 93, 28));
        tblRecords = new QTableView(centralWidget);
        tblRecords->setObjectName(QStringLiteral("tblRecords"));
        tblRecords->setGeometry(QRect(260, 60, 901, 641));
        tblRecords->horizontalHeader()->setVisible(true);
        cmdUpdateAll = new QPushButton(centralWidget);
        cmdUpdateAll->setObjectName(QStringLiteral("cmdUpdateAll"));
        cmdUpdateAll->setGeometry(QRect(260, 700, 93, 28));
        cmdCommitAll = new QPushButton(centralWidget);
        cmdCommitAll->setObjectName(QStringLiteral("cmdCommitAll"));
        cmdCommitAll->setGeometry(QRect(370, 700, 93, 28));
        cmdAddRecord = new QPushButton(centralWidget);
        cmdAddRecord->setObjectName(QStringLiteral("cmdAddRecord"));
        cmdAddRecord->setGeometry(QRect(790, 30, 93, 28));
        cmdDeleteRecord = new QPushButton(centralWidget);
        cmdDeleteRecord->setObjectName(QStringLiteral("cmdDeleteRecord"));
        cmdDeleteRecord->setGeometry(QRect(900, 0, 93, 28));
        cmdDeleteAllRecords = new QPushButton(centralWidget);
        cmdDeleteAllRecords->setObjectName(QStringLiteral("cmdDeleteAllRecords"));
        cmdDeleteAllRecords->setGeometry(QRect(1030, 0, 111, 28));
        cmdUnDeleteRecord = new QPushButton(centralWidget);
        cmdUnDeleteRecord->setObjectName(QStringLiteral("cmdUnDeleteRecord"));
        cmdUnDeleteRecord->setGeometry(QRect(900, 30, 121, 28));
        cmdUnDeleteAllRecords = new QPushButton(centralWidget);
        cmdUnDeleteAllRecords->setObjectName(QStringLiteral("cmdUnDeleteAllRecords"));
        cmdUnDeleteAllRecords->setGeometry(QRect(1030, 30, 131, 28));
        cmdHideTable = new QPushButton(centralWidget);
        cmdHideTable->setObjectName(QStringLiteral("cmdHideTable"));
        cmdHideTable->setGeometry(QRect(140, 570, 93, 28));
        cmdUndoRevert = new QPushButton(centralWidget);
        cmdUndoRevert->setObjectName(QStringLiteral("cmdUndoRevert"));
        cmdUndoRevert->setGeometry(QRect(470, 700, 93, 28));
        lblTableNames = new QLabel(centralWidget);
        lblTableNames->setObjectName(QStringLiteral("lblTableNames"));
        lblTableNames->setGeometry(QRect(10, 40, 53, 16));
        lblDataNames = new QLabel(centralWidget);
        lblDataNames->setObjectName(QStringLiteral("lblDataNames"));
        lblDataNames->setGeometry(QRect(260, 40, 53, 16));
        SQLiteViewerClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(SQLiteViewerClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1178, 26));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuDemo = new QMenu(menuBar);
        menuDemo->setObjectName(QStringLiteral("menuDemo"));
        SQLiteViewerClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(SQLiteViewerClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        SQLiteViewerClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(SQLiteViewerClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        SQLiteViewerClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuDemo->menuAction());
        menuFile->addAction(actionOpen_DB);
        menuFile->addAction(actionClose_DB);
        menuDemo->addAction(actionCreate_DemoDB01);
        menuDemo->addAction(actionCreate_DemoDB02);
        menuDemo->addAction(actionCreate_DemoDB03);

        retranslateUi(SQLiteViewerClass);

        QMetaObject::connectSlotsByName(SQLiteViewerClass);
    } // setupUi

    void retranslateUi(QMainWindow *SQLiteViewerClass)
    {
        SQLiteViewerClass->setWindowTitle(QApplication::translate("SQLiteViewerClass", "SQLiteViewer", 0));
        actionOpen_DB->setText(QApplication::translate("SQLiteViewerClass", "Open DB", 0));
        actionClose_DB->setText(QApplication::translate("SQLiteViewerClass", "Close DB", 0));
        actionCreate_DemoDB01->setText(QApplication::translate("SQLiteViewerClass", "Create DemoDB01", 0));
        actionCreate_DemoDB02->setText(QApplication::translate("SQLiteViewerClass", "Create DemoDB02", 0));
        actionCreate_DemoDB03->setText(QApplication::translate("SQLiteViewerClass", "Create DemoDB03", 0));
        cmdShowTable->setText(QApplication::translate("SQLiteViewerClass", "SHOW Table", 0));
        cmdUpdateAll->setText(QApplication::translate("SQLiteViewerClass", "Update All", 0));
        cmdCommitAll->setText(QApplication::translate("SQLiteViewerClass", "Commit All", 0));
        cmdAddRecord->setText(QApplication::translate("SQLiteViewerClass", "Add Record", 0));
        cmdDeleteRecord->setText(QApplication::translate("SQLiteViewerClass", "Delete Record", 0));
        cmdDeleteAllRecords->setText(QApplication::translate("SQLiteViewerClass", "Delete All Records", 0));
        cmdUnDeleteRecord->setText(QApplication::translate("SQLiteViewerClass", "UNDelete Record", 0));
        cmdUnDeleteAllRecords->setText(QApplication::translate("SQLiteViewerClass", "UNDelete All Records", 0));
        cmdHideTable->setText(QApplication::translate("SQLiteViewerClass", "HIDE Table", 0));
        cmdUndoRevert->setText(QApplication::translate("SQLiteViewerClass", "Undo Revert", 0));
        lblTableNames->setText(QApplication::translate("SQLiteViewerClass", "TABLES", 0));
        lblDataNames->setText(QApplication::translate("SQLiteViewerClass", "DATA", 0));
        menuFile->setTitle(QApplication::translate("SQLiteViewerClass", "File", 0));
        menuDemo->setTitle(QApplication::translate("SQLiteViewerClass", "Demo", 0));
    } // retranslateUi

};

namespace Ui {
    class SQLiteViewerClass: public Ui_SQLiteViewerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SQLITEVIEWER_H
