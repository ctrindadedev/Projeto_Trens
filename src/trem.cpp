#include "trem.h"
#include <QtCore>

// Inicialização dos mutexes estáticos (7 regiões críticas)
QMutex Trem::mutexRegiao0;
QMutex Trem::mutexRegiao1;
QMutex Trem::mutexRegiao2;
QMutex Trem::mutexRegiao3;
QMutex Trem::mutexRegiao4;
QMutex Trem::mutexRegiao5;
QMutex Trem::mutexRegiao6;

//Construtor
Trem::Trem(int ID, int x, int y){
    this->ID = ID;
    this->x = x;
    this->y = y;
    velocidade = 100;
}


void Trem::setVelocidade(int vel){
    // O slider vai de 0 (parado) a 200 (max) 
    // A velocidade é o tempo de sleep.
    this->velocidade = 200 - vel;
}

//Função a ser executada após executar trem->START
void Trem::run(){
    while(true){
        if(ID >= 1 && ID <= 5){
            moverTremInterno(); 
        } else if(ID == 6){
            moverTremExterno(); 
        }
        //Aatualizar interface
        emit updateGUI(ID, x, y); 
        msleep(velocidade);
    }
}

// Movimento dos trens internos (1-5) - sentido horário
void Trem::moverTremInterno(){
    // Cada trem tem seu próprio retângulo interno
    switch(ID){
    case 1: // Trem 1 - Retângulo pequeno (esquerda)
        if (y == 30 && x < 200) {
            if(ocuparRegiao(0)) { 
                x += 10;
                liberarRegiao(0);
            }
        }
        else if (x == 200 && y < 100) {
            if(ocuparRegiao(1)) { 
                y += 10;
                liberarRegiao(1);
            }
        }
        else if (x > 60 && y == 100) {
            if(ocuparRegiao(2)) { 
                x -= 10;
                liberarRegiao(2);
            }
        }
        else {
            if(ocuparRegiao(3)) { 
                y -= 10;
                liberarRegiao(3);
            }
        }
        break;
        
    case 2: 
        if (y == 30 && x < 400) {
            if(ocuparRegiao(1)) { 
                x += 10;
                liberarRegiao(1);
            }
        }
        else if (x == 400 && y < 100) {
            if(ocuparRegiao(4)) { 
                y += 10;
                liberarRegiao(4);
            }
        }
        else if (x > 200 && y == 100) {
            if(ocuparRegiao(2)) { 
                x -= 10;
                liberarRegiao(2);
            }
        }
        else {
            if(ocuparRegiao(1)) { 
                y -= 10;
                liberarRegiao(1);
            }
        }
        break;
        
    case 3: // Trem 3 - Retângulo grande (direita)
        if (y == 30 && x < 600) {
            if(ocuparRegiao(4)) { 
                x += 10;
                liberarRegiao(4);
            }
        }
        else if (x == 600 && y < 100) {
            if(ocuparRegiao(5)) { 
                y += 10;
                liberarRegiao(5);
            }
        }
        else if (x > 400 && y == 100) {
            if(ocuparRegiao(4)) {
                x -= 10;
                liberarRegiao(4);
            }
        }
        else {
            if(ocuparRegiao(4)) { 
                y -= 10;
                liberarRegiao(4);
            }
        }
        break;
        
    case 4: // Trem 4 - Retângulo inferior esquerdo
        if (y == 100 && x < 200) {
            if(ocuparRegiao(2)) { 
                x += 10;
                liberarRegiao(2);
            }
        }
        else if (x == 200 && y < 170) {
            if(ocuparRegiao(6)) { 
                y += 10;
                liberarRegiao(6);
            }
        }
        else if (x > 60 && y == 170) {
            if(ocuparRegiao(3)) { 
                x -= 10;
                liberarRegiao(3);
            }
        }
        else {
            if(ocuparRegiao(2)) { 
                y -= 10;
                liberarRegiao(2);
            }
        }
        break;
        
    case 5: // Trem 5 - Retângulo inferior direito
        if (y == 100 && x < 400) {
            if(ocuparRegiao(6)) { 
                x += 10;
                liberarRegiao(6);
            }
        }
        else if (x == 400 && y < 170) {
            if(ocuparRegiao(5)) { 
                y += 10;
                liberarRegiao(5);
            }
        }
        else if (x > 200 && y == 170) {
            if(ocuparRegiao(6)) {
                x -= 10;
                liberarRegiao(6);
            }
        }
        else {
            if(ocuparRegiao(6)) {
                y -= 10;
                liberarRegiao(6);
            }
        }
        break;
    }
}

// Movimento do trem externo (6) - sentido anti-horário
void Trem::moverTremExterno(){
    // Trem 6 percorre a malha externa no sentido anti-horário
    if (y == 10 && x > 50) {
        if(ocuparRegiao(0)) {
            x -= 10;
            liberarRegiao(0);
        }
    }
    else if (x == 50 && y < 190) {
        if(ocuparRegiao(3)) { 
            y += 10;
            liberarRegiao(3);
        }
    }
    else if (x < 610 && y == 190) {
        if(ocuparRegiao(5)) { 
            x += 10;
            liberarRegiao(5);
        }
    }
    else {
        if(ocuparRegiao(0)) { 
            y -= 10;
            liberarRegiao(0);
        }
    }
}

// Tenta ocupar uma região crítica (retorna true se conseguir)
bool Trem::ocuparRegiao(int regiao){
    QMutex* mutex = nullptr;
    
    switch(regiao){
    case 0: mutex = &mutexRegiao0; break;
    case 1: mutex = &mutexRegiao1; break;
    case 2: mutex = &mutexRegiao2; break;
    case 3: mutex = &mutexRegiao3; break;
    case 4: mutex = &mutexRegiao4; break;
    case 5: mutex = &mutexRegiao5; break;
    case 6: mutex = &mutexRegiao6; break;
    }
    
    if(mutex) {
        return mutex->tryLock(10); // Tenta obter o lock por 10ms
    }
    return false;
}

// Libera uma região crítica
void Trem::liberarRegiao(int regiao){
    QMutex* mutex = nullptr;
    
    switch(regiao){
    case 0: mutex = &mutexRegiao0; break;
    case 1: mutex = &mutexRegiao1; break;
    case 2: mutex = &mutexRegiao2; break;
    case 3: mutex = &mutexRegiao3; break;
    case 4: mutex = &mutexRegiao4; break;
    case 5: mutex = &mutexRegiao5; break;
    case 6: mutex = &mutexRegiao6; break;
    }
    
    if(mutex) mutex->unlock();
}




