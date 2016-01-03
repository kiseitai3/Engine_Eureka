/********************************************************************************
** Form generated from reading UI file 'unitsettings.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
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

QT_BEGIN_NAMESPACE

class Ui_UnitSettings
{
public:

    void setupUi(QDialog *UnitSettings)
    {
        if (UnitSettings->objectName().isEmpty())
            UnitSettings->setObjectName(QStringLiteral("UnitSettings"));
        UnitSettings->resize(400, 300);

        retranslateUi(UnitSettings);

        QMetaObject::connectSlotsByName(UnitSettings);
    } // setupUi

    void retranslateUi(QDialog *UnitSettings)
    {
        UnitSettings->setWindowTitle(QApplication::translate("UnitSettings", "Dialog", 0));
    } // retranslateUi

};

namespace Ui {
    class UnitSettings: public Ui_UnitSettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UNITSETTINGS_H
