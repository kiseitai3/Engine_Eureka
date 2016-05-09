#ifndef LOCALE_SETTINGS_H
#define LOCALE_SETTINGS_H

#include <QDialog>

namespace Ui {
class Locale_settings;
}

class Locale_settings : public QDialog
{
    Q_OBJECT

public:
    explicit Locale_settings(QWidget *parent = 0);
    ~Locale_settings();

private:
    Ui::Locale_settings *ui;
};

#endif // LOCALE_SETTINGS_H
