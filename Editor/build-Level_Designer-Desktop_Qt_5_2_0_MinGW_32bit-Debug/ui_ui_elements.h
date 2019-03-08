/********************************************************************************
** Form generated from reading UI file 'ui_elements.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UI_ELEMENTS_H
#define UI_UI_ELEMENTS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_UI_Elements
{
public:
    QGroupBox *groupBox;
    QGroupBox *groupBox_2;
    QLabel *label_3;
    QPushButton *pbTextureBrowse;
    QLabel *label_2;
    QPushButton *pbFontBrowse;
    QLineEdit *leFont;
    QLineEdit *leTexture;
    QLabel *label;
    QSpinBox *sbFontSize;
    QLabel *label_4;
    QSpinBox *sbX;
    QSpinBox *sbY;
    QLabel *label_5;
    QSpinBox *sbTextX;
    QSpinBox *sbTextY;
    QLabel *label_6;
    QSpinBox *sbTextW;
    QSpinBox *sbTextH;
    QPushButton *pbFontColorPicker;
    QLabel *label_13;
    QGroupBox *groupBox_3;
    QLabel *label_7;
    QLineEdit *leTextureEnter;
    QPushButton *pbTextureEnterBrowse;
    QLabel *label_8;
    QLineEdit *leTextureClick;
    QPushButton *pbTextureClickBrowse;
    QLabel *label_9;
    QLineEdit *leTextureIdle;
    QPushButton *pbTextureIdleBrowse;
    QLabel *label_10;
    QLineEdit *leTextureSelect;
    QPushButton *pbTextureSelectBrowse;
    QLabel *label_11;
    QLineEdit *leTextureDown;
    QPushButton *pbTextureDownBrowse;
    QGroupBox *groupBox_4;
    QCheckBox *cbWrite;
    QCheckBox *cbType;
    QLabel *label_14;
    QLineEdit *leName;
    QPushButton *pbSave;

    void setupUi(QDialog *UI_Elements)
    {
        if (UI_Elements->objectName().isEmpty())
            UI_Elements->setObjectName(QStringLiteral("UI_Elements"));
        UI_Elements->resize(695, 538);
        groupBox = new QGroupBox(UI_Elements);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(0, 0, 691, 531));
        groupBox_2 = new QGroupBox(groupBox);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(0, 20, 691, 201));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 100, 55, 16));
        pbTextureBrowse = new QPushButton(groupBox_2);
        pbTextureBrowse->setObjectName(QStringLiteral("pbTextureBrowse"));
        pbTextureBrowse->setGeometry(QRect(540, 20, 93, 28));
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 60, 81, 16));
        pbFontBrowse = new QPushButton(groupBox_2);
        pbFontBrowse->setObjectName(QStringLiteral("pbFontBrowse"));
        pbFontBrowse->setGeometry(QRect(540, 60, 93, 28));
        leFont = new QLineEdit(groupBox_2);
        leFont->setObjectName(QStringLiteral("leFont"));
        leFont->setGeometry(QRect(100, 60, 411, 22));
        leTexture = new QLineEdit(groupBox_2);
        leTexture->setObjectName(QStringLiteral("leTexture"));
        leTexture->setGeometry(QRect(90, 20, 421, 22));
        label = new QLabel(groupBox_2);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 20, 81, 16));
        sbFontSize = new QSpinBox(groupBox_2);
        sbFontSize->setObjectName(QStringLiteral("sbFontSize"));
        sbFontSize->setGeometry(QRect(70, 100, 61, 22));
        sbFontSize->setMinimum(1);
        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(150, 100, 91, 16));
        sbX = new QSpinBox(groupBox_2);
        sbX->setObjectName(QStringLiteral("sbX"));
        sbX->setGeometry(QRect(250, 100, 51, 22));
        sbX->setMaximum(999999);
        sbY = new QSpinBox(groupBox_2);
        sbY->setObjectName(QStringLiteral("sbY"));
        sbY->setGeometry(QRect(310, 100, 51, 22));
        sbY->setMaximum(999999);
        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(0, 130, 191, 16));
        sbTextX = new QSpinBox(groupBox_2);
        sbTextX->setObjectName(QStringLiteral("sbTextX"));
        sbTextX->setGeometry(QRect(190, 130, 51, 22));
        sbTextX->setMaximum(999999);
        sbTextY = new QSpinBox(groupBox_2);
        sbTextY->setObjectName(QStringLiteral("sbTextY"));
        sbTextY->setGeometry(QRect(250, 130, 51, 22));
        sbTextY->setMaximum(999999);
        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(10, 160, 181, 16));
        sbTextW = new QSpinBox(groupBox_2);
        sbTextW->setObjectName(QStringLiteral("sbTextW"));
        sbTextW->setGeometry(QRect(250, 160, 51, 22));
        sbTextW->setMaximum(999999);
        sbTextH = new QSpinBox(groupBox_2);
        sbTextH->setObjectName(QStringLiteral("sbTextH"));
        sbTextH->setGeometry(QRect(190, 160, 51, 22));
        sbTextH->setMaximum(999999);
        pbFontColorPicker = new QPushButton(groupBox_2);
        pbFontColorPicker->setObjectName(QStringLiteral("pbFontColorPicker"));
        pbFontColorPicker->setGeometry(QRect(540, 100, 93, 71));
        label_13 = new QLabel(groupBox_2);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(460, 110, 71, 16));
        groupBox_3 = new QGroupBox(groupBox);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(0, 230, 691, 191));
        label_7 = new QLabel(groupBox_3);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(10, 20, 101, 16));
        leTextureEnter = new QLineEdit(groupBox_3);
        leTextureEnter->setObjectName(QStringLiteral("leTextureEnter"));
        leTextureEnter->setGeometry(QRect(110, 20, 401, 22));
        pbTextureEnterBrowse = new QPushButton(groupBox_3);
        pbTextureEnterBrowse->setObjectName(QStringLiteral("pbTextureEnterBrowse"));
        pbTextureEnterBrowse->setGeometry(QRect(540, 20, 93, 28));
        label_8 = new QLabel(groupBox_3);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(10, 50, 111, 16));
        leTextureClick = new QLineEdit(groupBox_3);
        leTextureClick->setObjectName(QStringLiteral("leTextureClick"));
        leTextureClick->setGeometry(QRect(120, 50, 391, 22));
        pbTextureClickBrowse = new QPushButton(groupBox_3);
        pbTextureClickBrowse->setObjectName(QStringLiteral("pbTextureClickBrowse"));
        pbTextureClickBrowse->setGeometry(QRect(540, 50, 93, 28));
        label_9 = new QLabel(groupBox_3);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(10, 80, 101, 16));
        leTextureIdle = new QLineEdit(groupBox_3);
        leTextureIdle->setObjectName(QStringLiteral("leTextureIdle"));
        leTextureIdle->setGeometry(QRect(110, 80, 401, 22));
        pbTextureIdleBrowse = new QPushButton(groupBox_3);
        pbTextureIdleBrowse->setObjectName(QStringLiteral("pbTextureIdleBrowse"));
        pbTextureIdleBrowse->setGeometry(QRect(540, 80, 93, 28));
        label_10 = new QLabel(groupBox_3);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(10, 110, 121, 16));
        leTextureSelect = new QLineEdit(groupBox_3);
        leTextureSelect->setObjectName(QStringLiteral("leTextureSelect"));
        leTextureSelect->setGeometry(QRect(130, 110, 381, 22));
        pbTextureSelectBrowse = new QPushButton(groupBox_3);
        pbTextureSelectBrowse->setObjectName(QStringLiteral("pbTextureSelectBrowse"));
        pbTextureSelectBrowse->setGeometry(QRect(540, 110, 93, 28));
        label_11 = new QLabel(groupBox_3);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(10, 140, 101, 16));
        leTextureDown = new QLineEdit(groupBox_3);
        leTextureDown->setObjectName(QStringLiteral("leTextureDown"));
        leTextureDown->setGeometry(QRect(120, 140, 391, 22));
        pbTextureDownBrowse = new QPushButton(groupBox_3);
        pbTextureDownBrowse->setObjectName(QStringLiteral("pbTextureDownBrowse"));
        pbTextureDownBrowse->setGeometry(QRect(540, 140, 93, 28));
        groupBox_4 = new QGroupBox(groupBox);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(0, 430, 531, 91));
        cbWrite = new QCheckBox(groupBox_4);
        cbWrite->setObjectName(QStringLiteral("cbWrite"));
        cbWrite->setGeometry(QRect(10, 30, 101, 20));
        cbType = new QCheckBox(groupBox_4);
        cbType->setObjectName(QStringLiteral("cbType"));
        cbType->setGeometry(QRect(10, 60, 91, 20));
        label_14 = new QLabel(groupBox_4);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(140, 20, 55, 16));
        leName = new QLineEdit(groupBox_4);
        leName->setObjectName(QStringLiteral("leName"));
        leName->setGeometry(QRect(200, 20, 191, 22));
        pbSave = new QPushButton(groupBox);
        pbSave->setObjectName(QStringLiteral("pbSave"));
        pbSave->setGeometry(QRect(540, 470, 131, 41));

        retranslateUi(UI_Elements);

        QMetaObject::connectSlotsByName(UI_Elements);
    } // setupUi

    void retranslateUi(QDialog *UI_Elements)
    {
        UI_Elements->setWindowTitle(QApplication::translate("UI_Elements", "Dialog", 0));
        groupBox->setTitle(QApplication::translate("UI_Elements", "Element settings", 0));
        groupBox_2->setTitle(QApplication::translate("UI_Elements", "Textbox side", 0));
        label_3->setText(QApplication::translate("UI_Elements", "Font size", 0));
        pbTextureBrowse->setText(QApplication::translate("UI_Elements", "Browse", 0));
        label_2->setText(QApplication::translate("UI_Elements", "Font location:", 0));
        pbFontBrowse->setText(QApplication::translate("UI_Elements", "Browse", 0));
        label->setText(QApplication::translate("UI_Elements", "Texture file:", 0));
        label_4->setText(QApplication::translate("UI_Elements", "Location (x, y):", 0));
        label_5->setText(QApplication::translate("UI_Elements", "Text placeholder location (x, y):", 0));
        label_6->setText(QApplication::translate("UI_Elements", "Text placeholder size (h x w):", 0));
        pbFontColorPicker->setText(QString());
        label_13->setText(QApplication::translate("UI_Elements", "Font color:", 0));
        groupBox_3->setTitle(QApplication::translate("UI_Elements", "Button side", 0));
        label_7->setText(QApplication::translate("UI_Elements", "Texture (Enter):", 0));
        pbTextureEnterBrowse->setText(QApplication::translate("UI_Elements", "Browse", 0));
        label_8->setText(QApplication::translate("UI_Elements", "Texture (Clicking):", 0));
        pbTextureClickBrowse->setText(QApplication::translate("UI_Elements", "Browse", 0));
        label_9->setText(QApplication::translate("UI_Elements", "Texture (Idle):", 0));
        pbTextureIdleBrowse->setText(QApplication::translate("UI_Elements", "Browse", 0));
        label_10->setText(QApplication::translate("UI_Elements", "Texture (Selected):", 0));
        pbTextureSelectBrowse->setText(QApplication::translate("UI_Elements", "Browse", 0));
        label_11->setText(QApplication::translate("UI_Elements", "Texture (Down):", 0));
        pbTextureDownBrowse->setText(QApplication::translate("UI_Elements", "Browse", 0));
        groupBox_4->setTitle(QApplication::translate("UI_Elements", "General", 0));
        cbWrite->setText(QApplication::translate("UI_Elements", "Is writable!", 0));
        cbType->setText(QApplication::translate("UI_Elements", "Is a button!", 0));
        label_14->setText(QApplication::translate("UI_Elements", "Name:", 0));
        pbSave->setText(QApplication::translate("UI_Elements", "Build UI Element", 0));
    } // retranslateUi

};

namespace Ui {
    class UI_Elements: public Ui_UI_Elements {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UI_ELEMENTS_H
