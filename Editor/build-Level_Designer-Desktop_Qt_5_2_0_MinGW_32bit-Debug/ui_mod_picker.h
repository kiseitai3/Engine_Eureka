/********************************************************************************
** Form generated from reading UI file 'mod_picker.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MOD_PICKER_H
#define UI_MOD_PICKER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_mod_picker
{
public:
    QDialogButtonBox *buttonBox;
    QGroupBox *groupBox;
    QListWidget *lstMods;
    QLineEdit *leModName;
    QPushButton *pbAddMod;

    void setupUi(QDialog *mod_picker)
    {
        if (mod_picker->objectName().isEmpty())
            mod_picker->setObjectName(QStringLiteral("mod_picker"));
        mod_picker->resize(388, 287);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(mod_picker->sizePolicy().hasHeightForWidth());
        mod_picker->setSizePolicy(sizePolicy);
        buttonBox = new QDialogButtonBox(mod_picker);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Ok);
        groupBox = new QGroupBox(mod_picker);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 371, 221));
        QFont font;
        font.setPointSize(14);
        groupBox->setFont(font);
        lstMods = new QListWidget(groupBox);
        lstMods->setObjectName(QStringLiteral("lstMods"));
        lstMods->setGeometry(QRect(10, 30, 351, 141));
        leModName = new QLineEdit(groupBox);
        leModName->setObjectName(QStringLiteral("leModName"));
        leModName->setGeometry(QRect(10, 180, 231, 22));
        pbAddMod = new QPushButton(groupBox);
        pbAddMod->setObjectName(QStringLiteral("pbAddMod"));
        pbAddMod->setGeometry(QRect(260, 180, 93, 28));
        QFont font1;
        font1.setPointSize(8);
        pbAddMod->setFont(font1);

        retranslateUi(mod_picker);
        QObject::connect(buttonBox, SIGNAL(accepted()), mod_picker, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), mod_picker, SLOT(reject()));

        QMetaObject::connectSlotsByName(mod_picker);
    } // setupUi

    void retranslateUi(QDialog *mod_picker)
    {
        mod_picker->setWindowTitle(QApplication::translate("mod_picker", "Mod Picker", 0));
        groupBox->setTitle(QApplication::translate("mod_picker", "Which mod do you wish to edit?", 0));
        pbAddMod->setText(QApplication::translate("mod_picker", "Add New!", 0));
    } // retranslateUi

};

namespace Ui {
    class mod_picker: public Ui_mod_picker {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MOD_PICKER_H
