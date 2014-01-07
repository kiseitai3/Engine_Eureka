/********************************************************************************
** Form generated from reading UI file 'startup.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STARTUP_H
#define UI_STARTUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Startup
{
public:
    QDialogButtonBox *buttonBox;
    QGroupBox *groupBox;
    QLineEdit *leLocation;
    QPushButton *pbOpenBrowse;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *leName;
    QPushButton *pbNameBrowse;

    void setupUi(QDialog *Startup)
    {
        if (Startup->objectName().isEmpty())
            Startup->setObjectName(QStringLiteral("Startup"));
        Startup->resize(400, 294);
        buttonBox = new QDialogButtonBox(Startup);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        groupBox = new QGroupBox(Startup);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(20, 30, 351, 181));
        leLocation = new QLineEdit(groupBox);
        leLocation->setObjectName(QStringLiteral("leLocation"));
        leLocation->setGeometry(QRect(10, 60, 251, 20));
        pbOpenBrowse = new QPushButton(groupBox);
        pbOpenBrowse->setObjectName(QStringLiteral("pbOpenBrowse"));
        pbOpenBrowse->setGeometry(QRect(270, 60, 75, 23));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 30, 251, 16));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 100, 81, 16));
        leName = new QLineEdit(groupBox);
        leName->setObjectName(QStringLiteral("leName"));
        leName->setGeometry(QRect(10, 130, 113, 20));
        pbNameBrowse = new QPushButton(groupBox);
        pbNameBrowse->setObjectName(QStringLiteral("pbNameBrowse"));
        pbNameBrowse->setGeometry(QRect(130, 130, 75, 23));

        retranslateUi(Startup);
        QObject::connect(buttonBox, SIGNAL(accepted()), Startup, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Startup, SLOT(reject()));

        QMetaObject::connectSlotsByName(Startup);
    } // setupUi

    void retranslateUi(QDialog *Startup)
    {
        Startup->setWindowTitle(QApplication::translate("Startup", "Dialog", 0));
        groupBox->setTitle(QApplication::translate("Startup", "Project", 0));
        pbOpenBrowse->setText(QApplication::translate("Startup", "Browse", 0));
        label->setText(QApplication::translate("Startup", "Location of an existing project or of a new project:", 0));
#ifndef QT_NO_TOOLTIP
        label_2->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        label_2->setText(QApplication::translate("Startup", "Project Name:", 0));
        pbNameBrowse->setText(QApplication::translate("Startup", "Browse", 0));
    } // retranslateUi

};

namespace Ui {
    class Startup: public Ui_Startup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STARTUP_H
