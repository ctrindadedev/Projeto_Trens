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
    Trem(int,int,int);  //construtor
    void run();         //função a ser executada pela thread
    // TODO: Caio Medeiros deve implementar setVelocidade()

    // Mutexes para as 7 regiões críticas
    static QMutex mutexRegiao0;  // Região crítica 0
    static QMutex mutexRegiao1;  // Região crítica 1
    static QMutex mutexRegiao2;  // Região crítica 2
    static QMutex mutexRegiao3;  // Região crítica 3
    static QMutex mutexRegiao4;  // Região crítica 4
    static QMutex mutexRegiao5;  // Região crítica 5
    static QMutex mutexRegiao6;  // Região crítica 6

//Cria um sinal
signals:
    void updateGUI(int,int,int);

private:
   int x;           //posição X do trem na tela
   int y;           //posição Y do trem na tela
   int ID;          //ID do trem
   int velocidade;  //Velocidade. É o tempo de dormir em milisegundos entre a mudança de posição do trem
   
   // Funções auxiliares para movimento
   void moverTremInterno();  // Movimento dos trens 1-5 (malha interna, horário)
   void moverTremExterno();  // Movimento do trem 6 (malha externa, anti-horário)
   bool ocuparRegiao(int regiao); // Tenta ocupar uma região crítica (retorna true se conseguir)
   void liberarRegiao(int regiao); // Libera uma região crítica
};

#endif // TREM_H
