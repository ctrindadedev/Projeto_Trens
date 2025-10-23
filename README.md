# 🚂 Projeto Sistemas Operacionais - Simulação de Malha Ferroviária

[cite_start]Este projeto consiste na simulação de uma malha ferroviária com 6 trens [cite: 5] [cite_start]utilizando threads para execução concorrente e mecanismos de sincronização (mutexes/semáforos) para evitar colisões e deadlocks[cite: 9, 29].

[cite_start]O trabalho é proposto para a disciplina de Sistemas Operacionais (IMD0036) [cite: 3] [cite_start]do Instituto Metrópole Digital (IMD)[cite: 2].

---

## 💡 Objetivo

[cite_start]O objetivo é desenvolver uma malha ferroviária onde 6 trens percorrem livremente seus percursos sem colisão ou travamentos[cite: 5, 9]. [cite_start]A solução deve garantir o máximo assincronismo, com cada trem agindo de forma independente[cite: 25].

## ⚙️ Requisitos da Solução

Os requisitos mínimos para a implementação incluem:

1.  [cite_start]**Concorrência:** Cada trem deve ser executado em uma **thread totalmente independente** da outra[cite: 24].
2.  [cite_start]**Sincronização:** Utilizar **exclusivamente mutexes ou semáforos** para evitar colisão e deadlocks[cite: 29].
3.  [cite_start]**Regiões Críticas:** Considerar a existência de, pelo menos, **7 (sete) mutexes ou semáforos** correspondentes às regiões críticas (pontos de colisão numerados de 0 a 6 na Figura 2)[cite: 10, 16, 28].
4.  [cite_start]**Movimento:** Se o trem *pode* se mover sem causar colisão ou deadlock, ele *deve* se mover, evitando travamentos desnecessários[cite: 26, 27].
5.  [cite_start]**Interface:** A tela principal deve ser composta pela malha ferroviária (Figura 1) e pelo controle de velocidade (Figura 3)[cite: 30].
    * [cite_start]Os trens devem começar a se mover **automaticamente** na abertura do executável[cite: 32].

## 🚄 Descrição dos Trens e Percursos

| Trem (ID) | Cor | Malha | Sentido |
| :---: | :---: | :--- | :---: |
| 1 | Verde | Interna | [cite_start]Horário [cite: 7] |
| 2 | Vermelho | Interna | [cite_start]Horário [cite: 7] |
| 3 | Azul | Interna | [cite_start]Horário [cite: 7] |
| 4 | Laranja | Interna | [cite_start]Horário [cite: 7] |
| 5 | Roxo | Interna | [cite_start]Horário [cite: 7] |
| 6 | Preto | Externa | [cite_start]Anti-horário [cite: 8] |

## 🚦 Controle de Velocidade

[cite_start]O controle de velocidade de cada trem é feito por um *slider*[cite: 17].

* [cite_start]**Limites do Slider:** 0 a 200[cite: 34].
* [cite_start]**Velocidade Mínima (0):** O trem para seu movimento[cite: 34].
* [cite_start]**Velocidade Máxima (200):** O trem atinge a velocidade máxima (adotando um valor de tal forma que o trem anda realmente rápido na tela)[cite: 17, 18].

## 🛠️ Tecnologias

* C++
* Qt Framework (para threads e interface gráfica)

## 📁 Estrutura do Repositório (Exemplo)