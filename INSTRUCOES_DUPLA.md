# 👥 INSTRUÇÕES PARA O CAIO MEDEIROS

## 📋 SUA PARTE DO TRABALHO (50%)

### **✅ O QUE JÁ ESTÁ FEITO:**
- 6 trens implementados (trem1, trem2, trem3, trem4, trem5, trem6)
- 7 mutexes para sincronização (regiões 0, 1, 2, 3, 4, 5, 6)
- Lógica de movimento de todos os trens
- Sistema de sincronização completo (sem deadlocks)
- Interface gráfica básica (malha ferroviária)
- Início automático dos trens

### **🎯 O QUE VOCÊ PRECISA IMPLEMENTAR:**

#### **1. 🎮 CONTROLE DE VELOCIDADE:**
- Implementar função `setVelocidade()` na classe Trem
- Criar sliders para todos os 6 trens
- Implementar funções `on_sliderTrem1_valueChanged()` até `on_sliderTrem6_valueChanged()`
- Conectar sliders às funções de velocidade

#### **2. 🎨 INTERFACE GRÁFICA COMPLETA:**
- Adicionar labels para todos os 6 trens na interface (.ui)
- Implementar cores corretas (Verde, Vermelho, Azul, Laranja, Roxo, Preto)
- Adicionar sliders visuais para controle de velocidade
- Ajustar layout da malha ferroviária

#### **3. 🧪 TESTES E VALIDAÇÃO:**
- Compilar o projeto no Linux
- Testar se todos os 6 trens se movem corretamente
- Verificar se não há colisões
- Validar se os sliders funcionam (0-200)
- Testar diferentes velocidades


### **📝 ONDE IMPLEMENTAR:**

**Arquivo `src/mainwindow.h`:**
```cpp
// Adicionar slots para os sliders:
void on_sliderTrem1_valueChanged(int value);
void on_sliderTrem2_valueChanged(int value);
void on_sliderTrem3_valueChanged(int value);
void on_sliderTrem4_valueChanged(int value);
void on_sliderTrem5_valueChanged(int value);
void on_sliderTrem6_valueChanged(int value);
```

**Arquivo `src/mainwindow.cpp`:**
```cpp
// Implementar as funções dos sliders
// Conectar sliders às funções de velocidade
```

**Arquivo `src/trem.h`:**
```cpp
// Adicionar função:
void setVelocidade(int vel);
```

**Arquivo `src/trem.cpp`:**
```cpp
// Implementar setVelocidade()
```

**Arquivo `src/mainwindow.ui`:**
```xml
<!-- Adicionar labels para todos os 6 trens -->
<!-- Adicionar sliders para controle de velocidade -->
<!-- Ajustar cores dos trens -->
<!-- Melhorar layout da malha -->
```

**Verificar:**
- ✅ Todos os 6 trens se movem
- ✅ Não há colisões
- ✅ Sliders controlam velocidade (0-200)
- ✅ Trens iniciam automaticamente
- ✅ Cores estão corretas


