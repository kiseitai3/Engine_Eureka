/********************************************************************************
** Form generated from reading UI file 'physicssettings.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PHYSICSSETTINGS_H
#define UI_PHYSICSSETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_PhysicsSettings
{
public:

    void setupUi(QDialog *PhysicsSettings)
    {
        if (PhysicsSettings->objectName().isEmpty())
            PhysicsSettings->setObjectName(QStringLiteral("PhysicsSettings"));
        PhysicsSettings->resize(400, 300);

        retranslateUi(PhysicsSettings);

        QMetaObject::connectSlotsByName(PhysicsSettings);
    } // setupUi

    void retranslateUi(QDialog *PhysicsSettings)
    {
        PhysicsSettings->setWindowTitle(QApplication::translate("PhysicsSettings", "Dialog", 0));
    } // retranslateUi

};

namespace Ui {
    class PhysicsSettings: public Ui_PhysicsSettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PHYSICSSETTINGS_H
