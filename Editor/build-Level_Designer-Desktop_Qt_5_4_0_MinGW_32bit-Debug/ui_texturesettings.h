/********************************************************************************
** Form generated from reading UI file 'texturesettings.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEXTURESETTINGS_H
#define UI_TEXTURESETTINGS_H

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

class Ui_TextureSettings
{
public:
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

    void setupUi(QDialog *TextureSettings)
    {
        if (TextureSettings->objectName().isEmpty())
            TextureSettings->setObjectName(QStringLiteral("TextureSettings"));
        TextureSettings->resize(437, 260);
        groupBox_3 = new QGroupBox(TextureSettings);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(0, 10, 431, 241));
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
        label_6 = new QLabel(groupBox_3);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(300, 50, 16, 16));
        sbWidth = new QSpinBox(groupBox_3);
        sbWidth->setObjectName(QStringLiteral("sbWidth"));
        sbWidth->setGeometry(QRect(320, 50, 42, 22));
        label_7 = new QLabel(groupBox_3);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(20, 90, 61, 16));
        sbFrames = new QSpinBox(groupBox_3);
        sbFrames->setObjectName(QStringLiteral("sbFrames"));
        sbFrames->setGeometry(QRect(90, 90, 42, 22));
        label_8 = new QLabel(groupBox_3);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(150, 90, 231, 16));
        sbAnimCounter = new QSpinBox(groupBox_3);
        sbAnimCounter->setObjectName(QStringLiteral("sbAnimCounter"));
        sbAnimCounter->setGeometry(QRect(380, 90, 42, 22));
        label_9 = new QLabel(groupBox_3);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(20, 120, 241, 16));
        sbTimePerFrame = new QSpinBox(groupBox_3);
        sbTimePerFrame->setObjectName(QStringLiteral("sbTimePerFrame"));
        sbTimePerFrame->setGeometry(QRect(260, 120, 42, 22));
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

        retranslateUi(TextureSettings);

        QMetaObject::connectSlotsByName(TextureSettings);
    } // setupUi

    void retranslateUi(QDialog *TextureSettings)
    {
        TextureSettings->setWindowTitle(QApplication::translate("TextureSettings", "Dialog", 0));
        groupBox_3->setTitle(QApplication::translate("TextureSettings", "Texture", 0));
        pbTextureBrowse->setText(QApplication::translate("TextureSettings", "Browse", 0));
        label_5->setText(QApplication::translate("TextureSettings", "Size of placeholding rectangle (h * w):", 0));
        label_6->setText(QApplication::translate("TextureSettings", "X", 0));
        label_7->setText(QApplication::translate("TextureSettings", "# of frames:", 0));
        label_8->setText(QApplication::translate("TextureSettings", "# of animations in spritesheet/texture:", 0));
        label_9->setText(QApplication::translate("TextureSettings", "Time per frame (cycles for each frame):", 0));
#ifndef QT_NO_TOOLTIP
        label_10->setToolTip(QApplication::translate("TextureSettings", "Useful for multianimation textures! It allows you to select the animation from the file!", 0));
#endif // QT_NO_TOOLTIP
        label_10->setText(QApplication::translate("TextureSettings", "Selected animation (0-indexed):", 0));
        label_11->setText(QApplication::translate("TextureSettings", "Looping animation? (1 = yes):", 0));
        pbRegTexture->setText(QApplication::translate("TextureSettings", "Save", 0));
        label_12->setText(QApplication::translate("TextureSettings", "Name for this object:", 0));
    } // retranslateUi

};

namespace Ui {
    class TextureSettings: public Ui_TextureSettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEXTURESETTINGS_H
