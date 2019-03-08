/********************************************************************************
** Form generated from reading UI file 'trigger_settings.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRIGGER_SETTINGS_H
#define UI_TRIGGER_SETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_trigger_settings
{
public:
    QGroupBox *groupBox;
    QLabel *label;
    QSpinBox *sbH;
    QSpinBox *sbW;
    QLabel *label_2;
    QSpinBox *sbX;
    QSpinBox *sbY;
    QLabel *label_3;
    QSpinBox *sbDuration;
    QLabel *label_4;
    QLineEdit *leName;
    QLabel *label_5;
    QLineEdit *leScript;
    QPushButton *pbScript;
    QPushButton *pbSave;

    void setupUi(QDialog *trigger_settings)
    {
        if (trigger_settings->objectName().isEmpty())
            trigger_settings->setObjectName(QStringLiteral("trigger_settings"));
        trigger_settings->resize(475, 308);
        groupBox = new QGroupBox(trigger_settings);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(0, 0, 471, 301));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 30, 121, 16));
        sbH = new QSpinBox(groupBox);
        sbH->setObjectName(QStringLiteral("sbH"));
        sbH->setGeometry(QRect(140, 30, 61, 22));
        sbH->setMaximum(999999);
        sbW = new QSpinBox(groupBox);
        sbW->setObjectName(QStringLiteral("sbW"));
        sbW->setGeometry(QRect(220, 30, 61, 22));
        sbW->setMaximum(999999);
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 80, 141, 16));
        sbX = new QSpinBox(groupBox);
        sbX->setObjectName(QStringLiteral("sbX"));
        sbX->setEnabled(false);
        sbX->setGeometry(QRect(170, 80, 61, 22));
        sbX->setMaximum(999999);
        sbY = new QSpinBox(groupBox);
        sbY->setObjectName(QStringLiteral("sbY"));
        sbY->setEnabled(false);
        sbY->setGeometry(QRect(250, 80, 61, 22));
        sbY->setMaximum(999999);
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 120, 101, 16));
        sbDuration = new QSpinBox(groupBox);
        sbDuration->setObjectName(QStringLiteral("sbDuration"));
        sbDuration->setGeometry(QRect(120, 120, 71, 22));
        sbDuration->setMaximum(999999);
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(20, 170, 91, 16));
        leName = new QLineEdit(groupBox);
        leName->setObjectName(QStringLiteral("leName"));
        leName->setGeometry(QRect(120, 170, 241, 22));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(20, 210, 91, 16));
        leScript = new QLineEdit(groupBox);
        leScript->setObjectName(QStringLiteral("leScript"));
        leScript->setGeometry(QRect(120, 210, 241, 22));
        pbScript = new QPushButton(groupBox);
        pbScript->setObjectName(QStringLiteral("pbScript"));
        pbScript->setGeometry(QRect(370, 210, 93, 28));
        pbSave = new QPushButton(groupBox);
        pbSave->setObjectName(QStringLiteral("pbSave"));
        pbSave->setGeometry(QRect(352, 260, 101, 28));

        retranslateUi(trigger_settings);

        QMetaObject::connectSlotsByName(trigger_settings);
    } // setupUi

    void retranslateUi(QDialog *trigger_settings)
    {
        trigger_settings->setWindowTitle(QApplication::translate("trigger_settings", "Dialog", 0));
        groupBox->setTitle(QApplication::translate("trigger_settings", "Trigger Settings", 0));
        label->setText(QApplication::translate("trigger_settings", "Trigger size (h x w):", 0));
        label_2->setText(QApplication::translate("trigger_settings", "Trigger location (x * y):", 0));
        label_3->setText(QApplication::translate("trigger_settings", "Trigger duration:", 0));
        label_4->setText(QApplication::translate("trigger_settings", "Trigger name: ", 0));
        label_5->setText(QApplication::translate("trigger_settings", "Trigger script:", 0));
        pbScript->setText(QApplication::translate("trigger_settings", "Browse", 0));
        pbSave->setText(QApplication::translate("trigger_settings", "Create Trigger", 0));
    } // retranslateUi

};

namespace Ui {
    class trigger_settings: public Ui_trigger_settings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRIGGER_SETTINGS_H
