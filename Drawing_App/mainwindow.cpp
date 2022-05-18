#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <qstring.h>

QTimer timer;
QPen pen;
int widthPen_default = 1;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->eraseButton->setEnabled(false);
    ui->colorComboBox->setItemData(1, QBrush(Qt::red), Qt::BackgroundRole);
    ui->colorComboBox->setItemData(2, QBrush(Qt::green), Qt::BackgroundRole);
    ui->colorComboBox->setItemData(3, QBrush(Qt::blue), Qt::BackgroundRole);
    ui->colorComboBox->setItemData(4, QBrush(Qt::black), Qt::BackgroundRole);
    ui->colorComboBox->setItemData(4, QBrush(Qt::white), Qt::ForegroundRole);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_drawButton_clicked()
{
    ui->statusbar->showMessage("Drawing....", 10000);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    int w = width(), h= height();
    int xx1= w/2;
    int yy1= h/2;
    int xx2= w/2;
    int yy2= h/2;

    QFile file("C:/Users/Osman/Desktop/out2.txt"); //UPDATE!

    if(!file.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::warning(this,"Warning", "File not open");
    }

    QTextStream in(&file);

    rotate=0;
    while (!in.atEnd()) {

        QString line = in.readLine().trimmed();

        if(line.mid(0,5) == "COLOR"){

            if(((line.mid(5, line.length())).trimmed())=="M"){
                pen.setColor(Qt::blue);

            }
            else if(((line.mid(5, line.length())).trimmed())=="Y"){
                pen.setColor(Qt::green);
            }
            else if(((line.mid(5, line.length())).trimmed())=="K"){
                pen.setColor(Qt::red);
            }
            else if(((line.mid(5, line.length())).trimmed())=="S"){
                pen.setColor(Qt::black);
            }

        }

        else if(line.mid(0,3) == "pen"){
            widthPen_default = ((line.mid(3, line.length())).trimmed()).toInt();
            pen.setWidth(widthPen_default);
        }

        else if(line.mid(0,1) == "f"){

            delayPen(150);

            number= ((line.mid(1, line.length())).trimmed()).toInt();

            // Create the line object
            QLineF* angleLine= new QLineF();

            // Set the first point
            angleLine->setP1(QPointF(xx1,yy1).toPoint());

            angleLine->setAngle(rotate);
            angleLine->setLength(number);

            // Draw the line
            scene->addLine( angleLine->toLine(), pen);
            xx1 = angleLine->x2();
            yy1 = angleLine->y2();

            //qDebug()<< "number:" << number;

        }

        else if(line.mid(0,1) == "r"){

            rotate += ((line.mid(1, line.length())).trimmed()).toInt();
            // qDebug()<< "rotate:" << rotate;
        }
        else if(line=="RESET"){ //after loop-> L 4[F 100 R 90] R10
            xx1=xx2;
            yy1=yy2;
        }

        else{
            qDebug()<< "empty line...";
        }

    }
    file.close();
    //file.open(QFile::WriteOnly | QFile::Truncate);
    ui->statusbar->showMessage("Drawing is complete... Erase button activated.", 1000);
    ui->eraseButton->setEnabled(true);
}

void MainWindow::on_eraseButton_clicked()
{
    ui->graphicsView->scene()->clear(); // Drawing area clear
    ui->statusbar->showMessage("Drawing area cleared.", 500);
}

void MainWindow::on_errorButton_clicked()
{
    ui->statusbar->showMessage("Error messages are shown", 500);
    QFile file("C:/Users/Osman/Desktop/hata_mesajlari.txt"); //UPDATE!
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::warning(this,"Warning", "File not open");
    }

    QTextStream in(&file);
    QString line;

    while(!in.atEnd()) {
        line.append(in.readLine() + " ");
        ui->label->setText(line);
    }
    file.close();
    //file.open(QFile::WriteOnly | QFile::Truncate);

}

void MainWindow::on_commandButton_clicked()
{
    //Open Flex and Bison application
    system("start C:\\Users\\Osman\\Desktop\\odev-main\\parser.exe"); //UPDATE!
    ui->statusbar->showMessage("Command screen opened.", 500);
}

void MainWindow::on_colorComboBox_currentIndexChanged(int index)
{
    if(index == 1) {
        pen.setColor("red");
        ui->statusbar->showMessage("Red color selected.", 500);
    }
    else if(index == 2) {
        pen.setColor("green");
        ui->statusbar->showMessage("Green color selected.", 500);
    }
    else if(index == 3) {
        pen.setColor("blue");
        ui->statusbar->showMessage("Blue color selected.", 500);
    }
    else if(index == 4) {
        pen.setColor("black");
        ui->statusbar->showMessage("Black color selected.", 500);
    }
}


void MainWindow::on_widthComboBox_currentIndexChanged(int index)
{
    if(index == 1) {
        pen.setWidth(1);
        ui->statusbar->showMessage("Width 1 selected", 500);
    }
    else if(index == 2) {
        pen.setWidth(2);
        ui->statusbar->showMessage("Width 2 selected", 500);
    }
    else if(index == 3) {
        pen.setWidth(3);
        ui->statusbar->showMessage("Width 3 selected", 500);
    }
}

void MainWindow::on_actionOpen_File_triggered()
{
    //Open Flex and Bison application
    system("start C:\\Users\\Osman\\Desktop\\odev-main\\parser.exe"); //UPDATE!
    ui->statusbar->showMessage("Command screen opened.", 500);
}


void MainWindow::on_actionExit_triggered()
{
    MainWindow::close();
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::information(this,"About","COM2004 - Automata Theory Term Project");
}


void MainWindow::on_actionContributors_triggered()
{
    QMessageBox::about(this,"Contributors","Can OZGAN (Lexer)\nDogan YILMAZ (Parser)\nOsman Can AKSOY (GUI Design)");
}

void MainWindow::delayPen( int msec ) {
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < dieTime ){
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

    }
    //qDebug()<<"timer...";
}

