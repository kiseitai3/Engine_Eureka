/********************************************************************************
** Form generated from reading UI file 'locale_settings.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOCALE_SETTINGS_H
#define UI_LOCALE_SETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_Locale_settings
{
public:

    void setupUi(QDialog *Locale_settings)
    {
        if (Locale_settings->objectName().isEmpty())
            Locale_settings->setObjectName(QStringLiteral("Locale_settings"));
        Locale_settings->resize(400, 300);

        retranslateUi(Locale_settings);

        QMetaObject::connectSlotsByName(Locale_settings);
    } // setupUi

    void retranslateUi(QDialog *Locale_settings)
    {
        Locale_settings->setWindowTitle(QApplication::translate("Locale_settings", "Dialog", 0));
    } // retranslateUi

};

namespace Ui {
    class Locale_settings: public Ui_Locale_settings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOCALE_SETTINGS_H
