#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void SetModel(QStandardItemModel *model);
    
private slots:
    void on_actionExit_triggered();

    void on_actionAbout_triggered();

    void CloseApp();
    void CreateBlank();
    void PrintBlank();

    void on_actionCreateBlank_triggered();

    void on_actionPrint_triggered();

    void on_actionHelp_triggered();

private:
    Ui::MainWindow *ui;

    QStandardItemModel *model_;
};

#endif // MAINWINDOW_H
