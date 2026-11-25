# 🏠 Casa Inteligente com Arduino — Sistema de Segurança e Climatização

Projeto prático desenvolvido para a unidade curricular de **IoT (Internet das Coisas) / Sistemas Embarcados** do **Curso Técnico do SENAI**, utilizando **Arduino Uno R3** aplicado em uma maquete residencial e validado previamente em simulação no **Tinkercad**.

---

## 📋 Sobre o Projeto

O sistema simula duas frentes essenciais de automação residencial (**Casa Inteligente**):

1. **Climatização Automática (Ar-Condicionado Inteligente):**
   * O sensor **TMP36** monitora continuamente a temperatura ambiente e a exibe em tempo real no **Display LCD 16x2 (I2C)**.
   * Ao atingir ou ultrapassar a temperatura limite configurada (`32 °C` na maquete física / `28 °C` na simulação), o sistema aciona automaticamente o modo de refrigeração (`AR:ON`), reduzindo gradualmente a temperatura exibida até atingir `20 °C` e mantendo-a estabilizada (`20C FIXO`).
   * A tecla **`#`** do teclado permite ligar ou desligar o ar-condicionado manualmente a qualquer momento.

2. **Segurança Residencial (Barreira Laser + Senha):**
   * Um par **Laser + Sensor LDR** posicionado na porta de entrada monitora a passagem de pessoas.
   * Quando o feixe de luz é interrompido, o sistema detecta a invasão, exibe o alerta `INVASAO!` no LCD e aciona o **Buzzer** (`440 Hz` intermitente).
   * O alarme só é desativado após a inserção da senha correta (**`1234`**) no **Teclado Matricial 3x4** (a tecla **`*`** apaga os dígitos caso haja erro de digitação).

---

## 🧰 Componentes Utilizados

| Componente | Função no Projeto | Observações |
| :--- | :--- | :--- |
| **Arduino Uno R3** | Microcontrolador principal | Processamento dos sensores e atuadores |
| **Teclado Matricial 3x4** | Entrada de senha e controle manual | `1234` desarma alarme \| `*` limpa \| `#` liga/desliga ar |
| **Display LCD 16x2 (I2C)** | Interface visual | Exibe temperatura, status do ar e alertas |
| **Sensor de Temperatura TMP36** | Leitura térmica analógica | Acionamento automático do ar-condicionado |
| **Sensor LDR + Módulo Laser 5V** | Barreira óptica na porta | Detecção de entrada / invasão |
| **Buzzer Passivo (Piezo)** | Sinalização sonora | Alerta sonoro suave (`440 Hz`) |
| **Resistores e Protoboard** | Apoio ao circuito | `10 kΩ` (pull-down do LDR) e `220 Ω` (opcional no buzzer) |

---

## 🔌 Esquema de Ligação (Pinagem)

| Componente | Pino do Componente | Pino no Arduino Uno |
| :--- | :--- | :--- |
| **Teclado 3x4** | Linhas 1 a 4 | `11, 10, 9, 8` |
| **Teclado 3x4** | Colunas 1 a 3 | `7, 6, 5` |
| **Buzzer** | Positivo (`+`) / Negativo (`-`) | `12` / `GND` |
| **TMP36** | VCC / Vout / GND | `5V` / `A0` / `GND` |
| **LDR (Porta)** | Terminal 1 / Terminal 2 | `5V` / `A1` (+ Resistor `10 kΩ` para `GND`) |
| **Módulo Laser** | VCC (`+`) / GND (`-`) | `5V` / `GND` |
| **LCD 16x2 I2C** | GND / VCC / SDA / SCL | `GND` / `5V` / `A4` / `A5` |

---

## 📚 Bibliotecas Necessárias (Arduino IDE)

Para compilar e enviar o código para o Arduino físico, instale as seguintes bibliotecas pelo **Gerenciador de Bibliotecas** da Arduino IDE:

* **`Keypad`** — *Mark Stanley, Alexander Brevig*
* **`LiquidCrystal I2C`** — *Frank de Brabander*

> **Nota para simulação no Tinkercad:** No ambiente do Tinkercad (LCD com controlador padrão MCP23008), utiliza-se a biblioteca `#include <Adafruit_LiquidCrystal.h>` no lugar de `<LiquidCrystal_I2C.h>` e `teclado.setDebounceTime(1)` para melhor resposta no navegador.

---

## ⚙️ Como Usar na Prática

1. **Clone ou baixe** este repositório:
   ```bash
   git clone https://github.com/SEU-USUARIO/NOME-DO-REPOSITORIO.git
   ```
2. **Abra o arquivo `.ino`** na **Arduino IDE**.
3. Selecione a placa **Arduino Uno** em `Ferramentas > Placa` e a porta serial correta em `Ferramentas > Porta`.
4. Faça o **Upload** para a placa.
5. **Calibração rápida na maquete:**
   * Caso o LCD acenda sem exibir caracteres, ajuste o potenciômetro azul de contraste atrás do módulo I2C (ou altere o endereço `0x27` para `0x3F`).
   * Alinhe o laser diretamente sobre o LDR na porta (recomenda-se um pequeno tubo opaco no LDR para evitar interferência da luz ambiente). Se necessário, ajuste a constante `LIMITE_LUZ` conforme a leitura no Monitor Serial.
   * Ajuste `TEMP_LIMITE` conforme a temperatura ambiente do local de apresentação.

---

## 🎮 Comandos do Sistema

* **`1` `2` `3` `4`** → Desativa o alarme quando disparado.
* **`*`** → Apaga os números digitados da senha.
* **`#`** → Liga ou desliga manualmente o ar-condicionado.

---

## 🔗 Simulação

* **Link do circuito no Tinkercad:** *[Inserir link da simulação aqui]*

---

## 👥 Equipe — Curso Técnico SENAI

* **[Nome do Integrante 1]** — *[Ex: Programação / Montagem]*
* **[Nome do Integrante 2]** — *[Ex: Maquete / Documentação]*
* **[Nome do Integrante 3]** — *[Ex: Circuito / Testes]*

---
## 📄 Licença

Este projeto está licenciado sob a **GNU General Public License v3.0 (GPL-3.0)** — veja o arquivo [LICENSE](LICENSE) para mais detalhes.
