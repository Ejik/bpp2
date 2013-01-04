#include <QDesktopServices>
#include <QDesktopWidget>
#include <QDir>
#include <QShortcut>
#include <QUrl>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aboutview.h"
#include "f112.h"


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


    // Присваиваем горячие клавиши на собития
    QShortcut* shortcut = new QShortcut(QKeySequence(tr("Esc")), ui->tableView);
    connect(shortcut, SIGNAL(activated()), this, SLOT(CloseApp()));

    shortcut = new QShortcut(QKeySequence(tr("F10")), ui->tableView);
    connect(shortcut, SIGNAL(activated()), this, SLOT(PrintBlank()));

    shortcut = new QShortcut(QKeySequence(tr("Return")), ui->tableView);
    connect(shortcut, SIGNAL(activated()), this, SLOT(CreateBlank()));


}

MainWindow::~MainWindow()
{
    delete ui;
    delete model_;
}

void MainWindow::on_actionExit_triggered()
{
    CloseApp();
}

void MainWindow::on_actionAbout_triggered()
{
    AboutView view;
    view.exec();
}

void MainWindow::on_actionCreateBlank_triggered()
{
    CreateBlank();
}

void MainWindow::on_actionPrint_triggered()
{
    PrintBlank();
}

void MainWindow::CloseApp()
{
    close();
}

void MainWindow::CreateBlank()
{
    ui->statusBar->showMessage(tr("Выполняется обработка"));

    F112 f112;
    f112.CreateF112(model_, ui->tableView->currentIndex(), false);
}

void MainWindow::PrintBlank()
{
    F112 f112;
    f112.CreateF112(model_, ui->tableView->currentIndex(), true);
}

void MainWindow::on_actionHelp_triggered()
{
    QString exe = QDir::toNativeSeparators(QDir::currentPath() + "//bpp.chm");

    QDesktopServices::openUrl(QUrl::fromLocalFile(exe));
}

void MainWindow::SetModel(QStandardItemModel *model)
{
    this->model_ = model;

    // данные
    ui->tableView->setModel(model_);

    int cols_count = model_->columnCount();
    for (int i = 0; i < cols_count; i++)
    {
        if ((i == 0) || (i == 1) || (i == 4) || (i == cols_count - 1))
        {
        }
        else
            ui->tableView->setColumnHidden(i, true);
    }

    ui->tableView->resizeColumnsToContents();

}
