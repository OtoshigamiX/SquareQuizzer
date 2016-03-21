#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#define SQUARE_X 4
#define SQUARE_Y 4

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void squareReset();
      bool squares[SQUARE_X][SQUARE_Y];
     void squareTurnOff(int number);
//    static MainWindow* getMainWindow();
    void redraw();
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;
    void on_lineEdit_returnPressed();


private:
    Ui::MainWindow *ui;


    QPixmap cur_image;

};

#endif // MAINWINDOW_H
