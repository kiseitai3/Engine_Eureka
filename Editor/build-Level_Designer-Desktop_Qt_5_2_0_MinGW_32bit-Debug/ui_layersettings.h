/********************************************************************************
** Form generated from reading UI file 'layersettings.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LAYERSETTINGS_H
#define UI_LAYERSETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_Layersettings
{
public:

    void setupUi(QDialog *Layersettings)
    {
        if (Layersettings->objectName().isEmpty())
            Layersettings->setObjectName(QStringLiteral("Layersettings"));
        Layersettings->resize(400, 300);

        retranslateUi(Layersettings);

        QMetaObject::connectSlotsByName(Layersettings);
    } // setupUi

    void retranslateUi(QDialog *Layersettings)
    {
        Layersettings->setWindowTitle(QApplication::translate("Layersettings", "Dialog", 0));
    } // retranslateUi

};

namespace Ui {
    class Layersettings: public Ui_Layersettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LAYERSETTINGS_H
