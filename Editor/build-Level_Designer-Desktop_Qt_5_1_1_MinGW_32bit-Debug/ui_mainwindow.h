/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
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
        twTabs->addTab(tabRegisterAssets, QString());
        tabDesigner = new QWidget();
        tabDesigner->setObjectName(QStringLiteral("tabDesigner"));
        twTabs->addTab(tabDesigner, QString());

        gLWindow->addWidget(twTabs, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1019, 21));
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

        twTabs->setCurrentIndex(0);


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
