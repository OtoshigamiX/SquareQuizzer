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

void MainWindow::resetLabels()
{
    ui->label->setText(*constIterator);
    ui->label->setVisible(false);
    ui->questionNumLabel->setText(cur_question);
}

//When we click the Load button, we load the current image to the cur_image variable, reset squares
//and redraw the whole playground.
void MainWindow::on_pushButton_clicked()
{
    filenames = QFileDialog::getOpenFileNames(this,tr("Select Images"),"",tr("Image Files (*.png *.jpg *.bmp)"));
    if(filenames.isEmpty())
        return;
    constIterator=filenames.constBegin();
    cur_image= QPixmap(*constIterator);
    resetLabels();
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

bool MainWindow::isBlocked(int i, int j)
{
    int left = i-1;
    int right = i+1;
    int up = j+1;
    int down = j-1;
    return
       (left>=0 && left<SQUARE_X && squares[left][j]) &&
       (right>=0 && right<SQUARE_X && squares[right][j]) &&
       (up>=0 && up<SQUARE_Y && squares[i][up]) &&
       (down>=0 && down<SQUARE_Y && squares[i][down]);
}

bool MainWindow::isMiddle(int i, int j)
{
    return i>0 && i<SQUARE_X-1 && j>0 && j<SQUARE_Y-1;
}


static inline int is_odd(int x) { return x & 1; }

//This function redraws the whole playground.
void MainWindow::redraw()
{
  if(ui->graphicsView->scene()){
     ui->graphicsView->scene()->clear();
     ui->graphicsView->scene()->deleteLater();
  }
  QPointer<QGraphicsScene> scene= new QGraphicsScene;

    if(!cur_image.isNull())
        scene->addPixmap(cur_image.scaled(ui->graphicsView->width(),ui->graphicsView->height(),Qt::KeepAspectRatio ,Qt::SmoothTransformation));
    ui->graphicsView->setRenderHints(QPainter::Antialiasing
            | QPainter::SmoothPixmapTransform
            | QPainter::TextAntialiasing);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->fitInView(ui->graphicsView->scene()->sceneRect(),Qt::KeepAspectRatio );

    qreal square_width=ui->graphicsView->scene()->width()/SQUARE_X;
    qreal square_height=ui->graphicsView->scene()->height()/SQUARE_Y;
    auto usedSquares = countUsedSquares();
    auto usedMidSquares = countUsedMiddleSquares();
    int points = isAltScoringEnabled ?  HALF_OF_SQUARES+1 - usedSquares:
                                       (HALF_OF_SQUARES-(usedSquares/2)*2) - usedMidSquares;
    points = points>0 ? points : 1;
    ui->pointLabel->setText("Punkty:"+QString::number(points));
    if(points == 1)
    {
       ui->pointLabel->setStyleSheet("QLabel {color : red; }");
       cur_color = Qt::darkRed;
    } else
    if(is_odd(usedSquares) && not isAltScoringEnabled)
    {
        cur_color = Qt::darkGray;
    } else
    {
        cur_color = Qt::black;
    }
    for(int i=0;i<SQUARE_X;i++){
        for(int j=0;j<SQUARE_Y;j++){
            if(squares[i][j]){
                int number = (i+1)+j*SQUARE_X; //Calculate current square number

                //Add a square to our scene
                ui->graphicsView->scene()->addRect(i*square_width,j*square_height,square_width,square_height,QPen(cur_color),QBrush(cur_color));
                QGraphicsItem * cur_rekt=new QGraphicsClickableRectItem(i*square_width,j*square_height,square_width,square_height,number,*this);

                ui->graphicsView->scene()->addItem(cur_rekt);

                //Add a label to our square
                QPointer<QGraphicsTextItem> io = new QGraphicsTextItem;
                io->setPos((i*square_width+square_width/2)-50,(j*square_height+square_height/2)-50);
                io->setPlainText(QString::number(number));
                io->setScale(5.0);
                if(isMiddle(i,j))
                {
                    if(isBlocked(i,j))
                    {
                        io->setDefaultTextColor(Qt::red);
                    }
                    else
                    {
                        isAltScoringEnabled ? io->setDefaultTextColor(Qt::white) :
                                              io->setDefaultTextColor(Qt::yellow);
                    }
                }
                else
                {
                    io->setDefaultTextColor(Qt::white);
                }
                ui->graphicsView->scene()->addItem(io);
            }
        }
    }


    ui->graphicsView->show();
}

//This function activates when we press Return key, when focusted on lineEdit panel.
//It jumps to correct question.
//Also clears the line edit.
void MainWindow::on_lineEdit_returnPressed()
{
    int number = ui->lineEdit->text().toInt(); //number from lineEdit

    if(number>0 && number<=filenames.length()){ //If number is within correct range jump to correct question
        constIterator = filenames.cbegin()+(number-1);
        cur_image= QPixmap(*constIterator);
        resetLabels();
        squareReset(true);
        redraw();
    }
    ui->lineEdit->clear(); //Clear lineEdit
}

//On window resize we need to redraw our whole playfield, so the image will be visible.
void MainWindow::resizeEvent(QResizeEvent *){
    if(!cur_image.isNull())
    {
        redraw();
    }
}

//This function resets the squares, so they are true or false
void MainWindow::squareReset(bool type){
    cur_color = Qt::black;
    for(int i=0;i<SQUARE_X;i++){
        for(int j=0;j<SQUARE_Y;j++){
            squares[i][j]=type;
        }
    }
    ui->pointLabel->setStyleSheet("QLabel {color : black; }");
}

void MainWindow::squareTurnOff(int number){
    if(number <=0 || number > SQUARE_X*SQUARE_Y)
        return;
    int number_x=(number-1)%SQUARE_X; //x coordinate taken from number.
    int number_y=(number-1)/SQUARE_X; //y coordinate taken from number.

    squares[number_x][number_y]=false;
    redraw();
}

void MainWindow::updateLabels()
{
    ui->label->setText(*constIterator);
    ui->label->setVisible(false);
    cur_question =  QString::number(constIterator-filenames.constBegin()+1);
    ui->questionNumLabel->setText(cur_question);
}

void MainWindow::nextImage()
{
    if(filenames.empty())
           return;
    constIterator = constIterator!=(filenames.constEnd()-1)   ? ++constIterator : filenames.constBegin();
    cur_image= QPixmap(*constIterator);
    updateLabels();
    squareReset(true);
    redraw();
}

void MainWindow::previousImage()
{
    if(filenames.empty())
           return;
    constIterator = constIterator!=(filenames.constBegin())   ? --constIterator : filenames.constEnd()-1;
    cur_image= QPixmap(*constIterator);
    updateLabels();
    squareReset(true);
    redraw();
}

void MainWindow::on_nextButton_clicked()
{
    nextImage();
}

void MainWindow::on_previousButton_clicked()
{
    previousImage();
}

void MainWindow::on_RevealButton_clicked()
{
    squareReset(false);
    ui->label->setVisible(true);
    redraw();
}

void MainWindow::changeScoring(int state)
{
    isAltScoringEnabled = state;
    squareReset(true);
    redraw();
}

void MainWindow::on_configButton_clicked()
{
    cw.show();
}

