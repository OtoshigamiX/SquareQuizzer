#ifndef CONFIGURATIONWINDOW_H
#define CONFIGURATIONWINDOW_H

#include <QDialog>

namespace Ui {
class ConfigurationWindow;
}

class ConfigurationWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigurationWindow(QWidget *parent = nullptr);
    ~ConfigurationWindow();

private slots:
    void on_checkBox_stateChanged(int);

    void on_subPrevButton_clicked();

    void on_subNextButton_clicked();

    void on_revealLineEdit_returnPressed();
    void on_subRevealButton_clicked();

private:
    Ui::ConfigurationWindow *ui;
    QWidget *parent;
};

#endif // CONFIGURATIONWINDOW_H
