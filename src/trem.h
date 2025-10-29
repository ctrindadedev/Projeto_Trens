#ifndef TREM_H
#define TREM_H

#include <QThread>
#include <QMutex>

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
    Trem(int,int,int, QMutex*, QMutex*, QMutex*, QMutex*, QMutex*, QMutex*, QMutex*);
    void run(); // Função a ser executada pela thread

    void setVelocidade(int vel);

// Cria um sinal para atualizar a interface
signals:
    void updateGUI(int,int,int);

private:
// Posições X e  Ydo trem na tela
   int x;           
   int y;           
   int ID;          
   int velocidade;  // Velocidade (tempo de sleep em ms)

   // Ponteiros para os mutexes das 7 regiões críticas (recebidos da MainWindow)
   QMutex *mutex0;
   QMutex *mutex1;
   QMutex *mutex2;
   QMutex *mutex3;
   QMutex *mutex4;
   QMutex *mutex5;
   QMutex *mutex6;
};

#endif