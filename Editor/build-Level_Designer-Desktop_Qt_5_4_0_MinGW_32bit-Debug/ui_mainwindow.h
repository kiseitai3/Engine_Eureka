/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_Exit;
    QAction *actionInstall_mod;
    QWidget *centralWidget;
    QWidget *gridLayoutWidget;
    QGridLayout *gLWindow;
    QTabWidget *twTabs;
    QWidget *tabGeneral;
    QGroupBox *groupBox;
    QLineEdit *leMod;
    QLineEdit *leModInstall;
    QLabel *label;
    QLabel *label_2;
    QPushButton *pbModBrowse;
    QPushButton *pBInstallBrowse;
    QLineEdit *lineEdit;
    QLabel *label_26;
    QGroupBox *groupBox_2;
    QLabel *label_3;
    QLineEdit *leModName;
    QLabel *label_4;
    QTextEdit *teModDescription;
    QPushButton *pbModSave;
    QWidget *tabRegisterAssets;
    QGroupBox *groupBox_3;
    QPushButton *pbTextureBrowse;
    QLineEdit *leTexturePath;
    QLabel *label_5;
    QSpinBox *sbHeight;
    QLabel *label_6;
    QSpinBox *sbWidth;
    QLabel *label_7;
    QSpinBox *sbFrames;
    QLabel *label_8;
    QSpinBox *sbAnimCounter;
    QLabel *label_9;
    QSpinBox *sbTimePerFrame;
    QLabel *label_10;
    QSpinBox *sbAnimNum;
    QLabel *label_11;
    QSpinBox *sbLoop;
    QPushButton *pbRegTexture;
    QLabel *label_12;
    QLineEdit *leTexName;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout;
    QGroupBox *groupBox_5;
    QComboBox *comboBox;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_15;
    QSpinBox *spinBox;
    QSpinBox *spinBox_2;
    QLabel *label_16;
    QLabel *label_17;
    QLineEdit *leSoundLoc;
    QPushButton *pbSoundBrowse;
    QPushButton *pbRegSound;
    QGroupBox *groupBox_6;
    QLabel *label_18;
    QLineEdit *leCodeLoc;
    QPushButton *pbCodeBrowse;
    QPushButton *pbRegCode;
    QLabel *label_19;
    QComboBox *comboBox_2;
    QGroupBox *groupBox_7;
    QLabel *lbTextInfo;
    QGraphicsView *gvTexturePreview;
    QGroupBox *groupBox_8;
    QLabel *label_20;
    QLabel *label_21;
    QLineEdit *lePhysName;
    QSpinBox *sbMass;
    QLabel *label_22;
    QSpinBox *sbCharge;
    QLabel *label_23;
    QDoubleSpinBox *doubleSpinBox;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;
    QLabel *label_24;
    QSpinBox *spinBox_3;
    QLabel *label_25;
    QDoubleSpinBox *doubleSpinBox_2;
    QPushButton *pbRegPhys;
    QWidget *tabAssets;
    QGroupBox *gbBaseAssets;
    QTreeView *tvBaseAssets;
    QPushButton *pbDelAsset;
    QGroupBox *gbRegisteredObjects;
    QTreeView *tvRegisteredObjects;
    QPushButton *pbNewObj;
    QPushButton *pbDelObj;
    QComboBox *cbObjType;
    QWidget *tabDesigner;
    QGroupBox *gbObjects;
    QTreeView *tvObjList;
    QPushButton *pushButton_4;
    QGroupBox *gbGamePreview;
    QGraphicsView *gvGamePreview;
    QWidget *tabUIDesigner;
    QGroupBox *groupBox_4;
    QTreeView *treeView;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QMenuBar *menuBar;
    QMenu *menu_File;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1019, 653);
        action_Exit = new QAction(MainWindow);
        action_Exit->setObjectName(QStringLiteral("action_Exit"));
        actionInstall_mod = new QAction(MainWindow);
        actionInstall_mod->setObjectName(QStringLiteral("actionInstall_mod"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayoutWidget = new QWidget(centralWidget);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(0, 0, 1021, 601));
        gLWindow = new QGridLayout(gridLayoutWidget);
        gLWindow->setSpacing(6);
        gLWindow->setContentsMargins(11, 11, 11, 11);
        gLWindow->setObjectName(QStringLiteral("gLWindow"));
        gLWindow->setSizeConstraint(QLayout::SetNoConstraint);
        gLWindow->setContentsMargins(0, 0, 0, 0);
        twTabs = new QTabWidget(gridLayoutWidget);
        twTabs->setObjectName(QStringLiteral("twTabs"));
        tabGeneral = new QWidget();
        tabGeneral->setObjectName(QStringLiteral("tabGeneral"));
        groupBox = new QGroupBox(tabGeneral);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 501, 211));
        leMod = new QLineEdit(groupBox);
        leMod->setObjectName(QStringLiteral("leMod"));
        leMod->setGeometry(QRect(10, 40, 371, 20));
        leModInstall = new QLineEdit(groupBox);
        leModInstall->setObjectName(QStringLiteral("leModInstall"));
        leModInstall->setGeometry(QRect(10, 110, 371, 20));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 20, 221, 16));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 90, 281, 16));
        pbModBrowse = new QPushButton(groupBox);
        pbModBrowse->setObjectName(QStringLiteral("pbModBrowse"));
        pbModBrowse->setGeometry(QRect(400, 40, 75, 23));
        pBInstallBrowse = new QPushButton(groupBox);
        pBInstallBrowse->setObjectName(QStringLiteral("pBInstallBrowse"));
        pBInstallBrowse->setGeometry(QRect(400, 110, 75, 23));
        lineEdit = new QLineEdit(groupBox);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(10, 170, 281, 22));
        lineEdit->setReadOnly(true);
        label_26 = new QLabel(groupBox);
        label_26->setObjectName(QStringLiteral("label_26"));
        label_26->setGeometry(QRect(10, 150, 71, 16));
        groupBox_2 = new QGroupBox(tabGeneral);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 240, 501, 251));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 30, 321, 16));
        leModName = new QLineEdit(groupBox_2);
        leModName->setObjectName(QStringLiteral("leModName"));
        leModName->setGeometry(QRect(10, 50, 291, 20));
        leModName->setReadOnly(true);
        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 80, 321, 16));
        teModDescription = new QTextEdit(groupBox_2);
        teModDescription->setObjectName(QStringLiteral("teModDescription"));
        teModDescription->setGeometry(QRect(10, 100, 471, 131));
        pbModSave = new QPushButton(tabGeneral);
        pbModSave->setObjectName(QStringLiteral("pbModSave"));
        pbModSave->setGeometry(QRect(10, 500, 181, 31));
        twTabs->addTab(tabGeneral, QString());
        tabRegisterAssets = new QWidget();
        tabRegisterAssets->setObjectName(QStringLiteral("tabRegisterAssets"));
        groupBox_3 = new QGroupBox(tabRegisterAssets);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(0, 0, 431, 241));
        pbTextureBrowse = new QPushButton(groupBox_3);
        pbTextureBrowse->setObjectName(QStringLiteral("pbTextureBrowse"));
        pbTextureBrowse->setGeometry(QRect(320, 20, 75, 23));
        leTexturePath = new QLineEdit(groupBox_3);
        leTexturePath->setObjectName(QStringLiteral("leTexturePath"));
        leTexturePath->setGeometry(QRect(10, 20, 291, 20));
        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(20, 50, 231, 16));
        sbHeight = new QSpinBox(groupBox_3);
        sbHeight->setObjectName(QStringLiteral("sbHeight"));
        sbHeight->setGeometry(QRect(250, 50, 42, 22));
        sbHeight->setMaximum(99999999);
        label_6 = new QLabel(groupBox_3);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(300, 50, 16, 16));
        sbWidth = new QSpinBox(groupBox_3);
        sbWidth->setObjectName(QStringLiteral("sbWidth"));
        sbWidth->setGeometry(QRect(320, 50, 42, 22));
        sbWidth->setMaximum(99999999);
        label_7 = new QLabel(groupBox_3);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(20, 90, 61, 16));
        sbFrames = new QSpinBox(groupBox_3);
        sbFrames->setObjectName(QStringLiteral("sbFrames"));
        sbFrames->setGeometry(QRect(90, 90, 42, 22));
        sbFrames->setMaximum(99999999);
        label_8 = new QLabel(groupBox_3);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(150, 90, 231, 16));
        sbAnimCounter = new QSpinBox(groupBox_3);
        sbAnimCounter->setObjectName(QStringLiteral("sbAnimCounter"));
        sbAnimCounter->setGeometry(QRect(380, 90, 42, 22));
        sbAnimCounter->setMaximum(99999999);
        label_9 = new QLabel(groupBox_3);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(20, 120, 241, 16));
        sbTimePerFrame = new QSpinBox(groupBox_3);
        sbTimePerFrame->setObjectName(QStringLiteral("sbTimePerFrame"));
        sbTimePerFrame->setGeometry(QRect(260, 120, 42, 22));
        sbTimePerFrame->setMaximum(99999999);
        label_10 = new QLabel(groupBox_3);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(20, 150, 191, 16));
        sbAnimNum = new QSpinBox(groupBox_3);
        sbAnimNum->setObjectName(QStringLiteral("sbAnimNum"));
        sbAnimNum->setGeometry(QRect(210, 150, 42, 22));
        label_11 = new QLabel(groupBox_3);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(20, 180, 181, 16));
        sbLoop = new QSpinBox(groupBox_3);
        sbLoop->setObjectName(QStringLiteral("sbLoop"));
        sbLoop->setGeometry(QRect(200, 180, 42, 22));
        sbLoop->setMaximum(1);
        pbRegTexture = new QPushButton(groupBox_3);
        pbRegTexture->setObjectName(QStringLiteral("pbRegTexture"));
        pbRegTexture->setGeometry(QRect(330, 202, 75, 31));
        label_12 = new QLabel(groupBox_3);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(20, 210, 131, 16));
        leTexName = new QLineEdit(groupBox_3);
        leTexName->setObjectName(QStringLiteral("leTexName"));
        leTexName->setGeometry(QRect(150, 210, 161, 20));
        gridLayoutWidget_2 = new QWidget(tabRegisterAssets);
        gridLayoutWidget_2->setObjectName(QStringLiteral("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(0, 0, 2, 2));
        gridLayout = new QGridLayout(gridLayoutWidget_2);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetNoConstraint);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        groupBox_5 = new QGroupBox(tabRegisterAssets);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        groupBox_5->setGeometry(QRect(0, 250, 431, 151));
        comboBox = new QComboBox(groupBox_5);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(90, 20, 101, 22));
        label_13 = new QLabel(groupBox_5);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(10, 20, 71, 16));
        label_14 = new QLabel(groupBox_5);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(10, 50, 101, 16));
        label_15 = new QLabel(groupBox_5);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(120, 50, 21, 16));
        spinBox = new QSpinBox(groupBox_5);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setGeometry(QRect(150, 50, 42, 22));
        spinBox->setMaximum(99999999);
        spinBox_2 = new QSpinBox(groupBox_5);
        spinBox_2->setObjectName(QStringLiteral("spinBox_2"));
        spinBox_2->setGeometry(QRect(230, 50, 42, 22));
        spinBox_2->setMaximum(99999999);
        label_16 = new QLabel(groupBox_5);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setGeometry(QRect(200, 50, 21, 16));
        label_17 = new QLabel(groupBox_5);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setGeometry(QRect(10, 80, 71, 16));
        leSoundLoc = new QLineEdit(groupBox_5);
        leSoundLoc->setObjectName(QStringLiteral("leSoundLoc"));
        leSoundLoc->setGeometry(QRect(80, 80, 191, 22));
        pbSoundBrowse = new QPushButton(groupBox_5);
        pbSoundBrowse->setObjectName(QStringLiteral("pbSoundBrowse"));
        pbSoundBrowse->setGeometry(QRect(290, 80, 93, 28));
        pbRegSound = new QPushButton(groupBox_5);
        pbRegSound->setObjectName(QStringLiteral("pbRegSound"));
        pbRegSound->setGeometry(QRect(290, 120, 93, 28));
        groupBox_6 = new QGroupBox(tabRegisterAssets);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        groupBox_6->setGeometry(QRect(0, 410, 431, 81));
        label_18 = new QLabel(groupBox_6);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setGeometry(QRect(10, 20, 51, 16));
        leCodeLoc = new QLineEdit(groupBox_6);
        leCodeLoc->setObjectName(QStringLiteral("leCodeLoc"));
        leCodeLoc->setGeometry(QRect(70, 20, 251, 22));
        pbCodeBrowse = new QPushButton(groupBox_6);
        pbCodeBrowse->setObjectName(QStringLiteral("pbCodeBrowse"));
        pbCodeBrowse->setGeometry(QRect(330, 10, 93, 31));
        pbRegCode = new QPushButton(groupBox_6);
        pbRegCode->setObjectName(QStringLiteral("pbRegCode"));
        pbRegCode->setGeometry(QRect(330, 50, 93, 28));
        label_19 = new QLabel(groupBox_6);
        label_19->setObjectName(QStringLiteral("label_19"));
        label_19->setGeometry(QRect(10, 50, 31, 16));
        comboBox_2 = new QComboBox(groupBox_6);
        comboBox_2->setObjectName(QStringLiteral("comboBox_2"));
        comboBox_2->setGeometry(QRect(70, 50, 191, 22));
        groupBox_7 = new QGroupBox(tabRegisterAssets);
        groupBox_7->setObjectName(QStringLiteral("groupBox_7"));
        groupBox_7->setGeometry(QRect(430, 0, 571, 241));
        lbTextInfo = new QLabel(groupBox_7);
        lbTextInfo->setObjectName(QStringLiteral("lbTextInfo"));
        lbTextInfo->setGeometry(QRect(10, 20, 551, 16));
        gvTexturePreview = new QGraphicsView(groupBox_7);
        gvTexturePreview->setObjectName(QStringLiteral("gvTexturePreview"));
        gvTexturePreview->setGeometry(QRect(10, 50, 551, 181));
        groupBox_8 = new QGroupBox(tabRegisterAssets);
        groupBox_8->setObjectName(QStringLiteral("groupBox_8"));
        groupBox_8->setGeometry(QRect(440, 250, 541, 171));
        label_20 = new QLabel(groupBox_8);
        label_20->setObjectName(QStringLiteral("label_20"));
        label_20->setGeometry(QRect(10, 50, 41, 16));
        label_21 = new QLabel(groupBox_8);
        label_21->setObjectName(QStringLiteral("label_21"));
        label_21->setGeometry(QRect(10, 20, 101, 16));
        lePhysName = new QLineEdit(groupBox_8);
        lePhysName->setObjectName(QStringLiteral("lePhysName"));
        lePhysName->setGeometry(QRect(120, 20, 301, 21));
        sbMass = new QSpinBox(groupBox_8);
        sbMass->setObjectName(QStringLiteral("sbMass"));
        sbMass->setGeometry(QRect(60, 50, 42, 22));
        label_22 = new QLabel(groupBox_8);
        label_22->setObjectName(QStringLiteral("label_22"));
        label_22->setGeometry(QRect(10, 80, 51, 16));
        sbCharge = new QSpinBox(groupBox_8);
        sbCharge->setObjectName(QStringLiteral("sbCharge"));
        sbCharge->setGeometry(QRect(60, 80, 42, 22));
        label_23 = new QLabel(groupBox_8);
        label_23->setObjectName(QStringLiteral("label_23"));
        label_23->setGeometry(QRect(10, 110, 31, 16));
        doubleSpinBox = new QDoubleSpinBox(groupBox_8);
        doubleSpinBox->setObjectName(QStringLiteral("doubleSpinBox"));
        doubleSpinBox->setGeometry(QRect(60, 110, 51, 22));
        checkBox = new QCheckBox(groupBox_8);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setGeometry(QRect(120, 50, 171, 20));
        checkBox->setChecked(true);
        checkBox_2 = new QCheckBox(groupBox_8);
        checkBox_2->setObjectName(QStringLiteral("checkBox_2"));
        checkBox_2->setGeometry(QRect(120, 80, 251, 20));
        checkBox_2->setChecked(true);
        label_24 = new QLabel(groupBox_8);
        label_24->setObjectName(QStringLiteral("label_24"));
        label_24->setGeometry(QRect(120, 110, 171, 16));
        spinBox_3 = new QSpinBox(groupBox_8);
        spinBox_3->setObjectName(QStringLiteral("spinBox_3"));
        spinBox_3->setGeometry(QRect(300, 110, 42, 22));
        label_25 = new QLabel(groupBox_8);
        label_25->setObjectName(QStringLiteral("label_25"));
        label_25->setGeometry(QRect(10, 140, 131, 16));
        doubleSpinBox_2 = new QDoubleSpinBox(groupBox_8);
        doubleSpinBox_2->setObjectName(QStringLiteral("doubleSpinBox_2"));
        doubleSpinBox_2->setGeometry(QRect(150, 140, 71, 22));
        pbRegPhys = new QPushButton(groupBox_8);
        pbRegPhys->setObjectName(QStringLiteral("pbRegPhys"));
        pbRegPhys->setGeometry(QRect(440, 130, 93, 28));
        twTabs->addTab(tabRegisterAssets, QString());
        tabAssets = new QWidget();
        tabAssets->setObjectName(QStringLiteral("tabAssets"));
        gbBaseAssets = new QGroupBox(tabAssets);
        gbBaseAssets->setObjectName(QStringLiteral("gbBaseAssets"));
        gbBaseAssets->setGeometry(QRect(0, 10, 481, 551));
        tvBaseAssets = new QTreeView(gbBaseAssets);
        tvBaseAssets->setObjectName(QStringLiteral("tvBaseAssets"));
        tvBaseAssets->setGeometry(QRect(10, 20, 461, 441));
        tvBaseAssets->setUniformRowHeights(false);
        tvBaseAssets->setWordWrap(true);
        pbDelAsset = new QPushButton(gbBaseAssets);
        pbDelAsset->setObjectName(QStringLiteral("pbDelAsset"));
        pbDelAsset->setGeometry(QRect(10, 470, 151, 28));
        gbRegisteredObjects = new QGroupBox(tabAssets);
        gbRegisteredObjects->setObjectName(QStringLiteral("gbRegisteredObjects"));
        gbRegisteredObjects->setGeometry(QRect(490, 10, 511, 551));
        tvRegisteredObjects = new QTreeView(gbRegisteredObjects);
        tvRegisteredObjects->setObjectName(QStringLiteral("tvRegisteredObjects"));
        tvRegisteredObjects->setGeometry(QRect(10, 20, 491, 441));
        pbNewObj = new QPushButton(gbRegisteredObjects);
        pbNewObj->setObjectName(QStringLiteral("pbNewObj"));
        pbNewObj->setGeometry(QRect(370, 470, 131, 28));
        pbDelObj = new QPushButton(gbRegisteredObjects);
        pbDelObj->setObjectName(QStringLiteral("pbDelObj"));
        pbDelObj->setGeometry(QRect(10, 510, 161, 28));
        cbObjType = new QComboBox(gbRegisteredObjects);
        cbObjType->setObjectName(QStringLiteral("cbObjType"));
        cbObjType->setGeometry(QRect(10, 470, 351, 22));
        twTabs->addTab(tabAssets, QString());
        tabDesigner = new QWidget();
        tabDesigner->setObjectName(QStringLiteral("tabDesigner"));
        gbObjects = new QGroupBox(tabDesigner);
        gbObjects->setObjectName(QStringLiteral("gbObjects"));
        gbObjects->setGeometry(QRect(0, 0, 281, 561));
        tvObjList = new QTreeView(gbObjects);
        tvObjList->setObjectName(QStringLiteral("tvObjList"));
        tvObjList->setGeometry(QRect(0, 20, 281, 501));
        tvObjList->setUniformRowHeights(true);
        tvObjList->setSortingEnabled(false);
        tvObjList->setAnimated(true);
        tvObjList->setWordWrap(true);
        pushButton_4 = new QPushButton(gbObjects);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setGeometry(QRect(10, 530, 93, 28));
        gbGamePreview = new QGroupBox(tabDesigner);
        gbGamePreview->setObjectName(QStringLiteral("gbGamePreview"));
        gbGamePreview->setGeometry(QRect(290, 0, 721, 561));
        gvGamePreview = new QGraphicsView(gbGamePreview);
        gvGamePreview->setObjectName(QStringLiteral("gvGamePreview"));
        gvGamePreview->setGeometry(QRect(0, 20, 711, 531));
        gvGamePreview->setAcceptDrops(false);
        gvGamePreview->setRenderHints(QPainter::Antialiasing|QPainter::HighQualityAntialiasing|QPainter::SmoothPixmapTransform|QPainter::TextAntialiasing);
        twTabs->addTab(tabDesigner, QString());
        tabUIDesigner = new QWidget();
        tabUIDesigner->setObjectName(QStringLiteral("tabUIDesigner"));
        groupBox_4 = new QGroupBox(tabUIDesigner);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(0, 10, 261, 551));
        treeView = new QTreeView(groupBox_4);
        treeView->setObjectName(QStringLiteral("treeView"));
        treeView->setGeometry(QRect(10, 20, 241, 461));
        pushButton = new QPushButton(groupBox_4);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(10, 490, 93, 28));
        pushButton_2 = new QPushButton(groupBox_4);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(10, 520, 93, 28));
        pushButton_3 = new QPushButton(groupBox_4);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(110, 490, 93, 28));
        scrollArea = new QScrollArea(tabUIDesigner);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setGeometry(QRect(270, 20, 731, 541));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 729, 539));
        scrollArea->setWidget(scrollAreaWidgetContents);
        twTabs->addTab(tabUIDesigner, QString());

        gLWindow->addWidget(twTabs, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1019, 26));
        menu_File = new QMenu(menuBar);
        menu_File->setObjectName(QStringLiteral("menu_File"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu_File->menuAction());
        menu_File->addAction(action_Exit);
        menu_File->addAction(actionInstall_mod);

        retranslateUi(MainWindow);

        twTabs->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        action_Exit->setText(QApplication::translate("MainWindow", "&Exit", 0));
        actionInstall_mod->setText(QApplication::translate("MainWindow", "Install mod!", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "Mod Location", 0));
        label->setText(QApplication::translate("MainWindow", "Location of mod under construction:", 0));
        label_2->setText(QApplication::translate("MainWindow", "Location where to install mod (game directory):", 0));
        pbModBrowse->setText(QApplication::translate("MainWindow", "Browse", 0));
        pBInstallBrowse->setText(QApplication::translate("MainWindow", "Browse", 0));
        lineEdit->setText(QApplication::translate("MainWindow", "NONAME", 0));
        label_26->setText(QApplication::translate("MainWindow", "Mod Name", 0));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Mod Description", 0));
        label_3->setText(QApplication::translate("MainWindow", "Mod Name:", 0));
        label_4->setText(QApplication::translate("MainWindow", "Mod Description:", 0));
        pbModSave->setText(QApplication::translate("MainWindow", "Save Settings / Create mod", 0));
        twTabs->setTabText(twTabs->indexOf(tabGeneral), QApplication::translate("MainWindow", "Mod Settings", 0));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "Texture", 0));
        pbTextureBrowse->setText(QApplication::translate("MainWindow", "Browse", 0));
        label_5->setText(QApplication::translate("MainWindow", "Size of placeholding rectangle (h * w):", 0));
        label_6->setText(QApplication::translate("MainWindow", "X", 0));
        label_7->setText(QApplication::translate("MainWindow", "# of frames:", 0));
        label_8->setText(QApplication::translate("MainWindow", "# of animations in spritesheet/texture:", 0));
        label_9->setText(QApplication::translate("MainWindow", "Time per frame (cycles for each frame):", 0));
