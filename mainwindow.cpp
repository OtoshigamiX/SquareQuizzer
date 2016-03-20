#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    for(int i=0;i<4;i++){
        for(int j=0;j<3;j++){
            squares[i][j]=true;
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

    QString fileName = QFileDialog::getOpenFileName(this,tr("Open Image"), "", tr("Image Files (*.png *.jpg *.bmp)"));
    cur_image= QPixmap(fileName);
    for(int i=0;i<4;i++){
        for(int j=0;j<3;j++){
            squares[i][j]=true;
        }
    }
    redraw();
}

void MainWindow::redraw()
{
    QGraphicsScene *scene= new QGraphicsScene;
    scene->addPixmap(cur_image);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->fitInView(ui->graphicsView->scene()->sceneRect(),Qt::KeepAspectRatio);
    qreal square_width=ui->graphicsView->scene()->width()/4;
    qreal square_height=ui->graphicsView->scene()->height()/3;
    for(int i=0;i<4;i++){
        for(int j=0;j<3;j++){
            if(squares[i][j]){
                ui->graphicsView->scene()->addRect(i*square_width,j*square_height,square_width,square_height,QPen(Qt::black),QBrush(Qt::black));
                int number = (i+1)+j*4;
                QGraphicsTextItem * io = new QGraphicsTextItem;
                io->setPos((i*square_width+square_width/2)-50,(j*square_height+square_height/2)-50);
                io->setPlainText(QString::number(number));
                io->setScale(5.0);
                io->setDefaultTextColor(Qt::white);
                ui->graphicsView->scene()->addItem(io);
            }
        }
    }
    ui->graphicsView->show();
}



void MainWindow::on_lineEdit_returnPressed()
{
    int number = ui->lineEdit->text().toInt();
    int number_x=(number-1)%4;
    int number_y=(number-1)/4;
    if(number>0 && number<=12){
        squares[number_x][number_y]=false;
        redraw();
         ui->lineEdit->clear();
    }
}
