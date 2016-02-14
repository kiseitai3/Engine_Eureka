#ifndef LAYERSETTINGS_H
#define LAYERSETTINGS_H

#include <QDialog>

namespace Ui {
class Layersettings;
}

class Layersettings : public QDialog
{
    Q_OBJECT

public:
    explicit Layersettings(QWidget *parent = 0);
    ~Layersettings();

private:
    Ui::Layersettings *ui;
};

#endif // LAYERSETTINGS_H
