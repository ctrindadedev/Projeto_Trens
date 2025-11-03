#include "trem.h"
#include "mainwindow.h"
#include <QtCore>

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
                if (x == 290 && y==40)
                    emit ocupaTrilho(this->ID, 0);
                else if(x==290 && y == 160){
                    x-=10;
                    emit desocupaTrilho(0);
                }
                else if (x == 310 && y == 140)
                    emit ocupaTrilho(this->ID, 2);
                else if (x == 150 && y == 160){
                    x-=10;
                    emit desocupaTrilho(2);
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
                if (x == 330 && y==160){
                    emit ocupaTrilho(this->ID, 0);
                }
                else if(x==310 && y == 40){
                    x+=10;
                    emit desocupaTrilho(0);
                }
                else if (x == 560 && y==40){
                    emit ocupaTrilho(this->ID, 1);
                }
                else if(x==560 && y == 160){
                    x-=10;
                    emit desocupaTrilho(1);
                }
                else if (x == 460 && y==160){
                    emit ocupaTrilho(this->ID, 3);
                }
                else if(x==310 && y == 140){
                    y-=10;
                    emit desocupaTrilho(3);
                }
                else if (x == 580 && y==140){
                    emit ocupaTrilho(this->ID, 4);
                }
                else if(x==420 && y == 160){
                    x-=10;
                    emit desocupaTrilho(4);
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
                if (x == 730 && y==160){
                    emit ocupaTrilho(this->ID, 5);
                }
                else if(x==580 && y == 140){
                    y-=10;
                    emit desocupaTrilho(5);
                }
                else if (x == 600 && y==160){
                    emit ocupaTrilho(this->ID, 1);
                }
                else if(x == 600 && y == 40){
                    x+=10;
                    emit desocupaTrilho(1);
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
                if (x == 170 && y==180){
                    emit ocupaTrilho(this->ID, 2);
                }
                else if(x==330 && y == 160){
                    x+=10;
                    emit desocupaTrilho(2);
                }
                else if (x == 290 && y==160){
                    emit ocupaTrilho(this->ID, 3);
                }
                else if(x == 440 && y == 180){
                    y+=10;
                    emit desocupaTrilho(3);
                }
                else if (x == 420 && y==160){
                    emit ocupaTrilho(this->ID, 6);
                }
                else if(x == 420 && y == 280){
                    x-=10;
                    emit desocupaTrilho(6);
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
                if (x == 440 && y== 180){
                    emit ocupaTrilho(this->ID, 4);
                }
                else if(x == 600 && y == 160){
                    x+=10;
                    emit desocupaTrilho(4);
                }
                else if (x == 560 && y==160){
                    emit ocupaTrilho(this->ID, 5);
                }
                else if(x == 710 && y == 180){
                    y+=10;
                    emit desocupaTrilho(5);
                }
                else if (x == 460 && y==280){
                    emit ocupaTrilho(this->ID, 6);
                }
                else if(x == 460 && y == 160){
                    x+=10;
                    emit desocupaTrilho(6);
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
                if (x == 20 && y > 20)  
                    y-=10;
                else if (y == 20 && x < 870) 
                    x+=10;
                else if (x == 870 && y < 300) 
                    y+=10;
                else if (y == 300 && x > 20) 
                    x-=10;
                
                emit updateGUI(ID, x, y, vel);    //Emite um sinal
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