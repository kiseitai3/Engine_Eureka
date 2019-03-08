#ifndef COLOR_PICKER_H
#define COLOR_PICKER_H

#include <QWidget>
#include <QPalette>
#include <QColor>

namespace Ui {
class Color_picker;
}

class Color_picker : public QWidget
{
    Q_OBJECT

public:
    explicit Color_picker(QWidget *parent = 0);
    ~Color_picker();

    QPalette GetColor() const;
private slots:
    void on_hsR_actionTriggered(int action);

    void on_hsG_actionTriggered(int action);

    void on_hsB_actionTriggered(int action);

    void on_pbOK_clicked();

private:
    Ui::Color_picker *ui;


    void UpdateColors();
};

#endif // COLOR_PICKER_H
