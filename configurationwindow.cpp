#include "configurationwindow.h"
#include "ui_configurationwindow.h"
#include "mainwindow.h"

ConfigurationWindow::ConfigurationWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigurationWindow)
{
    ui->setupUi(this);
    this->parent = parent;
}

ConfigurationWindow::~ConfigurationWindow()
{
    delete ui;
}

void ConfigurationWindow::on_checkBox_stateChanged(int arg1)
{
    ((MainWindow*)parent)->changeScoring(arg1);
}

void ConfigurationWindow::on_subPrevButton_clicked()
{
    ((MainWindow*)parent)->previousImage();
}

void ConfigurationWindow::on_subNextButton_clicked()
{
    ((MainWindow*)parent)->nextImage();
}

void ConfigurationWindow::on_revealLineEdit_returnPressed()
{
    int number = ui->revealLineEdit->text().toInt();
    ((MainWindow*)parent)->squareTurnOff(number);
     ui->revealLineEdit->clear();
}

void ConfigurationWindow::on_subRevealButton_clicked()
{
    ((MainWindow*)parent)->revealAllTiles();
}


void ConfigurationWindow::on_timerLineEdit_returnPressed()
{
    int seconds = ui->timerLineEdit->text().toInt();
    ((MainWindow*)parent)->startTimer(seconds);
     ui->timerLineEdit->clear();
}