#ifndef QT_NO_TOOLTIP
        label_10->setToolTip(QApplication::translate("MainWindow", "Useful for multianimation textures! It allows you to select the animation from the file!", 0));
#endif // QT_NO_TOOLTIP
        label_10->setText(QApplication::translate("MainWindow", "Selected animation (0-indexed):", 0));
        label_11->setText(QApplication::translate("MainWindow", "Looping animation? (1 = yes):", 0));
        pbRegTexture->setText(QApplication::translate("MainWindow", "Register", 0));
        label_12->setText(QApplication::translate("MainWindow", "Name for this object:", 0));
        groupBox_5->setTitle(QApplication::translate("MainWindow", "Sound", 0));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Music (m)", 0)
         << QApplication::translate("MainWindow", "Effect (e)", 0)
         << QApplication::translate("MainWindow", "Random audio (a)", 0)
        );
        label_13->setText(QApplication::translate("MainWindow", "Sound type: ", 0));
        label_14->setText(QApplication::translate("MainWindow", "Sound Location:", 0));
        label_15->setText(QApplication::translate("MainWindow", "X->", 0));
        label_16->setText(QApplication::translate("MainWindow", "Y->", 0));
        label_17->setText(QApplication::translate("MainWindow", "Sound file: ", 0));
        pbSoundBrowse->setText(QApplication::translate("MainWindow", "Browse", 0));
        pbRegSound->setText(QApplication::translate("MainWindow", "Register", 0));
        groupBox_6->setTitle(QApplication::translate("MainWindow", "Code", 0));
        label_18->setText(QApplication::translate("MainWindow", "Location:", 0));
        pbCodeBrowse->setText(QApplication::translate("MainWindow", "Browse", 0));
        pbRegCode->setText(QApplication::translate("MainWindow", "Register", 0));
        label_19->setText(QApplication::translate("MainWindow", "Type:", 0));
        comboBox_2->clear();
        comboBox_2->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Plugin", 0)
         << QApplication::translate("MainWindow", "Script", 0)
        );
        groupBox_7->setTitle(QApplication::translate("MainWindow", "Texture Preview", 0));
        lbTextInfo->setText(QApplication::translate("MainWindow", "Texture size:", 0));
        groupBox_8->setTitle(QApplication::translate("MainWindow", "Physics Descriptor", 0));
        label_20->setText(QApplication::translate("MainWindow", "Mass:", 0));
        label_21->setText(QApplication::translate("MainWindow", "Descriptor Name:", 0));
        label_22->setText(QApplication::translate("MainWindow", "Charge:", 0));
        label_23->setText(QApplication::translate("MainWindow", "Mu:", 0));
