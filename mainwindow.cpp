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
    squareReset(true);
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
    if(filenames.isEmpty())
        return;
    constIterator=filenames.constBegin();
    //QString fileName = QFileDialog::getOpenFileName(this,tr("Open Image"), "", tr("Image Files (*.png *.jpg *.bmp)"));
    cur_image= QPixmap(*constIterator);
    ui->label->setText(*constIterator);
    squareReset(true);
    redraw();
}

int MainWindow::countUsedSquares(){
    int count = 0;
    for(int i =0;i<SQUARE_X;++i){
        for(int j=0;j<SQUARE_Y;++j){
            if(!squares[i][j])
                ++count;
        }
    }
    return count;
}

int MainWindow::countUsedMiddleSquares(){
    int count = 0;
    for(int i =1;i<SQUARE_X-1;++i){
        for(int j=1;j<SQUARE_Y-1;++j){
            if(!squares[i][j])
                ++count;
        }
    }
    return count;
}

//This function redraws the whole playground.
void MainWindow::redraw()
{
  if(ui->graphicsView->scene()){
     ui->graphicsView->scene()->clear();
     ui->graphicsView->scene()->deleteLater();
  }
  QPointer<QGraphicsScene> scene= new QGraphicsScene;

     //ui->graphicsView->fitInView(ui->graphicsView->scene()->sceneRect() );
    if(!cur_image.isNull())
        scene->addPixmap(cur_image.scaled(ui->graphicsView->width(),ui->graphicsView->height(),Qt::KeepAspectRatio ,Qt::SmoothTransformation));
    ui->graphicsView->setRenderHints(QPainter::Antialiasing
            | QPainter::SmoothPixmapTransform
            | QPainter::TextAntialiasing);
    ui->graphicsView->setScene(scene);
      ui->graphicsView->fitInView(ui->graphicsView->scene()->sceneRect(),Qt::KeepAspectRatio );


/*
    QPointer<QGraphicsScene> scene= new QGraphicsScene;
    if(!cur_image.isNull())
        scene->addPixmap(cur_image);
        //scene->addPixmap(cur_image.scaled(ui->graphicsView->scene()->width(),ui->graphicsView->scene()->height(),Qt::KeepAspectRatio ,Qt::SmoothTransformation));
    ui->graphicsView->setRenderHints(QPainter::Antialiasing
            | QPainter::SmoothPixmapTransform
            | QPainter::TextAntialiasing);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->fitInView(ui->graphicsView->scene()->sceneRect(),Qt::KeepAspectRatio );
*/

    //qreal square_width=ui->graphicsView->scene()->width()/SQUARE_X;
    //qreal square_height=ui->graphicsView->scene()->height()/SQUARE_Y;

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
    int points = (SQUARE_X*SQUARE_Y/2-(countUsedSquares()/2)*2) - countUsedMiddleSquares();
    points = points>0 ? points : 1;
    ui->pointLabel->setText("Punkty:"+QString::number(points));
    if(points == 1)
       ui->pointLabel->setStyleSheet("QLabel {color : red; }");
    ui->graphicsView->show();
}


//This function activates when we press Return key, when focusted on lineEdit panel.
//It sets correct square boolean to false and redraws the whole playground, making that square disappear.
//Also clears the line edit, making it easy to quickly disable squares.
void MainWindow::on_lineEdit_returnPressed()
{
    int number = ui->lineEdit->text().toInt(); //number from lineEdit



    if(number>0 && number<=filenames.length()){ //If number is within correct range, disable correct square and redraw.
        constIterator = filenames.begin()+(number-1);
        cur_image= QPixmap(*constIterator);
        ui->label->setText(*constIterator);
        squareReset(true);
        redraw();

    }
    ui->lineEdit->clear(); //Clear lineEdit
}

//On window resize we need to redraw our whole playfield, so the image will be visible.
void MainWindow::resizeEvent(QResizeEvent *event){
    redraw();
}

//This function resets the squares, so they are true or false
void MainWindow::squareReset(bool type){
    for(int i=0;i<SQUARE_X;i++){
        for(int j=0;j<SQUARE_Y;j++){
            squares[i][j]=type;
        }
    }
    ui->pointLabel->setStyleSheet("QLabel {color : black; }");
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
    squareReset(true);
    redraw();
}

void MainWindow::on_previousButton_clicked()
{
    constIterator = constIterator!=(filenames.constBegin())   ? --constIterator : filenames.constEnd()-1;
    cur_image= QPixmap(*constIterator);
    ui->label->setText(*constIterator);
    squareReset(true);
    redraw();
}

void MainWindow::on_RevealButton_clicked()
{
    squareReset(false);
    redraw();
}
