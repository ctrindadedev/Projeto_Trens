#include "trem.h"
#include <QtCore>
#include <QDebug> 

Trem::Trem(int ID, int x, int y, QMutex *m0, QMutex *m1, QMutex *m2, QMutex *m3, QMutex *m4, QMutex *m5, QMutex *m6){
    this->ID = ID;
    this->x = x;
    this->y = y;
    this->velocidade = 100; //(Meia barra +-)

    //Ponteiros dos mutexes
    this->mutex0 = m0;
    this->mutex1 = m1;
    this->mutex2 = m2;
    this->mutex3 = m3;
    this->mutex4 = m4;
    this->mutex5 = m5;
    this->mutex6 = m6;
}

void Trem::setVelocidade(int vel){
    // O slider vai de 0 (parado) a 200 (max) e a velocidade é o tempo do sleep
    this->velocidade = 200 - vel;
}


void Trem::run(){
    while(true){
        switch(ID){
        case 1: // Trem 1 (Verde) - Percurso: (60,30) -> (330,30) -> (330,150) -> (60,150) -> (60,30)
            if (y == 30 && x < 330){ // Move para direita no trilho superior
                if (x == 310) { // Próximo da região crítica 1
                    mutex1->lock(); // Trava RC1
                    x += 10;
                } else if (x == 180) { // Próximo da região crítica 0
                    mutex0->lock(); // Trava RC0
                    x += 10;
                }
                 else x += 10;
            }
            else if (x == 330 && y < 150){ // Move para baixo no trilho direito
                 if(y==130){ // Saindo da RC1, Próximo da RC4
                     mutex1->unlock(); // Libera RC1
                     mutex4->lock(); // Trava RC4
                     y+=10;
                 } else if (y == 10) { // Saindo da RC0
                     mutex0->unlock(); // Libera RC0
                     y += 10;
                 }
                 else y += 10;
            }
            else if (x > 60 && y == 150){ // Move para esquerda no trilho inferior
                if (x == 200) { // Saindo da RC4, Próximo da RC3
                    mutex4->unlock(); // Libera RC4
                    mutex3->lock(); // Trava RC3
                    x -= 10;
                } else x -= 10;
            }
            else { // Move para cima no trilho esquerdo
                if (y == 50) { // Saindo da RC3
                    mutex3->unlock(); // Libera RC3
                    y -= 10;
                } else y -= 10;
            }
            break;
        case 2: // Trem 2 (Vermelho) - Percurso: (330,30) -> (600,30) -> (600,150) -> (330,150) -> (330,30)
            if (y == 30 && x < 600){ // Move para direita no trilho superior
                if (x == 580) { // Próximo da RC2
                    mutex2->lock(); // Trava RC2
                    x += 10;
                } else if(x == 350) { // Saindo da RC1, Próximo da RC0
                    mutex1->unlock(); // Libera RC1
                    mutex0->lock(); // Trava RC0
                    x += 10;
                }
                else x += 10;
            }
            else if (x == 600 && y < 150){ // Move para baixo no trilho direito
                if (y == 130) { // Saindo da RC2, Próximo da RC5
                    mutex2->unlock(); // Libera RC2
                    mutex5->lock(); // Trava RC5
                    y += 10;
                } else if (y==10) { // Saindo da RC0
                    mutex0->unlock(); // Libera RC0
                    y += 10;
                }
                 else y += 10;
            }
            else if (x > 330 && y == 150){ // Move para esquerda no trilho inferior
                if (x == 470) { // Saindo da RC5, Próximo da RC4
                    mutex5->unlock(); // Libera RC5
                    mutex4->lock(); // Trava RC4
                     x -= 10;
                }
                else x -= 10;
            }
            else { // Move para cima no trilho esquerdo
                if (y == 50) { // Saindo da RC4, Próximo da RC1
                    mutex4->unlock(); // Libera RC4
                    mutex1->lock(); // Trava RC1
                     y -= 10;
                }
                 else y -= 10;
            }
            break;
        case 3: // Trem 3 (Azul) - Percurso: (600,30) -> (870,30) -> (870,150) -> (600,150) -> (600,30)
            if (y == 30 && x < 870){ // Move para direita no trilho superior
                 if (x == 620) { // Saindo da RC2
                    mutex2->unlock(); // Libera RC2
                    x += 10;
                 }
                else { // Continua movendo para a direita
                    x += 10;
                }
            }
            else if (x == 870 && y < 150){ // Move para baixo no trilho direito
                // Nenhuma RC neste segmento
                y += 10;
            }
            else if (x > 600 && y == 150){ // Move para esquerda no trilho inferior
                if (x == 740) { // Próximo da RC5
                    mutex5->lock(); // Trava RC5
                    x -= 10;
                 }
                 else { // Continua movendo para a esquerda
                    x -= 10;
                 }
            }
            else { // Move para cima no trilho esquerdo (x == 600)
                if (y == 50) { // Saindo da RC5, Próximo da RC2
                    mutex5->unlock(); // Libera RC5
                    mutex2->lock(); // Trava RC2
                    y -= 10;
                 } else { // Continua movendo para cima
                     y -= 10;
                 }
            }
            break;
        case 4: // Trem 4 (Laranja) - Percurso: (200,150) -> (470,150) -> (470,270) -> (200,270) -> (200,150)
            if (y == 150 && x < 470){ // Move para direita no trilho superior (do T4)
                if (x == 310) { // Próximo da RC4
                    mutex4->lock(); // Trava RC4
                    x += 10;
                } else if (x == 220) { // Saindo da RC3
                    mutex3->unlock(); // Libera RC3
                    x += 10;
                } else x += 10;
            }
            else if (x == 470 && y < 270){ // Move para baixo no trilho direito (do T4)
                if (y == 170) { // Saindo da RC4, Próximo da RC5
                    mutex4->unlock(); // Libera RC4
                    mutex5->lock(); // Trava RC5
                    y += 10;
                } else y += 10;
            }
            else if (x > 200 && y == 270){ // Move para esquerda no trilho inferior (do T4)
                if (x == 350) { // Próximo da RC6
                    mutex6->lock(); // Trava RC6
                    x -= 10;
                } else if(x == 450) { // Saindo da RC5
                    mutex5->unlock(); // Libera RC5
                    x -= 10;
                } else x -= 10;
            }
            else { // Move para cima no trilho esquerdo (do T4)
                if (y == 170) { // Saindo da RC6, Próximo da RC3
                    mutex6->unlock(); // Libera RC6
                    mutex3->lock(); // Trava RC3
                    y -= 10;
                } else y -= 10;
            }
            break;
        case 5: // Trem 5 (Roxo) - Percurso: (470,150) -> (740,150) -> (740,270) -> (470,270) -> (470,150)
            if (y == 150 && x < 740){ // Move para direita no trilho superior (do T5)
                if (x == 580) { // Próximo da RC5
                    mutex5->lock(); // Trava RC5
                    x += 10;
                } else if(x == 490) { // Saindo da RC4
                     mutex4->unlock(); // Libera RC4
                     x += 10;
                 }
                else x += 10;
            }
            else if (x == 740 && y < 270){ // Move para baixo no trilho direito (do T5)
                if (y==170){ // Saindo da RC5
                     mutex5->unlock(); // Libera RC5
                     y+=10;
                 } else y += 10;
            }
            else if (x > 470 && y == 270){ // Move para esquerda no trilho inferior (do T5)
                if (x == 620) { // Próximo da RC6
                    mutex6->lock(); // Trava RC6
                     x -= 10;
                 }
                 else x -= 10;
            }
            else { // Move para cima no trilho esquerdo (do T5)
                 if(y==170){ // Saindo da RC6, Próximo da RC4
                     mutex6->unlock(); // Libera RC6
                     mutex4->lock(); // Trava RC4
                     y-=10;
                 } else y -= 10;
            }
            break;
        case 6: // Trem 6 (Preto) - Percurso Externo Anti-horário 
                // (470, 10) -> (50, 10) -> (50, 270) -> (870, 270) -> (870, 10) -> (470, 10)
            if (y == 10 && x > 50) { // Move para esquerda no trilho superior externo
                 if (x == 350) { // Próximo da RC0
                     mutex0->lock(); // Trava RC0
                     x-=10;
                 } else if (x == 620){ // Próximo da RC2
                     mutex2->lock(); // Trava RC2
                     x-=10;
                 } else x -= 10;
            }
            else if (x == 50 && y < 270) { // Move para baixo no trilho esquerdo externo
                if (y == 30) { // Saindo da RC0
                    mutex0->unlock(); // Libera RC0
                    y+=10;
                } else if(y==130){ // Próximo da RC3
                    mutex3->lock(); // Trava RC3
                    y+=10;
                } else y += 10;
            }
            else if (x < 870 && y == 270) { // Move para direita no trilho inferior externo
                if(x==180){ // Saindo da RC3
                    mutex3->unlock(); // Libera RC3
                    x+=10;
                } else if (x == 450) { // Próximo da RC6
                    mutex6->lock(); // Trava RC6
                     x += 10;
                 } else if(x == 720){ // Saindo da RC6
                     mutex6->unlock(); // Libera RC6
                     x+=10;
                 } else x += 10;
            }
            else { // Move para cima no trilho direito externo
                if (y == 170) { // Próximo da RC5
                    mutex5->lock(); // Trava RC5
                     y -= 10;
                 } else if (y==50){ // Saindo da RC2 e RC5
                     mutex2->unlock(); // Libera RC2
                     mutex5->unlock(); // Libera RC5
                     y-=10;
                 } else y -= 10;
            }
            break;
        default:
            break;
        }
        emit updateGUI(ID, x, y); 
        msleep(velocidade);       
    }
}