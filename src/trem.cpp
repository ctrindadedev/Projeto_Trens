#include "trem.h"
#include "mainwindow.h"
#include <QtCore>
#include <semaphore.h>

extern sem_t semaforos[7];
extern sem_t master_lock; 

Trem::Trem(int ID, int x, int y, int vel){
    this->ID = ID;
    this->x = x;
    this->y = y;
    setVel(vel); 
}

//Função de verificação e espera 
void Trem::entrarNaRegiao(int id_Trilho) {
    int aux;
    while(true) {
        sem_getvalue(&semaforos[id_Trilho], &aux);
        if(aux > 0) { 
            sem_wait(&semaforos[id_Trilho]); 
            break; 
        }
        msleep(10); 
    }
}

// Lógica de verificação anti-deadlock 
void Trem::entrarNaRegiao(int id_Trilho, int id_Trilho_Dependente) {
    int aux1, aux2;
     while(true) {
        sem_wait(&master_lock); // Trava a verificação
        
        sem_getvalue(&semaforos[id_Trilho], &aux1);
        sem_getvalue(&semaforos[id_Trilho_Dependente], &aux2);

        if(aux1 > 0 && aux2 > 0) { // Se ambas estiverem livres
            sem_wait(&semaforos[id_Trilho]); // Trava a região
            sem_post(&master_lock); // Liberta a verificação
            break; 
        }
        
        sem_post(&master_lock); // Liberta a verificação (se não conseguiu)
        msleep(10); // Espera 10ms e tenta novamente
    }
}


