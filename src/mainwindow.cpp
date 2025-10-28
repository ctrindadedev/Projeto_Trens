#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Trens internos (1-5): malha interna
    trem1 = new Trem(1, 60, 30);   // Verde - canto superior esquerdo
    trem2 = new Trem(2, 200, 30);  // Vermelho - centro superior
    trem3 = new Trem(3, 400, 30);  // Azul - canto superior direito
    trem4 = new Trem(4, 60, 100);  // Laranja - canto inferior esquerdo
    trem5 = new Trem(5, 200, 100); // Roxo - centro inferior
    
    // Trem externo (6): malha externa
    trem6 = new Trem(6, 610, 10);  // Preto - malha externa

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

    // Inicia todos os trens automaticamente
    trem1->start();
    trem2->start();
    trem3->start();
    trem4->start();
    trem5->start();
    trem6->start();
}

//Função que será executada quando o sinal UPDATEGUI for emitido 
void MainWindow::updateInterface(int id, int x, int y){
    //Cada caso atualiza a posição dos trens
    switch(id){
    case 1: 
        ui->label_trem1->setGeometry(x,y,21,17);
        break;
    case 2:
        ui->label_trem2->setGeometry(x,y,21,17);
        break;
    case 3: 
        ui->label_trem3->setGeometry(x,y,21,17);
        break;
    case 4: 
        ui->label_trem4->setGeometry(x,y,21,17);
        break;
    case 5: 
        ui->label_trem5->setGeometry(x,y,21,17);
        break;
    case 6: 
        ui->label_trem6->setGeometry(x,y,21,17);
        break;
    default:
        break;
    }
}

MainWindow::~MainWindow()
{
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