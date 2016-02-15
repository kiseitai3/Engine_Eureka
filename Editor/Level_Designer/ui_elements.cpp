#include "ui_elements.h"
#include "ui_ui_elements.h"

UI_Elements::UI_Elements(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UI_Elements)
{
    ui->setupUi(this);
}

UI_Elements::~UI_Elements()
{
    delete ui;
}
