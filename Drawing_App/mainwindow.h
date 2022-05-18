#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDebug>
#include <QString>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QFile>
#include <QMessageBox>
#include <QTime>
#include <QLineF>
#include <QTimer>
#include <QProcess>
#include <QDir>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int number=0;
    int rotate=0;
    void delayPen(int);

private slots:
    void on_drawButton_clicked();
    void on_eraseButton_clicked();
    void on_errorButton_clicked();
    void on_commandButton_clicked();
    void on_colorComboBox_currentIndexChanged(int index);
    void on_widthComboBox_currentIndexChanged(int index);
    void on_actionOpen_File_triggered();
    void on_actionExit_triggered();
    void on_actionAbout_triggered();
    void on_actionContributors_triggered();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
};
#endif // MAINWINDOW_H
