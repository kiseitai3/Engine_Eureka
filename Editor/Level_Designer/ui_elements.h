#ifndef UI_ELEMENTS_H
#define UI_ELEMENTS_H

#include <QDialog>

namespace Ui {
class UI_Elements;
}

class UI_Elements : public QDialog
{
    Q_OBJECT

public:
    explicit UI_Elements(QWidget *parent = 0);
    ~UI_Elements();

private:
    Ui::UI_Elements *ui;
};

#endif // UI_ELEMENTS_H
