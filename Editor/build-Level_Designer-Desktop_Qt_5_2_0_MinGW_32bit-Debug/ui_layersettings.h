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
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_Layersettings
{
public:
    QGroupBox *groupBox;
    QLabel *label;
    QLineEdit *leTexture;
    QPushButton *pbBrowse;
    QLabel *label_2;
    QSpinBox *sbX;
    QLabel *label_3;
    QLabel *label_4;
    QSpinBox *sbY;
    QLabel *label_5;
    QSpinBox *sbZ;
    QPushButton *pbSave;
    QPushButton *pbSaveAdd;
    QLabel *label_6;
    QLineEdit *leLayerName;
    QGroupBox *groupBox_2;
    QListWidget *lstSet;
    QPushButton *pbSetSave;
    QPushButton *pbSetOpen;
    QPushButton *pbSetRemove;
    QPushButton *pbSetAdd;
    QLabel *label_7;
    QLineEdit *leNameSet;

    void setupUi(QDialog *Layersettings)
    {
        if (Layersettings->objectName().isEmpty())
            Layersettings->setObjectName(QStringLiteral("Layersettings"));
        Layersettings->resize(765, 320);
        groupBox = new QGroupBox(Layersettings);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(0, 0, 331, 261));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 20, 161, 16));
        leTexture = new QLineEdit(groupBox);
        leTexture->setObjectName(QStringLiteral("leTexture"));
        leTexture->setGeometry(QRect(10, 40, 201, 22));
        pbBrowse = new QPushButton(groupBox);
        pbBrowse->setObjectName(QStringLiteral("pbBrowse"));
        pbBrowse->setGeometry(QRect(220, 40, 93, 28));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 80, 171, 16));
        sbX = new QSpinBox(groupBox);
        sbX->setObjectName(QStringLiteral("sbX"));
        sbX->setGeometry(QRect(30, 110, 42, 22));
        sbX->setMaximum(999999);
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 110, 21, 16));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(90, 110, 21, 16));
        sbY = new QSpinBox(groupBox);
        sbY->setObjectName(QStringLiteral("sbY"));
        sbY->setGeometry(QRect(110, 110, 42, 22));
        sbY->setMaximum(999999);
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(170, 110, 21, 16));
        sbZ = new QSpinBox(groupBox);
        sbZ->setObjectName(QStringLiteral("sbZ"));
        sbZ->setGeometry(QRect(190, 110, 42, 22));
        sbZ->setMaximum(999999);
        pbSave = new QPushButton(groupBox);
        pbSave->setObjectName(QStringLiteral("pbSave"));
        pbSave->setGeometry(QRect(200, 220, 93, 28));
        pbSaveAdd = new QPushButton(groupBox);
        pbSaveAdd->setObjectName(QStringLiteral("pbSaveAdd"));
        pbSaveAdd->setGeometry(QRect(22, 220, 141, 28));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(10, 150, 91, 16));
        leLayerName = new QLineEdit(groupBox);
        leLayerName->setObjectName(QStringLiteral("leLayerName"));
        leLayerName->setGeometry(QRect(10, 170, 231, 22));
        groupBox_2 = new QGroupBox(Layersettings);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(330, 0, 431, 311));
        lstSet = new QListWidget(groupBox_2);
        lstSet->setObjectName(QStringLiteral("lstSet"));
        lstSet->setGeometry(QRect(10, 60, 411, 191));
        pbSetSave = new QPushButton(groupBox_2);
        pbSetSave->setObjectName(QStringLiteral("pbSetSave"));
        pbSetSave->setGeometry(QRect(330, 270, 93, 28));
        pbSetOpen = new QPushButton(groupBox_2);
        pbSetOpen->setObjectName(QStringLiteral("pbSetOpen"));
        pbSetOpen->setGeometry(QRect(220, 270, 93, 28));
        pbSetRemove = new QPushButton(groupBox_2);
        pbSetRemove->setObjectName(QStringLiteral("pbSetRemove"));
        pbSetRemove->setGeometry(QRect(120, 270, 93, 28));
        pbSetAdd = new QPushButton(groupBox_2);
        pbSetAdd->setObjectName(QStringLiteral("pbSetAdd"));
        pbSetAdd->setGeometry(QRect(20, 270, 93, 28));
        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(10, 20, 41, 16));
        leNameSet = new QLineEdit(groupBox_2);
        leNameSet->setObjectName(QStringLiteral("leNameSet"));
        leNameSet->setGeometry(QRect(60, 20, 271, 22));

        retranslateUi(Layersettings);

        QMetaObject::connectSlotsByName(Layersettings);
    } // setupUi

    void retranslateUi(QDialog *Layersettings)
    {
        Layersettings->setWindowTitle(QApplication::translate("Layersettings", "Dialog", 0));
        groupBox->setTitle(QApplication::translate("Layersettings", "Layer settings", 0));
        label->setText(QApplication::translate("Layersettings", "Texture descriptor location:", 0));
        pbBrowse->setText(QApplication::translate("Layersettings", "Browse", 0));
        label_2->setText(QApplication::translate("Layersettings", "Location of layer on screen:", 0));
        label_3->setText(QApplication::translate("Layersettings", "X:", 0));
        label_4->setText(QApplication::translate("Layersettings", "Y:", 0));
        label_5->setText(QApplication::translate("Layersettings", "Z:", 0));
        pbSave->setText(QApplication::translate("Layersettings", "Save", 0));
        pbSaveAdd->setText(QApplication::translate("Layersettings", "Save and add to set!", 0));
        label_6->setText(QApplication::translate("Layersettings", "Name of layer:", 0));
        groupBox_2->setTitle(QApplication::translate("Layersettings", "Layer Set", 0));
        pbSetSave->setText(QApplication::translate("Layersettings", "Save", 0));
        pbSetOpen->setText(QApplication::translate("Layersettings", "Open set...", 0));
        pbSetRemove->setText(QApplication::translate("Layersettings", "Remove", 0));
        pbSetAdd->setText(QApplication::translate("Layersettings", "Add", 0));
        label_7->setText(QApplication::translate("Layersettings", "Name:", 0));
    } // retranslateUi

};

namespace Ui {
    class Layersettings: public Ui_Layersettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LAYERSETTINGS_H
