#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qgraphicsclickablerectitem.h"
#include <QtWidgets>
#include <QPointer>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Sets up the squares (every square is on by default)
    squareReset();
}

MainWindow::~MainWindow()
{
    delete ui;
}


//When we click the Load button, we load the current image to the cur_image variable, reset squares
//and redraw the whole playground.
void MainWindow::on_pushButton_clicked()
{

    filenames = QFileDialog::getOpenFileNames(this,tr("Select Images"),"",tr("Image Files (*.png *.jpg *.bmp)"));
    constIterator=filenames.constBegin();
    //QString fileName = QFileDialog::getOpenFileName(this,tr("Open Image"), "", tr("Image Files (*.png *.jpg *.bmp)"));
    cur_image= QPixmap(*constIterator);
    ui->label->setText(*constIterator);
    squareReset();
    redraw();
}


//This function redraws the whole playground.
void MainWindow::redraw()
{
    QPointer<QGraphicsScene> scene= new QGraphicsScene;
    scene->addPixmap(cur_image);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->fitInView(ui->graphicsView->scene()->sceneRect(),Qt::KeepAspectRatio);

    qreal square_width=ui->graphicsView->scene()->width()/SQUARE_X;
    qreal square_height=ui->graphicsView->scene()->height()/SQUARE_Y;

    for(int i=0;i<SQUARE_X;i++){
        for(int j=0;j<SQUARE_Y;j++){
            if(squares[i][j]){
                int number = (i+1)+j*SQUARE_X; //Calculate current square number

                //Add a square to our scene
                ui->graphicsView->scene()->addRect(i*square_width,j*square_height,square_width,square_height,QPen(Qt::black),QBrush(Qt::black));
                QGraphicsItem * cur_rekt=new QGraphicsClickableRectItem(i*square_width,j*square_height,square_width,square_height,number);

                ui->graphicsView->scene()->addItem(cur_rekt);


                //Add a label to our square
                QPointer<QGraphicsTextItem> io = new QGraphicsTextItem;
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


//This function activates when we press Return key, when focusted on lineEdit panel.
//It sets correct square boolean to false and redraws the whole playground, making that square disappear.
//Also clears the line edit, making it easy to quickly disable squares.
void MainWindow::on_lineEdit_returnPressed()
{
    int number = ui->lineEdit->text().toInt(); //number from lineEdit



    if(number>0 && number<=SQUARE_X*SQUARE_Y){ //If number is within correct range, disable correct square and redraw.
        squareTurnOff(number);
        //redraw();

    }
    ui->lineEdit->clear(); //Clear lineEdit
}

//On window resize we need to redraw our whole playfield, so the image will be visible.
void MainWindow::resizeEvent(QResizeEvent *event){
    redraw();
}

void MainWindow::squareReset(){
    for(int i=0;i<SQUARE_X;i++){
        for(int j=0;j<SQUARE_Y;j++){
            squares[i][j]=true;
        }
    }
}

void MainWindow::squareTurnOff(int number){
    int number_x=(number-1)%SQUARE_X; //x coordinate taken from number.
    int number_y=(number-1)/SQUARE_X; //y coordinate taken from number.

    squares[number_x][number_y]=false;
    redraw();
}

//static MainWindow *MainWindow::getMainWindow()
//{
//    QWidgetList widgets = qApp->topLevelWidgets();
//    for (QWidgetList::iterator i = widgets.begin(); i != widgets.end(); ++i)
//        if ((*i)->objectName() == "MainWindow")
//            return (MainWindow*) (*i);
//    return NULL;
//}



void MainWindow::on_nextButton_clicked()
{
    constIterator = constIterator!=(filenames.constEnd()-1)   ? ++constIterator : filenames.constBegin();
    cur_image= QPixmap(*constIterator);
    ui->label->setText(*constIterator);
    squareReset();
    redraw();
}

void MainWindow::on_previousButton_clicked()
{
    constIterator = constIterator!=(filenames.constBegin())   ? --constIterator : filenames.constEnd()-1;
    cur_image= QPixmap(*constIterator);
    ui->label->setText(*constIterator);
    squareReset();
    redraw();
}
