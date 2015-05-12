/********************************************************************************
** Form generated from reading UI file 'QFieldEditDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QFIELDEDITDIALOG_H
#define UI_QFIELDEDITDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_QFieldEditDialogClass
{
public:
    QPushButton *cmdOK;
    QPushButton *cmdCancel;
    QTextEdit *txtField;

    void setupUi(QDialog *QFieldEditDialogClass)
    {
        if (QFieldEditDialogClass->objectName().isEmpty())
            QFieldEditDialogClass->setObjectName(QStringLiteral("QFieldEditDialogClass"));
        QFieldEditDialogClass->resize(700, 400);
        cmdOK = new QPushButton(QFieldEditDialogClass);
        cmdOK->setObjectName(QStringLiteral("cmdOK"));
        cmdOK->setGeometry(QRect(490, 360, 93, 28));
        cmdCancel = new QPushButton(QFieldEditDialogClass);
        cmdCancel->setObjectName(QStringLiteral("cmdCancel"));
        cmdCancel->setGeometry(QRect(600, 360, 93, 28));
        txtField = new QTextEdit(QFieldEditDialogClass);
        txtField->setObjectName(QStringLiteral("txtField"));
        txtField->setGeometry(QRect(10, 10, 680, 340));

        retranslateUi(QFieldEditDialogClass);

        QMetaObject::connectSlotsByName(QFieldEditDialogClass);
    } // setupUi

    void retranslateUi(QDialog *QFieldEditDialogClass)
    {
        QFieldEditDialogClass->setWindowTitle(QApplication::translate("QFieldEditDialogClass", "QFieldEditDialog", 0));
        cmdOK->setText(QApplication::translate("QFieldEditDialogClass", "OK", 0));
        cmdCancel->setText(QApplication::translate("QFieldEditDialogClass", "CANCEL", 0));
    } // retranslateUi

};

namespace Ui {
    class QFieldEditDialogClass: public Ui_QFieldEditDialogClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QFIELDEDITDIALOG_H
