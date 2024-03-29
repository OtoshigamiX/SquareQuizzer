#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <QPushButton>
#include <QTimer>
#include <QTime>
#include <memory>
#include "configurationwindow.h"
#define SQUARE_X 4
#define SQUARE_Y 4
#define HALF_OF_SQUARES SQUARE_X*SQUARE_Y/2

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void squareTurnOff(int number);
    void changeScoring(int arg1);
    void nextImage();
    void previousImage();
    void revealAllTiles();
    void timerUpdate();
    void startTimer(unsigned secs);
    void resetTimer();

    ~MainWindow();
    unsigned auto_timer_value = 30u;
private slots:

    void on_pushButton_clicked();
    void resizeEvent(QResizeEvent *) Q_DECL_OVERRIDE;
    void on_lineEdit_returnPressed();

    void on_nextButton_clicked();

    void on_previousButton_clicked();

    void on_RevealButton_clicked();

    void on_configButton_clicked();

private:
    bool isMiddle(int i, int j);
    int countUsedSquares();
    int countUsedMiddleSquares();
    bool isBlocked(int i, int j);
    void squareReset(bool type);
    void redraw();
    void resetLabels();
    void updateLabels();
    void calculatePoints();
    void calculateHalfPoints();

    bool squares[SQUARE_X][SQUARE_Y];
    Ui::MainWindow *ui;

    QStringList filenames;
    QStringList::const_iterator constIterator;
    QPixmap cur_image;
    QColor cur_color = Qt::black;
    QString cur_question = "1";
    bool isAltScoringEnabled{false};
    QTimer* timer;
    QTime time;
    const QTime zerotime = QTime(0,0);
    int points = 8;

    ConfigurationWindow cw{this};
};

#endif // MAINWINDOW_H
