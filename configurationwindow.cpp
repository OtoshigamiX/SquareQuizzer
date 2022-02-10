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

