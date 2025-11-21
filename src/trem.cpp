#include "trem.h"
#include "mainwindow.h"
#include <QtCore>
#include <semaphore.h>

// Declaração externa dos semáforos (definidos em mainwindow.cpp)
extern sem_t semaforos[11];

Trem::Trem(int ID, int x, int y, int vel){
    this->ID = ID;
    this->x = x;
    this->y = y;
    // Garante que a velocidade inicial esteja dentro dos limites 0-200 
    setVel(vel); 
}

//Função a ser executada após executar trem->START
void Trem::run(){
    while(true){
        // O trem só se move se a velocidade for maior que 0 
        if(vel > 0) 
        {
            switch(ID){
            case 1:     //Trem 1 (Verde)
                // Lock ANTES de entrar na RC 0 e 2
                if (x == 280 && y==40) {
                    sem_wait(&semaforos[0]);
                    sem_wait(&semaforos[2]);
                    x+=10;
                }
                // Dentro da RC 0 e 2, mantém semáforos
                else if (x == 290 && y==40) {
                    x+=10;
                }
                // Ainda dentro da RC 0 e 2, mantém semáforos
                else if(x==300 && y == 40){
                    x+=10;
                }
                // Unlock DEPOIS de sair completamente da RC 0 e 2 (quando sai para y=50)
                else if(x==310 && y == 40){
                    y+=10;
                    sem_post(&semaforos[0]);
                    sem_post(&semaforos[2]);
                }
                // Lock ANTES de entrar na RC 2
                else if (x == 310 && y == 130) {
                    sem_wait(&semaforos[2]);
                    y+=10;
                }
                // Dentro da RC 2, mantém semáforo
                else if (x == 310 && y == 140) {
                    y+=10;
                }
                // Ainda dentro da RC 2, mantém semáforo
                else if (x == 310 && y == 150) {
                    y+=10;
                }
                // Unlock DEPOIS de sair completamente da RC 2 (quando muda de direção para esquerda)
                else if (x == 310 && y == 160){
                    x-=10;
                    sem_post(&semaforos[2]);
                }
                else if (y == 40 && x <310)
                    x+=10;
                else if (x == 310 && y < 160)
                    y+=10;
                else if (x > 40 && y == 160)
                    x-=10;
                else
                    y-=10;
                emit updateGUI(ID, x, y, vel); 
                break;
            case 2: //Trem 2 (Vermelho)
                // Lock ANTES de entrar na RC 0
                if (x == 340 && y==160){
                    sem_wait(&semaforos[0]);
                    x-=10;
                }
                // Dentro da RC 0, mantém semáforo
                else if (x == 330 && y==160){
                    x-=10;
                }
                // Ainda dentro da RC 0, mantém semáforo
                else if (x == 320 && y==160){
                    x-=10;
                }
                // Unlock DEPOIS de sair completamente da RC 0 (quando muda de direção para cima)
                else if(x==310 && y == 160){
                    y-=10;
                    sem_post(&semaforos[0]);
                }
                // Lock ANTES de entrar na RC 1 e 5 (ordem: menor ID primeiro)
                else if (x == 550 && y==40){
                    sem_wait(&semaforos[1]);
                    sem_wait(&semaforos[5]);
                    x+=10;
                }
                // Dentro da RC 1 e 5, mantém semáforos
                else if (x == 560 && y==40){
                    x+=10;
                }
                // Ainda dentro da RC 1 e 5, mantém semáforos
                else if (x == 570 && y==40){
                    x+=10;
                }
                // Unlock DEPOIS de sair completamente da RC 1 e 5 (quando muda de direção para baixo)
                else if(x==580 && y == 40){
                    y+=10;
                    sem_post(&semaforos[1]);
                    sem_post(&semaforos[5]);
                }
                // Lock ANTES de entrar na RC 3
                else if (x == 470 && y==160){
                    sem_wait(&semaforos[3]);
                    x-=10;
                }
                // Dentro da RC 3 (entre 340 e 470), mantém semáforo e move para esquerda
                else if (x > 340 && x < 470 && y==160){
                    x-=10;
                }
                // Unlock DEPOIS de sair completamente da RC 3 (quando muda de direção para cima)
                else if(x==340 && y == 160){
                    y-=10;
                    sem_post(&semaforos[3]);
                }
                // Lock ANTES de entrar na RC 3 e 4 (ordem: menor ID primeiro)
                else if (x == 580 && y==130){
                    sem_wait(&semaforos[3]);
                    sem_wait(&semaforos[4]);
                    y+=10;
                }
                // Dentro da RC 3 e 4, mantém semáforos
                else if (x == 580 && y==140){
                    y+=10;
                }
                // Ainda dentro da RC 3 e 4, mantém semáforos
                else if (x == 580 && y==150){
                    y+=10;
                }
                // Unlock DEPOIS de sair completamente da RC 3 e 4 (quando muda de direção para esquerda)
                else if(x==580 && y == 160){
                    x-=10;
                    sem_post(&semaforos[3]);
                    sem_post(&semaforos[4]);
                }
                else if (y == 40 && x <580)
                    x+=10;
                else if (x == 580 && y < 160)
                    y+=10;
                else if (x > 310 && y == 160)
                    x-=10;
                else
                    y-=10;
                emit updateGUI(ID, x, y, vel); 
                break;
            case 3: //Trem 3 (Azul)
                // Lock ANTES de entrar na RC 1 e 5 (ordem: menor ID primeiro)
                if (x == 740 && y==160){
                    sem_wait(&semaforos[1]);
                    sem_wait(&semaforos[5]);
                    x-=10;
                }
                // Dentro da RC 1 e 5, mantém semáforos (indo para esquerda)
                else if (x > 580 && x < 740 && y==160){
                    x-=10;
                }
                // Ainda dentro da RC 1 e 5, mantém semáforos (mudando de direção para cima)
                else if (x == 580 && y==160){
                    y-=10;
                }
                // Ainda dentro da RC 1 e 5, mantém semáforos (subindo)
                else if (x == 580 && y > 140 && y < 160){
                    y-=10;
                }
                // Unlock DEPOIS de sair completamente da RC 1 e 5 (quando muda de direção para direita)
                else if(x==580 && y == 140){
                    x+=10;
                    sem_post(&semaforos[1]);
                    sem_post(&semaforos[5]);
                }
                // Lock ANTES de entrar na RC 1
                else if (x == 610 && y==160){
                    sem_wait(&semaforos[1]);
                    x-=10;
                }
                // Dentro da RC 1, mantém semáforo (indo para esquerda)
                else if (x > 580 && x < 610 && y==160){
                    x-=10;
                }
                // Dentro da RC 1, mantém semáforo (mudando de direção para cima)
                else if (x == 580 && y==160){
                    y-=10;
                }
                // Dentro da RC 1, mantém semáforo (subindo)
                else if (x == 580 && y > 40 && y < 160){
                    y-=10;
                }
                // Unlock DEPOIS de sair completamente da RC 1 (quando muda de direção para direita)
                else if(x == 580 && y == 40){
                    x+=10;
                    sem_post(&semaforos[1]);
                }
                else if (y == 40 && x <850)
                    x+=10;
                else if (x == 850 && y < 160)
                    y+=10;
                else if (x > 580 && y == 160)
                    x-=10;
                else
                    y-=10;
                emit updateGUI(ID, x, y, vel);  
                break;
            case 4: //Trem 4 (Laranja)
                // Lock ANTES de entrar na RC 0 e 2 (ordem: menor ID primeiro)
                if (x == 170 && y==190){
                    sem_wait(&semaforos[0]);
                    sem_wait(&semaforos[2]);
                    y-=10;
                }
                // Dentro da RC 0 e 2, mantém semáforos (subindo)
                else if (x == 170 && y > 160 && y < 190){
                    y-=10;
                }
                // Ainda dentro da RC 0 e 2, mantém semáforos
                else if (x == 170 && y==160){
                    x+=10;
                }
                // Dentro da RC 0 e 2, mantém semáforos (indo para direita)
                else if (x > 170 && x < 310 && y==160){
                    x+=10;
                }
                // Unlock DEPOIS de sair completamente da RC 0 e 2 (quando muda de direção para baixo)
                else if(x==310 && y == 160){
                    y+=10;
                    sem_post(&semaforos[0]);
                    sem_post(&semaforos[2]);
                }
                // Lock ANTES de entrar na RC 3 e 4 (ordem: menor ID primeiro)
                else if (x == 280 && y==160){
                    sem_wait(&semaforos[3]);
                    sem_wait(&semaforos[4]);
                    x+=10;
                }
                // Dentro da RC 3 e 4, mantém semáforos
                else if (x > 280 && x < 440 && y==160){
                    x+=10;
                }
                // Ainda dentro da RC 3 e 4, mantém semáforos
                else if (x == 440 && y==160){
                    y+=10;
                }
                // Dentro da RC 3 e 4, mantém semáforos (descendo)
                else if (x == 440 && y > 160 && y < 180){
                    y+=10;
                }
                // Unlock DEPOIS de sair completamente da RC 3 e 4 (quando muda de direção para esquerda)
                else if(x == 440 && y == 180){
                    x-=10;
                    sem_post(&semaforos[3]);
                    sem_post(&semaforos[4]);
                }
                // Lock ANTES de entrar na RC 6
                else if (x == 410 && y==160){
                    sem_wait(&semaforos[6]);
                    x+=10;
                }
                // Dentro da RC 6, mantém semáforo
                else if (x == 420 && y==160){
                    y+=10;
                }
                // Dentro da RC 6, mantém semáforo (descendo)
                else if (x == 420 && y > 160 && y < 280){
                    y+=10;
                }
                // Unlock DEPOIS de sair completamente da RC 6 (quando muda de direção para esquerda)
                else if(x == 420 && y == 280){
                    x-=10;
                    sem_post(&semaforos[6]);
                }
                else if (y == 160 && x <440)
                    x+=10;
                else if (x == 440 && y < 280)
                    y+=10;
                else if (x > 170 && y == 280)
                    x-=10;
                else
                    y-=10;
                emit updateGUI(ID, x, y, vel);
                break;
            case 5: //Trem 5 (Roxo)
                // Lock ANTES de entrar na RC 4 e 5 (ordem: menor ID primeiro)
                if (x == 440 && y== 190){
                    sem_wait(&semaforos[4]);
                    sem_wait(&semaforos[5]);
                    y-=10;
                }
                // Dentro da RC 4 e 5, mantém semáforos (subindo)
                else if (x == 440 && y > 160 && y < 190){
                    y-=10;
                }
                // Ainda dentro da RC 4 e 5, mantém semáforos
                else if (x == 440 && y==160){
                    x+=10;
                }
                // Dentro da RC 4 e 5, mantém semáforos (indo para direita)
                else if (x > 440 && x < 600 && y==160){
                    x+=10;
                }
                // Unlock DEPOIS de sair completamente da RC 4 e 5 (quando muda de direção para cima)
                else if(x == 600 && y == 160){
                    y-=10;
                    sem_post(&semaforos[4]);
                    sem_post(&semaforos[5]);
                }
                // Lock ANTES de entrar na RC 5
                else if (x == 550 && y==160){
                    sem_wait(&semaforos[5]);
                    x+=10;
                }
                // Dentro da RC 5, mantém semáforo
                else if (x > 550 && x < 710 && y==160){
                    x+=10;
                }
                // Ainda dentro da RC 5, mantém semáforo
                else if (x == 710 && y==160){
                    y+=10;
                }
                // Dentro da RC 5, mantém semáforo (descendo)
                else if (x == 710 && y > 160 && y < 180){
                    y+=10;
                }
                // Unlock DEPOIS de sair completamente da RC 5 (quando muda de direção para esquerda)
                else if(x == 710 && y == 180){
                    x-=10;
                    sem_post(&semaforos[5]);
                }
                // Lock ANTES de entrar na RC 6
                else if (x == 470 && y==280){
                    sem_wait(&semaforos[6]);
                    x-=10;
                }
                // Dentro da RC 6, mantém semáforo
                else if (x > 420 && x < 470 && y==280){
                    x-=10;
                }
                // Ainda dentro da RC 6, mantém semáforo
                else if (x == 420 && y==280){
                    y-=10;
                }
                // Dentro da RC 6, mantém semáforo (subindo)
                else if (x == 420 && y > 160 && y < 280){
                    y-=10;
                }
                // Unlock DEPOIS de sair completamente da RC 6 (quando muda de direção para direita)
                else if(x == 420 && y == 160){
                    x+=10;
                    sem_post(&semaforos[6]);
                }
                else if (y == 160 && x <710)
                    x+=10;
                else if (x == 710 && y < 280)
                    y+=10;
                else if (x > 440 && y == 280)
                    x-=10;
                else
                    y-=10;
                emit updateGUI(ID, x, y, vel); 
                break;
            
            //  Trem 6 (preto) malha externa
            case 6: 
                // Lock ANTES de entrar na RC 7 (borda esquerda - onde cruza com trilho do trem 1)
                if (x == 20 && y == 50) {
                    sem_wait(&semaforos[7]);
                    y-=10;
                }
                // Dentro da RC 7, mantém semáforo
                else if (x == 20 && y == 40) {
                    y-=10;
                }
                // Unlock DEPOIS de sair da RC 7
                else if (x == 20 && y == 30) {
                    y-=10;
                    sem_post(&semaforos[7]);
                }
                // Lock ANTES de entrar na RC 8 (borda superior - onde cruza com trilhos dos trens 1,2,3)
                else if (y == 20 && x == 30) {
                    sem_wait(&semaforos[8]);
                    x+=10;
                }
                // Dentro da RC 8, mantém semáforo
                else if (y == 20 && x >= 40 && x <= 300) {
                    x+=10;
                }
                // Unlock DEPOIS de sair da RC 8
                else if (y == 20 && x == 310) {
                    x+=10;
                    sem_post(&semaforos[8]);
                }
                // Lock ANTES de entrar na RC 9 (borda direita - onde cruza com trilho do trem 3)
                else if (x == 870 && y == 50) {
                    sem_wait(&semaforos[9]);
                    y+=10;
                }
                // Dentro da RC 9, mantém semáforo
                else if (x == 870 && y == 60) {
                    y+=10;
                }
                // Unlock DEPOIS de sair da RC 9
                else if (x == 870 && y == 150) {
                    y+=10;
                    sem_post(&semaforos[9]);
                }
                // Lock ANTES de entrar na RC 10 (borda inferior - onde cruza com trilhos dos trens 4,5)
                else if (y == 300 && x == 320) {
                    sem_wait(&semaforos[10]);
                    x-=10;
                }
                // Dentro da RC 10, mantém semáforo
                else if (y == 300 && x <= 310 && x >= 50) {
                    x-=10;
                }
                // Unlock DEPOIS de sair da RC 10
                else if (y == 300 && x == 40) {
                    x-=10;
                    sem_post(&semaforos[10]);
                }
                // Movimento normal (sem regiões críticas)
                else if (x == 20 && y > 20)  
                    y-=10;
                else if (y == 20 && x < 870) 
                    x+=10;
                else if (x == 870 && y < 300) 
                    y+=10;
                else if (y == 300 && x > 20) 
                    x-=10;
                
                emit updateGUI(ID, x, y, vel);
                break;
            default:
                break;
            }
            msleep(200 - vel);
        }
        else {
            // Se vel == 0, apenas dorme para não consumir CPU
            msleep(200);
        }
    }
}

void Trem::setVel(int value){
    // Garante que a velocidade esteja entre 0 e 200 
    if (value < 0)
        this->vel = 0;
    else if (value > 200)
        this->vel = 200;
    else
        this->vel = value;
}

int Trem::getX(){
    return this->x;
};

void Trem::setX(int x){
    this->x = x;
};

int Trem::getY(){
    return this->y;
};

void Trem::setY(int y){
    this->y = y;
};