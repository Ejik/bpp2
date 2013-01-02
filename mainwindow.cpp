#include <QDesktopWidget>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aboutview.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Поместим в центр экрана
    int w = QApplication::desktop()->width(); //ширина экрана
    w /= 2;
    w -= this->width()/2;
    int h = QApplication::desktop()->height(); //высота экрана
    h /= 2;
    h -= this->height()/2;

    move(w, h);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::on_actionAbout_triggered()
{
    AboutView view;
    view.exec();
}
