#ifndef STARTUP_H
#define STARTUP_H

#include <QDialog>

namespace Ui {
  class Startup;
}

class Startup : public QDialog
{
  Q_OBJECT

public:
  explicit Startup(QWidget *parent = 0);
  ~Startup();

private slots:
  void on_pbOpenBrowse_clicked();

  void on_pbNameBrowse_clicked();

  void on_buttonBox_accepted();

  void on_leName_textChanged(const QString &arg1);

  void on_buttonBox_rejected();

private:
  Ui::Startup *ui;
};

#endif // STARTUP_H
