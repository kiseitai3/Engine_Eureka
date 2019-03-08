#ifndef TEXTURESETTINGS_H
#define TEXTURESETTINGS_H

#include <QDialog>

namespace Ui {
class TextureSettings;
}

class TextureSettings : public QDialog
{
    Q_OBJECT

public:
    explicit TextureSettings(QWidget *parent = 0);
    ~TextureSettings();

private:
    Ui::TextureSettings *ui;
};

#endif // TEXTURESETTINGS_H