#ifndef QT_NO_TOOLTIP
        checkBox->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600;\">Warning</span>: checking this box will mean that the engine will ignore updating the objects physical position despite computing the forces that act on it!</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        checkBox->setText(QApplication::translate("MainWindow", "Is the object unmovable?", 0));
        checkBox_2->setText(QApplication::translate("MainWindow", "Does the object have a magnetic field?", 0));
        label_24->setText(QApplication::translate("MainWindow", "Magnitude of magnetic field:", 0));
        label_25->setText(QApplication::translate("MainWindow", "Elasticity of collisions:", 0));
        pbRegPhys->setText(QApplication::translate("MainWindow", "Register", 0));
        twTabs->setTabText(twTabs->indexOf(tabRegisterAssets), QApplication::translate("MainWindow", "Register Assets", 0));
        gbBaseAssets->setTitle(QApplication::translate("MainWindow", "Base Assets", 0));
        pbDelAsset->setText(QApplication::translate("MainWindow", "Delete Selected Asset", 0));
        gbRegisteredObjects->setTitle(QApplication::translate("MainWindow", "Game Objects", 0));
        pbNewObj->setText(QApplication::translate("MainWindow", "Create New Object", 0));
        pbDelObj->setText(QApplication::translate("MainWindow", "Delete Selected Object", 0));
        cbObjType->clear();
        cbObjType->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Environment Object", 0)
         << QApplication::translate("MainWindow", "Cursor", 0)
         << QApplication::translate("MainWindow", "Cursorset", 0)
         << QApplication::translate("MainWindow", "Layer", 0)
         << QApplication::translate("MainWindow", "Layerset", 0)
         << QApplication::translate("MainWindow", "Locale", 0)
         << QApplication::translate("MainWindow", "Trigger", 0)
         << QApplication::translate("MainWindow", "Unit", 0)
         << QApplication::translate("MainWindow", "UI", 0)
        );
        twTabs->setTabText(twTabs->indexOf(tabAssets), QApplication::translate("MainWindow", "Assets", 0));
        gbObjects->setTitle(QApplication::translate("MainWindow", "Objects Toolbox", 0));
        pushButton_4->setText(QApplication::translate("MainWindow", "Undo", 0));
        gbGamePreview->setTitle(QApplication::translate("MainWindow", "Game World Preview (real time)", 0));
        twTabs->setTabText(twTabs->indexOf(tabDesigner), QApplication::translate("MainWindow", "Level Designer", 0));
        groupBox_4->setTitle(QApplication::translate("MainWindow", "UI Toolbox", 0));
        pushButton->setText(QApplication::translate("MainWindow", "Undo", 0));
        pushButton_2->setText(QApplication::translate("MainWindow", "Clear", 0));
        pushButton_3->setText(QApplication::translate("MainWindow", "Save UI", 0));
        twTabs->setTabText(twTabs->indexOf(tabUIDesigner), QApplication::translate("MainWindow", "UI Designer", 0));
        menu_File->setTitle(QApplication::translate("MainWindow", "&File", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
