#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMutex> 
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
    // Slots para controle de velocidade 
    void on_sliderTrem1_valueChanged(int value);
    void on_sliderTrem2_valueChanged(int value);
    void on_sliderTrem3_valueChanged(int value);
    void on_sliderTrem4_valueChanged(int value);
    void on_sliderTrem5_valueChanged(int value);
    void on_sliderTrem6_valueChanged(int value);

private:
    Ui::MainWindow *ui;

    // Declaração dos 7 Mutexes como membros da MainWindow
    QMutex mutexRegiao0;
    QMutex mutexRegiao1;
    QMutex mutexRegiao2;
    QMutex mutexRegiao3;
    QMutex mutexRegiao4;
    QMutex mutexRegiao5;
    QMutex mutexRegiao6;

    Trem *trem1;
    Trem *trem2;
    Trem *trem3;
    Trem *trem4;
    Trem *trem5;
    Trem *trem6;
};

#endif 