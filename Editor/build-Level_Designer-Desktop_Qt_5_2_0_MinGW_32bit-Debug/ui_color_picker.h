/********************************************************************************
** Form generated from reading UI file 'color_picker.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COLOR_PICKER_H
#define UI_COLOR_PICKER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Color_picker
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QSlider *hsR;
    QSlider *hsG;
    QSlider *hsB;
    QWidget *pbColor;
    QPushButton *pbOK;

    void setupUi(QWidget *Color_picker)
    {
        if (Color_picker->objectName().isEmpty())
            Color_picker->setObjectName(QStringLiteral("Color_picker"));
        Color_picker->resize(546, 98);
        label = new QLabel(Color_picker);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 10, 55, 16));
        label_2 = new QLabel(Color_picker);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 40, 55, 16));
        label_3 = new QLabel(Color_picker);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 70, 55, 16));
        hsR = new QSlider(Color_picker);
        hsR->setObjectName(QStringLiteral("hsR"));
        hsR->setGeometry(QRect(80, 10, 251, 22));
        hsR->setMaximum(255);
        hsR->setSliderPosition(128);
        hsR->setOrientation(Qt::Horizontal);
        hsG = new QSlider(Color_picker);
        hsG->setObjectName(QStringLiteral("hsG"));
        hsG->setGeometry(QRect(80, 40, 251, 22));
        hsG->setMaximum(255);
        hsG->setSliderPosition(128);
        hsG->setOrientation(Qt::Horizontal);
        hsB = new QSlider(Color_picker);
        hsB->setObjectName(QStringLiteral("hsB"));
        hsB->setGeometry(QRect(80, 70, 251, 22));
        hsB->setMaximum(255);
        hsB->setSliderPosition(128);
        hsB->setOrientation(Qt::Horizontal);
        pbColor = new QWidget(Color_picker);
        pbColor->setObjectName(QStringLiteral("pbColor"));
        pbColor->setGeometry(QRect(340, 10, 120, 80));
        pbOK = new QPushButton(Color_picker);
        pbOK->setObjectName(QStringLiteral("pbOK"));
        pbOK->setGeometry(QRect(470, 30, 61, 41));

        retranslateUi(Color_picker);

        QMetaObject::connectSlotsByName(Color_picker);
    } // setupUi

    void retranslateUi(QWidget *Color_picker)
    {
        Color_picker->setWindowTitle(QApplication::translate("Color_picker", "Form", 0));
        label->setText(QApplication::translate("Color_picker", "Red", 0));
        label_2->setText(QApplication::translate("Color_picker", "Green", 0));
        label_3->setText(QApplication::translate("Color_picker", "Blue", 0));
        pbOK->setText(QApplication::translate("Color_picker", "Ok", 0));
    } // retranslateUi

};

namespace Ui {
    class Color_picker: public Ui_Color_picker {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COLOR_PICKER_H
