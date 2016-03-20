#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_lineEdit_returnPressed();

private:
    Ui::MainWindow *ui;
    bool squares[4][3];
    void redraw();
    QPixmap cur_image;
};

#endif // MAINWINDOW_H
