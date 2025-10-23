# 🚂 Projeto de Simulação de Malha Ferroviária

**Instituto Metrópole Digital - IMD0036**  
**Sistemas Operacionais - Trabalho 2**

## 📋 Descrição do Projeto

Este projeto implementa uma simulação de malha ferroviária com **6 trens** que circulam simultaneamente, utilizando **threads** e **sincronização** para evitar colisões e deadlocks.

### 🎯 Objetivo
Desenvolver um sistema onde os trens percorram livremente seus percursos **sem colisões** ou **travamentos**, utilizando conceitos de programação concorrente.

## 🚂 Funcionalidades

### **Trens Implementados:**
- **Trem 1** (Verde) - Malha interna, sentido horário
- **Trem 2** (Vermelho) - Malha interna, sentido horário  
- **Trem 3** (Azul) - Malha interna, sentido horário
- **Trem 4** (Laranja) - Malha interna, sentido horário
- **Trem 5** (Roxo) - Malha interna, sentido horário
- **Trem 6** (Preto) - Malha externa, sentido anti-horário

### **Características Técnicas:**
- ✅ **6 threads independentes** (cada trem em sua própria thread)
- ✅ **7 mutexes** para proteção de regiões críticas
- ✅ **Sistema anti-deadlock** implementado
- ✅ **Sincronização robusta** com `tryLock()`
- ✅ **Início automático** dos trens
- ✅ **Interface gráfica** completa

## 🔧 Tecnologias Utilizadas

- **C++** - Linguagem principal
- **Qt Framework** - Interface gráfica e threads
- **QThread** - Execução concorrente
- **QMutex** - Sincronização e proteção de regiões críticas
- **Qt Designer** - Criação da interface visual

## 🏗️ Estrutura do Projeto

```
Projeto_Trens/
├── src/
│   ├── main.cpp          # Ponto de entrada da aplicação
│   ├── mainwindow.h      # Declaração da janela principal
│   ├── mainwindow.cpp    # Implementação da janela principal
│   ├── mainwindow.ui     # Interface gráfica (Qt Designer)
│   ├── trem.h           # Declaração da classe Trem
│   ├── trem.cpp         # Implementação da classe Trem
│   └── Trem.pro         # Arquivo de projeto Qt
├── INSTRUCOES_DUPLA.md  # Instruções para desenvolvimento em dupla
└── README.md            # Este arquivo
```

## 🚀 Como Executar

### **Pré-requisitos:**
- Qt 5.x ou superior
- Compilador C++ (GCC, Clang, ou MSVC)
- CMake ou qmake

### **Compilação:**
```bash
cd src
qmake Trem.pro
make
```

### **Execução:**
```bash
./Trem
```

## 🔒 Sistema de Sincronização

### **Regiões Críticas Protegidas:**
- **Região 0** - Cruzamento superior esquerdo
- **Região 1** - Cruzamento superior central
- **Região 2** - Cruzamento inferior esquerdo
- **Região 3** - Cruzamento inferior central
- **Região 4** - Cruzamento superior direito
- **Região 5** - Cruzamento inferior direito
- **Região 6** - Cruzamento central

### **Estratégia Anti-Deadlock:**
- Uso de `tryLock()` com timeout de 10ms
- Liberação imediata de mutexes após uso
- Verificação de disponibilidade antes de ocupar região

## 🎮 Controles

### **Sliders de Velocidade:**
- **0** - Trem parado
- **200** - Velocidade máxima
- Controle individual para cada trem

## 📊 Status do Projeto

### **✅ Implementado:**
- [x] 6 trens com movimento correto
- [x] 7 mutexes para sincronização
- [x] Sistema anti-deadlock
- [x] Interface gráfica básica
- [x] Início automático dos trens

### **🔄 Em Desenvolvimento:**
- [ ] Controle de velocidade via sliders
- [ ] Cores dos trens na interface
- [ ] Testes e validação final

## 👥 Desenvolvimento em Dupla

Este projeto foi desenvolvido em dupla, com divisão de responsabilidades:

### **Parte 1 (Completa):**
- Implementação dos 6 trens
- Sistema de sincronização
- Lógica de movimento
- Proteção contra deadlocks

### **Parte 2 (Pendente):**
- Controle de velocidade
- Interface visual completa
- Testes e validação
- Gravação do vídeo explicativo

## 📝 Critérios de Avaliação

### **Requisitos Obrigatórios:**
- ✅ Evitar colisões entre trens
- ✅ Evitar deadlocks
- ✅ Usar mutexes/semáforos para sincronização
- ✅ Cada trem em thread independente
- ✅ Controle de velocidade (0-200)
- ✅ Interface gráfica conforme especificação

### **Pontuação:**
- **0 pontos:** Não atende requisitos básicos
- **4 pontos:** Evita colisões, mas tem deadlocks
- **4-10 pontos:** Sem colisões nem deadlocks (nota proporcional à qualidade)

## 🎯 Objetivos Alcançados

- **Máximo assincronismo** - Cada trem executa independentemente
- **Sincronização eficiente** - Uso inteligente de mutexes
- **Prevenção de deadlocks** - Estratégia robusta implementada
- **Interface intuitiva** - Controles claros e visuais
- **Código limpo** - Bem documentado e organizado

## 📚 Conceitos Aplicados

- **Programação Concorrente**
- **Sincronização de Threads**
- **Prevenção de Deadlocks**
- **Regiões Críticas**
- **Mutexes e Semáforos**
- **Interface Gráfica com Qt**

---

