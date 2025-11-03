#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <semaphore.h>

// Semáforos para as 7 regiões críticas
sem_t semaforos [7];
sem_t master_lock;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) 
{
    ui->setupUi(this);

    //Cria o trem com seu (ID, posição X, posição Y, velocidade)
    trem1 = new Trem(1,40,40, ui->horizontalSlider_1->value());
    trem2 = new Trem(2,310,40, ui->horizontalSlider_2->value());
    trem3 = new Trem(3,580,40, ui->horizontalSlider_3->value());
    trem4 = new Trem(4,170,160, ui->horizontalSlider_4->value());
    trem5 = new Trem(5,440,160, ui->horizontalSlider_5->value());
    trem6 = new Trem(6, 20, 300, ui->horizontalSlider_6->value());


    /*
     * Conecta o sinal UPDATEGUI à função UPDATEINTERFACE.
     */
    connect(trem1,SIGNAL(updateGUI(int,int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem2,SIGNAL(updateGUI(int,int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem3,SIGNAL(updateGUI(int,int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem4,SIGNAL(updateGUI(int,int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem5,SIGNAL(updateGUI(int,int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem6,SIGNAL(updateGUI(int,int,int,int)),SLOT(updateInterface(int,int,int)));

    
    // Inicializa os 7 semáforos para as 7 regiões críticas 
    sem_init(&semaforos[0], 0, 1); // R0
    sem_init(&semaforos[1], 0, 1); // R1
    sem_init(&semaforos[2], 0, 1); // R2
    sem_init(&semaforos[3], 0, 1); // R3
    sem_init(&semaforos[4], 0, 1); // R4
    sem_init(&semaforos[5], 0, 1); // R5
    sem_init(&semaforos[6], 0, 1); // R6

    // Inicializa o semáforo mestre
    sem_init(&master_lock, 0, 1);

    // Inicia os trens automaticamente 
    init_trem();
}

//Função que será executada quando o sinal UPDATEGUI for emitido
void MainWindow::updateInterface(int id, int x, int y){
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
    for (int i = 0; i < 7; ++i) {
        sem_destroy(&semaforos[i]);
    }
 
    sem_destroy(&master_lock);
    delete ui;
}

/*
 * Inicia a execução das threads dos trens
 */
void MainWindow::init_trem()
{
    trem1->start();
    trem2->start();
    trem3->start();
    trem4->start();
    trem5->start();
    trem6->start(); 
}

// Slots de controle de velocidade/sliders
void MainWindow::on_horizontalSlider_1_valueChanged(int value){
    trem1->setVel(value);
};

void MainWindow::on_horizontalSlider_2_valueChanged(int value){
    trem2->setVel(value);
};

void MainWindow::on_horizontalSlider_3_valueChanged(int value){
    trem3->setVel(value);
};

void MainWindow::on_horizontalSlider_4_valueChanged(int value){
    trem4->setVel(value);
};

void MainWindow::on_horizontalSlider_5_valueChanged(int value){
    trem5->setVel(value);
};

void MainWindow::on_horizontalSlider_6_valueChanged(int value){
    trem6->setVel(value);
};