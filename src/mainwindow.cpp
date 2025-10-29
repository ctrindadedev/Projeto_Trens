#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    trem1 = new Trem(1, 60, 30,   &mutexRegiao0, &mutexRegiao1, &mutexRegiao2, &mutexRegiao3, &mutexRegiao4, &mutexRegiao5, &mutexRegiao6); // Verde
    trem2 = new Trem(2, 330, 30,  &mutexRegiao0, &mutexRegiao1, &mutexRegiao2, &mutexRegiao3, &mutexRegiao4, &mutexRegiao5, &mutexRegiao6); // Vermelho
    trem3 = new Trem(3, 600, 30,  &mutexRegiao0, &mutexRegiao1, &mutexRegiao2, &mutexRegiao3, &mutexRegiao4, &mutexRegiao5, &mutexRegiao6); // Azul
    trem4 = new Trem(4, 200, 150, &mutexRegiao0, &mutexRegiao1, &mutexRegiao2, &mutexRegiao3, &mutexRegiao4, &mutexRegiao5, &mutexRegiao6); // Laranja
    trem5 = new Trem(5, 470, 150, &mutexRegiao0, &mutexRegiao1, &mutexRegiao2, &mutexRegiao3, &mutexRegiao4, &mutexRegiao5, &mutexRegiao6); // Roxo
    trem6 = new Trem(6, 870, 10,  &mutexRegiao0, &mutexRegiao1, &mutexRegiao2, &mutexRegiao3, &mutexRegiao4, &mutexRegiao5, &mutexRegiao6); // Preto


    /*
     * Conecta o sinal UPDATEGUI à função UPDATEINTERFACE.
     * Cada trem emite sinais que são capturados pela interface
     */
    connect(trem1,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem2,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem3,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem4,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem5,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem6,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));

    trem1->start();
    trem2->start();
    trem3->start();
    trem4->start();
    trem5->start();
    trem6->start();
}

// Assim que o updateGUI for emitido, essa função será chamada
void MainWindow::updateInterface(int id, int x, int y){
    switch(id){
    case 1: // Atualiza a posição do trem verde
        ui->label_trem1->setGeometry(x,y,21,17);
        break;
    case 2: // Atualiza a posição do vermelho
        ui->label_trem2->setGeometry(x,y,21,17);
        break;
    case 3: // Atualiza a posição do trem azul
        ui->label_trem3->setGeometry(x,y,21,17);
        break;
    case 4: // Atualiza a posição do tremk laranja
        ui->label_trem4->setGeometry(x,y,21,17);
        break;
    case 5: // Atualiza a posição do trem roxo
        ui->label_trem5->setGeometry(x,y,21,17);
        break;
    case 6: // Atualiza a posição do trem6 preto
        ui->label_trem6->setGeometry(x,y,21,17);
        break;
    default:
        break;
    }
}

MainWindow::~MainWindow()
{
//Parar as threads antes do destrutor deleta-las
    trem1->terminate(); 
    trem2->terminate();
    trem3->terminate();
    trem4->terminate();
    trem5->terminate();
    trem6->terminate();

    trem1->wait(500);
    trem2->wait(500);
    trem3->wait(500);
    trem4->wait(500);
    trem5->wait(500);
    trem6->wait(500);

    delete trem1;
    delete trem2;
    delete trem3;
    delete trem4;
    delete trem5;
    delete trem6;
    delete ui;
}

void MainWindow::on_sliderTrem1_valueChanged(int value)
{
    trem1->setVelocidade(value);
}

void MainWindow::on_sliderTrem2_valueChanged(int value)
{
    trem2->setVelocidade(value);
}

void MainWindow::on_sliderTrem3_valueChanged(int value)
{
    trem3->setVelocidade(value);
}

void MainWindow::on_sliderTrem4_valueChanged(int value)
{
    trem4->setVelocidade(value);
}

void MainWindow::on_sliderTrem5_valueChanged(int value)
{
    trem5->setVelocidade(value);
}

void MainWindow::on_sliderTrem6_valueChanged(int value)
{
    trem6->setVelocidade(value);
}