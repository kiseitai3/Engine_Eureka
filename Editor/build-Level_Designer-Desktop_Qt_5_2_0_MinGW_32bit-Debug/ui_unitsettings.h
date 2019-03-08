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
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UnitSettings
{
public:
    QTabWidget *tabWidget;
    QWidget *tabStats;
    QGroupBox *groupBox;
    QSpinBox *sbAP;
    QLabel *label_3;
    QSpinBox *sbHP;
    QLabel *label;
    QLabel *label_2;
    QSpinBox *sbAD;
    QLabel *label_4;
    QDoubleSpinBox *dsbASpeed;
    QLabel *label_5;
    QSpinBox *sbVRange;
    QLabel *label_6;
    QSpinBox *sbRange;
    QSpinBox *sbMana;
    QLabel *label_7;
    QLabel *label_8;
    QLineEdit *leUnitName;
    QSpinBox *sbMSpeed;
    QLabel *label_9;
    QLabel *label_10;
    QComboBox *cbUnitType;
    QGroupBox *groupBox_2;
    QCheckBox *cbHasBars;
    QLabel *label_11;
    QLineEdit *leHPBar;
    QPushButton *pbHPBar;
    QLineEdit *leManaBar;
    QPushButton *pbManaBar;
    QLabel *label_12;
    QLabel *label_21;
    QLabel *label_22;
    QSpinBox *sbBarH;
    QSpinBox *sbBarW;
    QCheckBox *cbShowHP;
    QCheckBox *cbShowMana;
    QGroupBox *groupBox_3;
    QCheckBox *cbUnitMelee;
    QCheckBox *cbHasBuffs;
    QLineEdit *leBuffLoc;
    QPushButton *pbBuffBrowse;
    QLabel *label_13;
    QLineEdit *leGenScriptLoc;
    QPushButton *pbGenScriptBrowse;
    QLabel *label_14;
    QLineEdit *leAILoc;
    QLabel *label_15;
    QPushButton *pbAIBrowse;
    QPushButton *pbPhysicsBrowse;
    QLabel *label_20;
    QLineEdit *lePhysicsLoc;
    QPushButton *pbCreateUnit;
    QWidget *tabUnitText;
    QListWidget *lstTextures;
    QPushButton *pbBrowseTexture;
    QPushButton *pbAddTexture;
    QPushButton *pbRemTexture;
    QLineEdit *leTextLoc;
    QLineEdit *leTextName;
    QLabel *label_16;
    QLabel *label_17;
    QWidget *tab;
    QListWidget *lstSounds;
    QPushButton *pbAddSound;
    QLabel *label_18;
    QLabel *label_19;
    QPushButton *pbRemSound;
    QLineEdit *leSoundLoc;
    QPushButton *pbBrowseSound;
    QLineEdit *leSoundName;

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
        groupBox = new QGroupBox(tabStats);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(0, 0, 241, 351));
        sbAP = new QSpinBox(groupBox);
        sbAP->setObjectName(QStringLiteral("sbAP"));
        sbAP->setGeometry(QRect(40, 120, 61, 22));
        sbAP->setMinimum(1);
        sbAP->setMaximum(99999);
        sbAP->setSingleStep(10);
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 120, 21, 16));
        sbHP = new QSpinBox(groupBox);
        sbHP->setObjectName(QStringLiteral("sbHP"));
        sbHP->setGeometry(QRect(40, 30, 61, 22));
        sbHP->setMinimum(1);
        sbHP->setMaximum(99999);
        sbHP->setSingleStep(10);
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 30, 21, 16));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 90, 21, 16));
        sbAD = new QSpinBox(groupBox);
        sbAD->setObjectName(QStringLiteral("sbAD"));
        sbAD->setGeometry(QRect(40, 90, 61, 22));
        sbAD->setMinimum(1);
        sbAD->setMaximum(99999);
        sbAD->setSingleStep(10);
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 150, 81, 16));
        dsbASpeed = new QDoubleSpinBox(groupBox);
        dsbASpeed->setObjectName(QStringLiteral("dsbASpeed"));
        dsbASpeed->setGeometry(QRect(100, 150, 62, 22));
        dsbASpeed->setMaximum(999999);
        dsbASpeed->setSingleStep(0.01);
        dsbASpeed->setValue(1);
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(10, 180, 81, 16));
        sbVRange = new QSpinBox(groupBox);
        sbVRange->setObjectName(QStringLiteral("sbVRange"));
        sbVRange->setGeometry(QRect(100, 180, 61, 22));
        sbVRange->setMinimum(1);
        sbVRange->setMaximum(99999);
        sbVRange->setSingleStep(10);
        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(10, 210, 81, 16));
        sbRange = new QSpinBox(groupBox);
        sbRange->setObjectName(QStringLiteral("sbRange"));
        sbRange->setGeometry(QRect(100, 210, 61, 22));
        sbRange->setMinimum(1);
        sbRange->setMaximum(99999);
        sbRange->setSingleStep(10);
        sbMana = new QSpinBox(groupBox);
        sbMana->setObjectName(QStringLiteral("sbMana"));
        sbMana->setGeometry(QRect(50, 60, 61, 22));
        sbMana->setMinimum(1);
        sbMana->setMaximum(99999);
        sbMana->setSingleStep(10);
        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(10, 60, 41, 16));
        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(10, 280, 71, 16));
        leUnitName = new QLineEdit(groupBox);
        leUnitName->setObjectName(QStringLiteral("leUnitName"));
        leUnitName->setGeometry(QRect(80, 280, 141, 22));
        sbMSpeed = new QSpinBox(groupBox);
        sbMSpeed->setObjectName(QStringLiteral("sbMSpeed"));
        sbMSpeed->setGeometry(QRect(120, 240, 61, 22));
        sbMSpeed->setMinimum(1);
        sbMSpeed->setMaximum(99999);
        sbMSpeed->setSingleStep(10);
        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(10, 240, 111, 16));
        label_10 = new QLabel(groupBox);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(10, 310, 55, 16));
        cbUnitType = new QComboBox(groupBox);
        cbUnitType->setObjectName(QStringLiteral("cbUnitType"));
        cbUnitType->setGeometry(QRect(80, 310, 141, 22));
        groupBox_2 = new QGroupBox(tabStats);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(0, 350, 661, 111));
        cbHasBars = new QCheckBox(groupBox_2);
        cbHasBars->setObjectName(QStringLiteral("cbHasBars"));
        cbHasBars->setGeometry(QRect(10, 20, 191, 20));
        label_11 = new QLabel(groupBox_2);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(10, 50, 91, 16));
        leHPBar = new QLineEdit(groupBox_2);
        leHPBar->setObjectName(QStringLiteral("leHPBar"));
        leHPBar->setEnabled(false);
        leHPBar->setGeometry(QRect(110, 50, 291, 22));
        pbHPBar = new QPushButton(groupBox_2);
        pbHPBar->setObjectName(QStringLiteral("pbHPBar"));
        pbHPBar->setEnabled(false);
        pbHPBar->setGeometry(QRect(410, 50, 93, 28));
        leManaBar = new QLineEdit(groupBox_2);
        leManaBar->setObjectName(QStringLiteral("leManaBar"));
        leManaBar->setEnabled(false);
        leManaBar->setGeometry(QRect(120, 80, 281, 22));
        pbManaBar = new QPushButton(groupBox_2);
        pbManaBar->setObjectName(QStringLiteral("pbManaBar"));
        pbManaBar->setEnabled(false);
        pbManaBar->setGeometry(QRect(410, 80, 93, 28));
        label_12 = new QLabel(groupBox_2);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(10, 80, 111, 16));
        label_21 = new QLabel(groupBox_2);
        label_21->setObjectName(QStringLiteral("label_21"));
        label_21->setGeometry(QRect(510, 50, 71, 16));
        label_22 = new QLabel(groupBox_2);
        label_22->setObjectName(QStringLiteral("label_22"));
        label_22->setGeometry(QRect(510, 80, 71, 16));
        sbBarH = new QSpinBox(groupBox_2);
        sbBarH->setObjectName(QStringLiteral("sbBarH"));
        sbBarH->setEnabled(false);
        sbBarH->setGeometry(QRect(590, 50, 71, 22));
        sbBarH->setMaximum(99999);
        sbBarW = new QSpinBox(groupBox_2);
        sbBarW->setObjectName(QStringLiteral("sbBarW"));
        sbBarW->setEnabled(false);
        sbBarW->setGeometry(QRect(590, 80, 71, 22));
        sbBarW->setMaximum(99999);
        cbShowHP = new QCheckBox(groupBox_2);
        cbShowHP->setObjectName(QStringLiteral("cbShowHP"));
        cbShowHP->setEnabled(false);
        cbShowHP->setGeometry(QRect(250, 20, 191, 20));
        cbShowMana = new QCheckBox(groupBox_2);
        cbShowMana->setObjectName(QStringLiteral("cbShowMana"));
        cbShowMana->setEnabled(false);
        cbShowMana->setGeometry(QRect(460, 20, 191, 20));
        groupBox_3 = new QGroupBox(tabStats);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(250, 0, 551, 351));
        cbUnitMelee = new QCheckBox(groupBox_3);
        cbUnitMelee->setObjectName(QStringLiteral("cbUnitMelee"));
        cbUnitMelee->setGeometry(QRect(10, 30, 111, 20));
        cbHasBuffs = new QCheckBox(groupBox_3);
        cbHasBuffs->setObjectName(QStringLiteral("cbHasBuffs"));
        cbHasBuffs->setGeometry(QRect(10, 60, 111, 20));
        leBuffLoc = new QLineEdit(groupBox_3);
        leBuffLoc->setObjectName(QStringLiteral("leBuffLoc"));
        leBuffLoc->setGeometry(QRect(100, 90, 321, 22));
        pbBuffBrowse = new QPushButton(groupBox_3);
        pbBuffBrowse->setObjectName(QStringLiteral("pbBuffBrowse"));
        pbBuffBrowse->setGeometry(QRect(432, 90, 81, 28));
        label_13 = new QLabel(groupBox_3);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(0, 130, 91, 16));
        leGenScriptLoc = new QLineEdit(groupBox_3);
        leGenScriptLoc->setObjectName(QStringLiteral("leGenScriptLoc"));
        leGenScriptLoc->setGeometry(QRect(100, 130, 321, 22));
        pbGenScriptBrowse = new QPushButton(groupBox_3);
        pbGenScriptBrowse->setObjectName(QStringLiteral("pbGenScriptBrowse"));
        pbGenScriptBrowse->setGeometry(QRect(430, 130, 81, 28));
        label_14 = new QLabel(groupBox_3);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(0, 90, 91, 16));
        leAILoc = new QLineEdit(groupBox_3);
        leAILoc->setObjectName(QStringLiteral("leAILoc"));
        leAILoc->setGeometry(QRect(100, 170, 321, 22));
        label_15 = new QLabel(groupBox_3);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(0, 170, 91, 16));
        pbAIBrowse = new QPushButton(groupBox_3);
        pbAIBrowse->setObjectName(QStringLiteral("pbAIBrowse"));
        pbAIBrowse->setGeometry(QRect(430, 170, 81, 28));
        pbPhysicsBrowse = new QPushButton(groupBox_3);
        pbPhysicsBrowse->setObjectName(QStringLiteral("pbPhysicsBrowse"));
        pbPhysicsBrowse->setGeometry(QRect(430, 210, 81, 28));
        label_20 = new QLabel(groupBox_3);
        label_20->setObjectName(QStringLiteral("label_20"));
        label_20->setGeometry(QRect(0, 210, 91, 16));
        lePhysicsLoc = new QLineEdit(groupBox_3);
        lePhysicsLoc->setObjectName(QStringLiteral("lePhysicsLoc"));
        lePhysicsLoc->setGeometry(QRect(100, 210, 321, 22));
        pbCreateUnit = new QPushButton(tabStats);
        pbCreateUnit->setObjectName(QStringLiteral("pbCreateUnit"));
        pbCreateUnit->setGeometry(QRect(680, 360, 191, 101));
        tabWidget->addTab(tabStats, QString());
        tabUnitText = new QWidget();
        tabUnitText->setObjectName(QStringLiteral("tabUnitText"));
        lstTextures = new QListWidget(tabUnitText);
        lstTextures->setObjectName(QStringLiteral("lstTextures"));
        lstTextures->setGeometry(QRect(10, 0, 901, 411));
        pbBrowseTexture = new QPushButton(tabUnitText);
        pbBrowseTexture->setObjectName(QStringLiteral("pbBrowseTexture"));
        pbBrowseTexture->setGeometry(QRect(530, 420, 93, 28));
        pbAddTexture = new QPushButton(tabUnitText);
        pbAddTexture->setObjectName(QStringLiteral("pbAddTexture"));
        pbAddTexture->setGeometry(QRect(700, 420, 93, 28));
        pbRemTexture = new QPushButton(tabUnitText);
        pbRemTexture->setObjectName(QStringLiteral("pbRemTexture"));
        pbRemTexture->setGeometry(QRect(802, 420, 111, 28));
        leTextLoc = new QLineEdit(tabUnitText);
        leTextLoc->setObjectName(QStringLiteral("leTextLoc"));
        leTextLoc->setGeometry(QRect(212, 420, 311, 22));
        leTextName = new QLineEdit(tabUnitText);
        leTextName->setObjectName(QStringLiteral("leTextName"));
        leTextName->setGeometry(QRect(210, 450, 311, 22));
        label_16 = new QLabel(tabUnitText);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setGeometry(QRect(90, 420, 121, 16));
        label_17 = new QLabel(tabUnitText);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setGeometry(QRect(90, 450, 121, 16));
        tabWidget->addTab(tabUnitText, QString());
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        lstSounds = new QListWidget(tab);
        lstSounds->setObjectName(QStringLiteral("lstSounds"));
        lstSounds->setGeometry(QRect(8, 0, 901, 411));
        pbAddSound = new QPushButton(tab);
        pbAddSound->setObjectName(QStringLiteral("pbAddSound"));
        pbAddSound->setGeometry(QRect(698, 420, 93, 28));
        label_18 = new QLabel(tab);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setGeometry(QRect(88, 420, 121, 16));
        label_19 = new QLabel(tab);
        label_19->setObjectName(QStringLiteral("label_19"));
        label_19->setGeometry(QRect(88, 450, 121, 16));
        pbRemSound = new QPushButton(tab);
        pbRemSound->setObjectName(QStringLiteral("pbRemSound"));
        pbRemSound->setGeometry(QRect(800, 420, 111, 28));
        leSoundLoc = new QLineEdit(tab);
        leSoundLoc->setObjectName(QStringLiteral("leSoundLoc"));
        leSoundLoc->setGeometry(QRect(210, 420, 311, 22));
        pbBrowseSound = new QPushButton(tab);
        pbBrowseSound->setObjectName(QStringLiteral("pbBrowseSound"));
        pbBrowseSound->setGeometry(QRect(528, 420, 93, 28));
        leSoundName = new QLineEdit(tab);
        leSoundName->setObjectName(QStringLiteral("leSoundName"));
        leSoundName->setGeometry(QRect(208, 450, 311, 22));
        tabWidget->addTab(tab, QString());

        retranslateUi(UnitSettings);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(UnitSettings);
    } // setupUi

    void retranslateUi(QDialog *UnitSettings)
    {
        UnitSettings->setWindowTitle(QApplication::translate("UnitSettings", "Dialog", 0));
        groupBox->setTitle(QApplication::translate("UnitSettings", "Base Stats", 0));
        sbAP->setSuffix(QString());
        label_3->setText(QApplication::translate("UnitSettings", "AP:", 0));
        sbHP->setSuffix(QString());
        label->setText(QApplication::translate("UnitSettings", "HP:", 0));
        label_2->setText(QApplication::translate("UnitSettings", "AD:", 0));
        sbAD->setSuffix(QString());
        label_4->setText(QApplication::translate("UnitSettings", "Attack Speed:", 0));
        label_5->setText(QApplication::translate("UnitSettings", "Vision Range:", 0));
        sbVRange->setSuffix(QString());
        label_6->setText(QApplication::translate("UnitSettings", "Attack Range:", 0));
        sbRange->setSuffix(QString());
        sbMana->setSuffix(QString());
        label_7->setText(QApplication::translate("UnitSettings", "Mana:", 0));
        label_8->setText(QApplication::translate("UnitSettings", "Unit name:", 0));
        sbMSpeed->setSuffix(QString());
        label_9->setText(QApplication::translate("UnitSettings", "Movement Speed:", 0));
        label_10->setText(QApplication::translate("UnitSettings", "Unit type:", 0));
        cbUnitType->clear();
        cbUnitType->insertItems(0, QStringList()
         << QApplication::translate("UnitSettings", "Unit (u)", 0)
         << QApplication::translate("UnitSettings", "Environment object (o)", 0)
         << QApplication::translate("UnitSettings", "Projectile (p)", 0)
        );
        groupBox_2->setTitle(QApplication::translate("UnitSettings", "Bars", 0));
        cbHasBars->setText(QApplication::translate("UnitSettings", "Unit has hp and mana bars?", 0));
        label_11->setText(QApplication::translate("UnitSettings", "HP bar texture:", 0));
        pbHPBar->setText(QApplication::translate("UnitSettings", "Browse", 0));
        pbManaBar->setText(QApplication::translate("UnitSettings", "Browse", 0));
        label_12->setText(QApplication::translate("UnitSettings", "Mana bar texture:", 0));
        label_21->setText(QApplication::translate("UnitSettings", "Bar Height:", 0));
        label_22->setText(QApplication::translate("UnitSettings", "Bar Width:", 0));
        cbShowHP->setText(QApplication::translate("UnitSettings", "Show HP Bar?", 0));
        cbShowMana->setText(QApplication::translate("UnitSettings", "Show Mana Bar?", 0));
        groupBox_3->setTitle(QApplication::translate("UnitSettings", "Other options", 0));
        cbUnitMelee->setText(QApplication::translate("UnitSettings", "Unit is melee?", 0));
        cbHasBuffs->setText(QApplication::translate("UnitSettings", "Unit has buffs?", 0));
        pbBuffBrowse->setText(QApplication::translate("UnitSettings", "Browse", 0));
        label_13->setText(QApplication::translate("UnitSettings", "General Script:", 0));
        pbGenScriptBrowse->setText(QApplication::translate("UnitSettings", "Browse", 0));
        label_14->setText(QApplication::translate("UnitSettings", "Buff Script:", 0));
        label_15->setText(QApplication::translate("UnitSettings", "AI Script:", 0));
        pbAIBrowse->setText(QApplication::translate("UnitSettings", "Browse", 0));
        pbPhysicsBrowse->setText(QApplication::translate("UnitSettings", "Browse", 0));
        label_20->setText(QApplication::translate("UnitSettings", "Physics:", 0));
        pbCreateUnit->setText(QApplication::translate("UnitSettings", "Create Unit", 0));
        tabWidget->setTabText(tabWidget->indexOf(tabStats), QApplication::translate("UnitSettings", "Unit Stats", 0));
        pbBrowseTexture->setText(QApplication::translate("UnitSettings", "Browse", 0));
        pbAddTexture->setText(QApplication::translate("UnitSettings", "Add", 0));
        pbRemTexture->setText(QApplication::translate("UnitSettings", "Remove Selected", 0));
        label_16->setText(QApplication::translate("UnitSettings", "Location of Texture:", 0));
        label_17->setText(QApplication::translate("UnitSettings", "Name of Texture:", 0));
        tabWidget->setTabText(tabWidget->indexOf(tabUnitText), QApplication::translate("UnitSettings", "Unit Textures", 0));
        pbAddSound->setText(QApplication::translate("UnitSettings", "Add", 0));
        label_18->setText(QApplication::translate("UnitSettings", "Location of Texture:", 0));
        label_19->setText(QApplication::translate("UnitSettings", "Name of Texture:", 0));
        pbRemSound->setText(QApplication::translate("UnitSettings", "Remove Selected", 0));
        pbBrowseSound->setText(QApplication::translate("UnitSettings", "Browse", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("UnitSettings", "Unit Sounds", 0));
    } // retranslateUi

};

namespace Ui {
    class UnitSettings: public Ui_UnitSettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UNITSETTINGS_H
