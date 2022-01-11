#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


    void on_searchCont_clicked();

    void on_searchCountry_clicked();



    void on_backCountry_clicked();

    void on_backCont_clicked();

    void on_loadButton_clicked();

    // void on_loadCountry_clicked();

    void on_startOver_clicked();

    void on_loadCountry_clicked();

    void on_currentLibrary_clicked();

    void on_pushButton_clicked();//dfs

    void on_pushButton_2_clicked();//bfs
    void on_backAll_clicked();

    //void on_continentDrop_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
