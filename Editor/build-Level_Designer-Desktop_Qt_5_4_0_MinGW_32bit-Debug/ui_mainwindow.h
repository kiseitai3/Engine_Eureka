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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_Exit;
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
    QWidget *tabDesigner;
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
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayoutWidget = new QWidget(centralWidget);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(0, 0, 1021, 601));
        gLWindow = new QGridLayout(gridLayoutWidget);
        gLWindow->setSpacing(6);
        gLWindow->setContentsMargins(11, 11, 11, 11);
        gLWindow->setObjectName(QStringLiteral("gLWindow"));
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
        label->setGeometry(QRect(10, 20, 191, 16));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 90, 241, 16));
        pbModBrowse = new QPushButton(groupBox);
        pbModBrowse->setObjectName(QStringLiteral("pbModBrowse"));
        pbModBrowse->setGeometry(QRect(400, 40, 75, 23));
        pBInstallBrowse = new QPushButton(groupBox);
        pBInstallBrowse->setObjectName(QStringLiteral("pBInstallBrowse"));
        pBInstallBrowse->setGeometry(QRect(400, 110, 75, 23));
        groupBox_2 = new QGroupBox(tabGeneral);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 240, 501, 251));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 30, 321, 16));
        leModName = new QLineEdit(groupBox_2);
        leModName->setObjectName(QStringLiteral("leModName"));
        leModName->setGeometry(QRect(10, 50, 291, 20));
        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 80, 321, 16));
        teModDescription = new QTextEdit(groupBox_2);
        teModDescription->setObjectName(QStringLiteral("teModDescription"));
        teModDescription->setGeometry(QRect(10, 100, 471, 131));
        pbModSave = new QPushButton(tabGeneral);
        pbModSave->setObjectName(QStringLiteral("pbModSave"));
        pbModSave->setGeometry(QRect(10, 500, 75, 23));
        twTabs->addTab(tabGeneral, QString());
        tabRegisterAssets = new QWidget();
        tabRegisterAssets->setObjectName(QStringLiteral("tabRegisterAssets"));
        groupBox_3 = new QGroupBox(tabRegisterAssets);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(0, 0, 411, 241));
        pbTextureBrowse = new QPushButton(groupBox_3);
        pbTextureBrowse->setObjectName(QStringLiteral("pbTextureBrowse"));
        pbTextureBrowse->setGeometry(QRect(320, 20, 75, 23));
        leTexturePath = new QLineEdit(groupBox_3);
        leTexturePath->setObjectName(QStringLiteral("leTexturePath"));
        leTexturePath->setGeometry(QRect(10, 20, 291, 20));
        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(20, 50, 201, 16));
        sbHeight = new QSpinBox(groupBox_3);
        sbHeight->setObjectName(QStringLiteral("sbHeight"));
        sbHeight->setGeometry(QRect(240, 50, 42, 22));
        label_6 = new QLabel(groupBox_3);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(290, 50, 16, 16));
        sbWidth = new QSpinBox(groupBox_3);
        sbWidth->setObjectName(QStringLiteral("sbWidth"));
        sbWidth->setGeometry(QRect(310, 50, 42, 22));
        label_7 = new QLabel(groupBox_3);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(20, 90, 61, 16));
        sbFrames = new QSpinBox(groupBox_3);
        sbFrames->setObjectName(QStringLiteral("sbFrames"));
        sbFrames->setGeometry(QRect(90, 90, 42, 22));
        label_8 = new QLabel(groupBox_3);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(150, 90, 191, 16));
        sbAnimCounter = new QSpinBox(groupBox_3);
        sbAnimCounter->setObjectName(QStringLiteral("sbAnimCounter"));
        sbAnimCounter->setGeometry(QRect(350, 90, 42, 22));
        label_9 = new QLabel(groupBox_3);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(20, 120, 191, 16));
        sbTimePerFrame = new QSpinBox(groupBox_3);
        sbTimePerFrame->setObjectName(QStringLiteral("sbTimePerFrame"));
        sbTimePerFrame->setGeometry(QRect(220, 120, 42, 22));
        label_10 = new QLabel(groupBox_3);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(20, 150, 161, 16));
        sbAnimNum = new QSpinBox(groupBox_3);
        sbAnimNum->setObjectName(QStringLiteral("sbAnimNum"));
        sbAnimNum->setGeometry(QRect(190, 150, 42, 22));
        label_11 = new QLabel(groupBox_3);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(20, 180, 151, 16));
        sbLoop = new QSpinBox(groupBox_3);
        sbLoop->setObjectName(QStringLiteral("sbLoop"));
        sbLoop->setGeometry(QRect(170, 180, 42, 22));
        sbLoop->setMaximum(1);
        pbRegTexture = new QPushButton(groupBox_3);
        pbRegTexture->setObjectName(QStringLiteral("pbRegTexture"));
        pbRegTexture->setGeometry(QRect(320, 210, 75, 23));
        label_12 = new QLabel(groupBox_3);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(20, 210, 101, 16));
        leTexName = new QLineEdit(groupBox_3);
        leTexName->setObjectName(QStringLiteral("leTexName"));
        leTexName->setGeometry(QRect(130, 210, 113, 20));
        gridLayoutWidget_2 = new QWidget(tabRegisterAssets);
        gridLayoutWidget_2->setObjectName(QStringLiteral("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(-1, -1, 1011, 581));
        gridLayout = new QGridLayout(gridLayoutWidget_2);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        twTabs->addTab(tabRegisterAssets, QString());
        tabDesigner = new QWidget();
        tabDesigner->setObjectName(QStringLiteral("tabDesigner"));
        twTabs->addTab(tabDesigner, QString());

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

        retranslateUi(MainWindow);

        twTabs->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        action_Exit->setText(QApplication::translate("MainWindow", "&Exit", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "Mod Location", 0));
        label->setText(QApplication::translate("MainWindow", "Location of mod under construction:", 0));
        label_2->setText(QApplication::translate("MainWindow", "Location where to install mod (game directory):", 0));
        pbModBrowse->setText(QApplication::translate("MainWindow", "Browse", 0));
        pBInstallBrowse->setText(QApplication::translate("MainWindow", "Browse", 0));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Mod Description", 0));
        label_3->setText(QApplication::translate("MainWindow", "Mod Name:", 0));
        label_4->setText(QApplication::translate("MainWindow", "Mod Description:", 0));
        pbModSave->setText(QApplication::translate("MainWindow", "Save Settings", 0));
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
        twTabs->setTabText(twTabs->indexOf(tabRegisterAssets), QApplication::translate("MainWindow", "Register Assets", 0));
        twTabs->setTabText(twTabs->indexOf(tabDesigner), QApplication::translate("MainWindow", "Level Designer", 0));
        menu_File->setTitle(QApplication::translate("MainWindow", "&File", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
