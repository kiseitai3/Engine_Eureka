#include "color_picker.h"
#include "ui_color_picker.h"

Color_picker::Color_picker(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Color_picker)
{
    ui->setupUi(this);
    UpdateColors();
}

Color_picker::~Color_picker()
{
    delete ui;
}

QPalette Color_picker::GetColor() const
{
    return ui->pbColor->palette();
}

void Color_picker::on_hsR_actionTriggered(int action)
{
    UpdateColors();
}

void Color_picker::on_hsG_actionTriggered(int action)
{
    UpdateColors();
}

void Color_picker::on_hsB_actionTriggered(int action)
{
    UpdateColors();
}

void Color_picker::UpdateColors()
{
    QColor c;
    c.fromRgb(ui->hsR->value(), ui->hsG->value(), ui->hsB->value());
    QPalette p = ui->pbColor->palette();
    p.setColor(QPalette::Window, c);
}

void Color_picker::on_pbOK_clicked()
{
    this->close();
}
