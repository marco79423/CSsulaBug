/********************************************************************************
** Form generated from reading UI file 'lister.ui'
**
** Created: Wed Mar 21 15:02:11 2012
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LISTER_H
#define UI_LISTER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QTableView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Lister
{
public:
    QVBoxLayout *verticalLayout;
    QLineEdit *lineEdit;
    QTableView *tableView;

    void setupUi(QWidget *Lister)
    {
        if (Lister->objectName().isEmpty())
            Lister->setObjectName(QString::fromUtf8("Lister"));
        Lister->resize(400, 300);
        verticalLayout = new QVBoxLayout(Lister);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        lineEdit = new QLineEdit(Lister);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        verticalLayout->addWidget(lineEdit);

        tableView = new QTableView(Lister);
        tableView->setObjectName(QString::fromUtf8("tableView"));

        verticalLayout->addWidget(tableView);


        retranslateUi(Lister);

        QMetaObject::connectSlotsByName(Lister);
    } // setupUi

    void retranslateUi(QWidget *Lister)
    {
        Lister->setWindowTitle(QApplication::translate("Lister", "Lister", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Lister: public Ui_Lister {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LISTER_H