//Função a ser executada após executar trem->START
void Trem::run(){
    while(true){
        if(vel > 0) 
        {
            switch(ID){
            case 1:     //Trem 1 (Verde)
                // LÓGICA DE UNLOC
                if(x == 290 && y == 160){ // Ponto de saída da R0
                    sem_post(&semaforos[0]);
                }
                else if(x == 150 && y == 160){ // Ponto de saída da R2
                    sem_post(&semaforos[2]);
                }

                // LÓGICA DE MOVIMENTO E LOCK
                if (y == 40 && x < 310) // Movendo para a direita
                {
                    if(x == 280) 
                        entrarNaRegiao(0, 2); // Pedir R0 (verificando R2)
                    x+=10;
                }
                else if (x == 310 && y < 160) // Movendo para baixo
                {
                    if(y == 130) 
                        entrarNaRegiao(2); // Pedir R2
                    y+=10;
                }
                else if (x > 40 && y == 160) // Movendo para a esquerda
                {
                    x-=10;
                }
                else if (y > 40 && x == 40) // Movendo para cima
                {
                    y-=10;
                }
                emit updateGUI(ID, x, y, vel); 
                break;
                
            case 2: //Trem 2 (Vermelho)
                // LÓGICA DE UNLOCK
                if(x == 310 && y == 40){ // Ponto de saída da R0
                    sem_post(&semaforos[0]);
                }
                else if(x == 560 && y == 160){ // Ponto de saída da R1
                    sem_post(&semaforos[1]);
                }
                else if(x == 310 && y == 140){ // Ponto de saída da R3
                    sem_post(&semaforos[3]);
                }
                else if(x == 420 && y == 160){ // Ponto de saída da R4
                    sem_post(&semaforos[4]);
                }

                // LÓGICA DE MOVIMENTO E LOCK
                if (y == 40 && x < 580) // Movendo para a direita
                {
                    if(x == 550) 
                        entrarNaRegiao(1, 5);
                    x+=10;
                }
                else if (x == 580 && y < 160) // Movendo para baixo
                {
                    if(y == 130) 
                        entrarNaRegiao(4, 3); // Pedir R4 (verificando R3)
                    y+=10;
                }
                else if (x > 310 && y == 160) // Movendo para a esquerda
                {
                    if(x == 470) 
                        entrarNaRegiao(3); // Pedir R3
                    else if (x == 340)
                        entrarNaRegiao(0); // Pedir R0
                    x-=10;
                }
                else if (y > 40 && x == 310) // Movendo para cima
                {
                    y-=10;
                }
                emit updateGUI(ID, x, y, vel); 
                break;
                
            case 3: //Trem 3 (Azul)
                // LÓGICA DE UNLOCK
                if(x == 580 && y == 140){ // Ponto de saída da R5
                    sem_post(&semaforos[5]);
                }
                else if(x == 600 && y == 40){ // Ponto de saída da R1
                    sem_post(&semaforos[1]);
                }

                if (y == 40 && x < 850) // Movendo para a direita
                {
                    x+=10;
                }
                else if (x == 850 && y < 160) // Movendo para baixo
                {
                    y+=10;
                }
                else if (x > 580 && y == 160) // Movendo para a esquerda
                {
                    if(x == 740) 
                        entrarNaRegiao(5, 1); // Pedir R5 (verificando R1)
                    else if(x == 610) 
                        entrarNaRegiao(1); // Pedir R1
                    x-=10;
                }
                else if (y > 40 && x == 580) // Movendo para cima
                {
                    y-=10;
                }
                emit updateGUI(ID, x, y, vel);  
                break;
                
            case 4: //Trem 4 (Laranja)
                // LÓGICA DE UNLOCK
                if(x == 330 && y == 160){ // Ponto de saída da R2
                    sem_post(&semaforos[2]);
                }
                else if(x == 440 && y == 180){ // Ponto de saída da R3
                    sem_post(&semaforos[3]);
                }
                else if(x == 420 && y == 280){ // Ponto de saída da R6
                    sem_post(&semaforos[6]);
                }

                // LÓGICA DE MOVIMENTO E LOCK
                if (y == 160 && x < 440) // Movendo para a direita
                {
                    if(x == 280) 
                        entrarNaRegiao(3, 4); // Pedir R3 (verificando R4)
                    else if (x == 410) 
                        entrarNaRegiao(6); // Pedir R6
                    x+=10;
                }
                else if (x == 440 && y < 280) // Movendo para baixo
                {
                    y+=10;
                }
                else if (x > 170 && y == 280) // Movendo para a esquerda
                {
                    x-=10;
                }
                else if (y > 160 && x == 170) // Movendo para cima
                {
                    if(y == 190) 
                        entrarNaRegiao(2, 0); // Pedir R2 (verificando R0)
                    y-=10;
                }
                emit updateGUI(ID, x, y, vel);
                break;
                
            case 5: //Trem 5 (Roxo)
                // LÓGICA DE UNLOCK
                if(x == 600 && y == 160){ // Ponto de saída da R4
                    sem_post(&semaforos[4]);
                }
                else if(x == 710 && y == 180){ // Ponto de saída da R5
                    sem_post(&semaforos[5]);
                }
                else if(x == 460 && y == 160){ // Ponto de saída da R6
                    sem_post(&semaforos[6]);
                }

                // LÓGICA DE MOVIMENTO E LOCK
                if (y == 160 && x < 710) // Movendo para a direita
                {
                    if(x == 550) 
                        entrarNaRegiao(5); // Pedir R5
                    x+=10;
                }
                else if (x == 710 && y < 280) // Movendo para baixo
                {
                    y+=10;
                }
                else if (x > 440 && y == 280) // Movendo para a esquerda
                {
                    if(x == 470) 
                        entrarNaRegiao(6); // Pedir R6
                    x-=10;
                }
                else if (y > 160 && x == 440) // Movendo para cima
                {
                    if(y == 190) 
                        entrarNaRegiao(4, 5); // Pedir R4 (verificando R5)
                    y-=10;
                }
                emit updateGUI(ID, x, y, vel); 
                break;
            
            case 6: // Trem 6 (preto) - Sem locks
                if (x == 20 && y > 20)  
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
            msleep(200);
        }
    }
}

void Trem::setVel(int value){
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