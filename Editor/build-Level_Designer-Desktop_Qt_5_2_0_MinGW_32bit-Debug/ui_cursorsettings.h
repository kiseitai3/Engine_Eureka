/********************************************************************************
** Form generated from reading UI file 'cursorsettings.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CURSORSETTINGS_H
#define UI_CURSORSETTINGS_H

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

class Ui_cursorsettings
{
public:
    QGroupBox *groupBox;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLineEdit *leName;
    QLineEdit *leSound;
    QLineEdit *leTexture;
    QSpinBox *sbFrames;
    QPushButton *pbSound;
    QPushButton *pbTexture;
    QPushButton *pbCreate;
    QPushButton *pbCreateAdd;
    QGroupBox *groupBox_2;
    QPushButton *pbSaveSet;
    QPushButton *pbLoadSet;
    QPushButton *pbAdd;
    QListWidget *lstSet;
    QPushButton *pbRemove;
    QLabel *label_5;
    QLineEdit *leNameSet;

    void setupUi(QDialog *cursorsettings)
    {
        if (cursorsettings->objectName().isEmpty())
            cursorsettings->setObjectName(QStringLiteral("cursorsettings"));
        cursorsettings->resize(775, 254);
        groupBox = new QGroupBox(cursorsettings);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(0, 0, 381, 251));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 30, 41, 16));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 60, 71, 16));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 90, 51, 16));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 130, 121, 16));
        leName = new QLineEdit(groupBox);
        leName->setObjectName(QStringLiteral("leName"));
        leName->setGeometry(QRect(90, 30, 113, 22));
        leSound = new QLineEdit(groupBox);
        leSound->setObjectName(QStringLiteral("leSound"));
        leSound->setGeometry(QRect(90, 60, 161, 22));
        leTexture = new QLineEdit(groupBox);
        leTexture->setObjectName(QStringLiteral("leTexture"));
        leTexture->setGeometry(QRect(90, 90, 161, 22));
        sbFrames = new QSpinBox(groupBox);
        sbFrames->setObjectName(QStringLiteral("sbFrames"));
        sbFrames->setGeometry(QRect(140, 130, 71, 22));
        pbSound = new QPushButton(groupBox);
        pbSound->setObjectName(QStringLiteral("pbSound"));
        pbSound->setGeometry(QRect(270, 60, 93, 28));
        pbTexture = new QPushButton(groupBox);
        pbTexture->setObjectName(QStringLiteral("pbTexture"));
        pbTexture->setGeometry(QRect(270, 90, 93, 28));
        pbCreate = new QPushButton(groupBox);
        pbCreate->setObjectName(QStringLiteral("pbCreate"));
        pbCreate->setGeometry(QRect(270, 200, 93, 28));
        pbCreateAdd = new QPushButton(groupBox);
        pbCreateAdd->setObjectName(QStringLiteral("pbCreateAdd"));
        pbCreateAdd->setGeometry(QRect(92, 200, 171, 28));
        groupBox_2 = new QGroupBox(cursorsettings);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(380, 0, 381, 251));
        pbSaveSet = new QPushButton(groupBox_2);
        pbSaveSet->setObjectName(QStringLiteral("pbSaveSet"));
        pbSaveSet->setGeometry(QRect(280, 200, 93, 28));
        pbLoadSet = new QPushButton(groupBox_2);
        pbLoadSet->setObjectName(QStringLiteral("pbLoadSet"));
        pbLoadSet->setGeometry(QRect(180, 200, 93, 28));
        pbAdd = new QPushButton(groupBox_2);
        pbAdd->setObjectName(QStringLiteral("pbAdd"));
        pbAdd->setGeometry(QRect(80, 200, 93, 28));
        lstSet = new QListWidget(groupBox_2);
        lstSet->setObjectName(QStringLiteral("lstSet"));
        lstSet->setGeometry(QRect(10, 60, 361, 131));
        pbRemove = new QPushButton(groupBox_2);
        pbRemove->setObjectName(QStringLiteral("pbRemove"));
        pbRemove->setGeometry(QRect(10, 200, 61, 28));
        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(10, 20, 81, 16));
        leNameSet = new QLineEdit(groupBox_2);
        leNameSet->setObjectName(QStringLiteral("leNameSet"));
        leNameSet->setGeometry(QRect(100, 20, 113, 22));

        retranslateUi(cursorsettings);

        QMetaObject::connectSlotsByName(cursorsettings);
    } // setupUi

    void retranslateUi(QDialog *cursorsettings)
    {
        cursorsettings->setWindowTitle(QApplication::translate("cursorsettings", "Dialog", 0));
        groupBox->setTitle(QApplication::translate("cursorsettings", "Cursor Settings", 0));
        label->setText(QApplication::translate("cursorsettings", "Name:", 0));
        label_2->setText(QApplication::translate("cursorsettings", "Sound file:", 0));
        label_3->setText(QApplication::translate("cursorsettings", "Texture:", 0));
        label_4->setText(QApplication::translate("cursorsettings", "Frames per second:", 0));
        pbSound->setText(QApplication::translate("cursorsettings", "Browse", 0));
        pbTexture->setText(QApplication::translate("cursorsettings", "Browse", 0));
        pbCreate->setText(QApplication::translate("cursorsettings", "Create file", 0));
        pbCreateAdd->setText(QApplication::translate("cursorsettings", "Create file and add to set!", 0));
        groupBox_2->setTitle(QApplication::translate("cursorsettings", "Cursor set", 0));
        pbSaveSet->setText(QApplication::translate("cursorsettings", "Save", 0));
        pbLoadSet->setText(QApplication::translate("cursorsettings", "Open set...", 0));
        pbAdd->setText(QApplication::translate("cursorsettings", "Add cursor...", 0));
        pbRemove->setText(QApplication::translate("cursorsettings", "Remove", 0));
        label_5->setText(QApplication::translate("cursorsettings", "Name of set:", 0));
    } // retranslateUi

};

namespace Ui {
    class cursorsettings: public Ui_cursorsettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CURSORSETTINGS_H
