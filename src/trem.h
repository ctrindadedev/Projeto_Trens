#ifndef TREM_H
#define TREM_H

#include <QThread>
#include <QMutex>
#include <QSemaphore>

/*
 * Classe Trem herda QThread
 * Classe Trem passa a ser uma thread.
 * A função START inicializa a thread. Após inicializada, a thread irá executar a função RUN.
 * Para parar a execução da função RUN da thread, basta executar a função TERMINATE.
 *
*/
class Trem: public QThread{
 Q_OBJECT
public:
    Trem(int,int,int);  
    void run();         //função a ser executada pela thread

    void setVelocidade(int vel);

    // Mutexes para as 7 regiões críticas
    static QMutex mutexRegiao0; 
    static QMutex mutexRegiao1; 
    static QMutex mutexRegiao2; 
    static QMutex mutexRegiao3;  
    static QMutex mutexRegiao4;  
    static QMutex mutexRegiao5; 
    static QMutex mutexRegiao6;  

//Cria um sinal
signals:
    void updateGUI(int,int,int);

private:
   int x;          
   int y;           
   int ID;          
   int velocidade;  //Tempo de dormir em milisegundos entre a mudança de posição do trem
   
   // Funções auxiliares para movimento
   void moverTremInterno();  // Movimento dos trens 1-5 (malha interna, horário)
   void moverTremExterno();  // Movimento do trem 6 (malha externa, anti-horário)
   bool ocuparRegiao(int regiao); 
   void liberarRegiao(int regiao); 
};

#endif 