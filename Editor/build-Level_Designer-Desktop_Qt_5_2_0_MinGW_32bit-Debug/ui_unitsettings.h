/********************************************************************************
** Form generated from reading UI file 'unitsettings.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UNITSETTINGS_H
#define UI_UNITSETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UnitSettings
{
public:
    QTabWidget *tabWidget;
    QWidget *tabStats;
    QWidget *tab_2;

    void setupUi(QDialog *UnitSettings)
    {
        if (UnitSettings->objectName().isEmpty())
            UnitSettings->setObjectName(QStringLiteral("UnitSettings"));
        UnitSettings->resize(937, 519);
        tabWidget = new QTabWidget(UnitSettings);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(0, 0, 931, 511));
        tabStats = new QWidget();
        tabStats->setObjectName(QStringLiteral("tabStats"));
        tabWidget->addTab(tabStats, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        tabWidget->addTab(tab_2, QString());

        retranslateUi(UnitSettings);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(UnitSettings);
    } // setupUi

    void retranslateUi(QDialog *UnitSettings)
    {
        UnitSettings->setWindowTitle(QApplication::translate("UnitSettings", "Dialog", 0));
        tabWidget->setTabText(tabWidget->indexOf(tabStats), QApplication::translate("UnitSettings", "Unit Stats", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("UnitSettings", "Unit Textures", 0));
    } // retranslateUi

};

namespace Ui {
    class UnitSettings: public Ui_UnitSettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UNITSETTINGS_H
