#ifndef PHYSICSSETTINGS_H
#define PHYSICSSETTINGS_H

#include <QDialog>

namespace Ui {
class PhysicsSettings;
}

class PhysicsSettings : public QDialog
{
    Q_OBJECT

public:
    explicit PhysicsSettings(QWidget *parent = 0);
    ~PhysicsSettings();

private:
    Ui::PhysicsSettings *ui;
};

#endif // PHYSICSSETTINGS_H
