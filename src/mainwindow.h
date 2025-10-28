#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "trem.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void updateInterface(int,int,int);
    
private slots:
    // Slots para controle de velocidade (auto-conectados pelo Qt)
    void on_sliderTrem1_valueChanged(int value);
    void on_sliderTrem2_valueChanged(int value);
    void on_sliderTrem3_valueChanged(int value);
    void on_sliderTrem4_valueChanged(int value);
    void on_sliderTrem5_valueChanged(int value);
    void on_sliderTrem6_valueChanged(int value);

private:
    Ui::MainWindow *ui;

    Trem *trem1;
    Trem *trem2;
    Trem *trem3; 
    Trem *trem4;
    Trem *trem5; 
    Trem *trem6;
};

#endif 