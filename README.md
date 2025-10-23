# 🚂 Projeto de Sistemas Operacionais — Simulação de Malha Ferroviária

Este projeto consiste na **simulação de uma malha ferroviária com 6 trens**, utilizando **threads** para execução concorrente e **mecanismos de sincronização** (mutexes/semáforos) para evitar **colisões** e **deadlocks**.  

O trabalho foi proposto na disciplina **Sistemas Operacionais (IMD0036)** do **Instituto Metrópole Digital (IMD)**.

---

## 💡 Objetivo

O objetivo é desenvolver uma malha ferroviária onde **6 trens** percorrem livremente seus percursos **sem colisões ou travamentos**.  
A solução deve garantir **máximo assincronismo**, com cada trem agindo de forma **independente**.

---

## ⚙️ Requisitos da Solução

Os requisitos mínimos para a implementação incluem:

1. **Concorrência:**  
   Cada trem deve ser executado em uma **thread totalmente independente** das demais.

2. **Sincronização:**  
   Utilizar **exclusivamente mutexes ou semáforos** para evitar colisões e deadlocks.

3. **Regiões Críticas:**  
   Considerar pelo menos **7 mutexes ou semáforos**, correspondentes às regiões críticas (pontos de colisão numerados de 0 a 6).

4. **Movimento:**  
   Se o trem *pode* se mover sem causar colisão ou deadlock, ele *deve* se mover — evitando travamentos desnecessários.

5. **Interface:**  
   A tela principal deve conter:
   - A **malha ferroviária** (Figura 1)  
   - O **controle de velocidade** (Figura 3)

   ➜ Os trens devem começar a se mover **automaticamente** ao iniciar o executável.

---

## 🚄 Descrição dos Trens e Percursos

| Trem (ID) | Cor     | Malha   | Sentido       |
| :--------: | :------: | :------- | :------------: |
| 1 | 🟢 Verde | Interna | Horário |
| 2 | 🔴 Vermelho | Interna | Horário |
| 3 | 🔵 Azul | Interna | Horário |
| 4 | 🟠 Laranja | Interna | Horário |
| 5 | 🟣 Roxo | Interna | Horário |
| 6 | ⚫ Preto | Externa | Anti-horário |

---

## 🚦 Controle de Velocidade

O **controle de velocidade** de cada trem é feito por meio de um **slider**.

- **Limites do slider:** 0 a 200  
- **Velocidade mínima (0):** o trem para completamente  
- **Velocidade máxima (200):** o trem atinge a velocidade máxima (movimento rápido na tela)

---

## 🛠️ Tecnologias Utilizadas

- **C++**
- **Qt Framework** — para threads e interface gráfica

---

## 📁 Estrutura do Repositório (Exemplo)

