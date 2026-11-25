#include <Keypad.h>
#include <Adafruit_LiquidCrystal.h>

Adafruit_LiquidCrystal lcd(0);

const int Temp = A0;
const int SensorPorta = A1;
const int Buzzer = 12;

const byte TecladoL = 4;
const byte TecladoC = 3;

char teclas[TecladoL][TecladoC] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

byte pinosLinhas[TecladoL] = {11, 10, 9, 8};
byte pinosColunas[TecladoC] = {7, 6, 5};

Keypad teclado = Keypad(makeKeymap(teclas), pinosLinhas, pinosColunas, TecladoL, TecladoC);

const int LIMITE_LUZ = 500;
const int TEMP_LIMITE = 28;
const int TEMP_ALVO = 20;

char senhaDigitada[5] = "";
int tamSenha = 0;

bool alarmeArmado = false;
bool alarmeDisparado = false;
bool feixeEstavaCortado = false;

bool arLigado = false;
bool desligadoManual = false;
bool voltandoAoAmbiente = false;
int tempAtual = 25;
int tempSensor = 25;

unsigned long tempoAnteriorBuzzer = 0;
bool estadoSom = false;
unsigned long tempoAnteriorTemp = 0;
unsigned long tempoAnteriorSensores = 0;

bool atualizarLinha0 = true;
bool atualizarLinha1 = true;

void setup() {
  pinMode(Buzzer, OUTPUT);
  noTone(Buzzer);

  teclado.setDebounceTime(1); // Na maquete física real use 20

  lcd.begin(16, 2);

  tempSensor = (analogRead(Temp) * 5.0 / 1024.0 - 0.5) * 100.0;
  tempAtual = tempSensor;
}

void loop() {
  // 1. Lê sensores a cada 200ms (deixa o teclado bem mais leve)
  if (millis() - tempoAnteriorSensores >= 200) {
    tempoAnteriorSensores = millis();

    int leituraLuz = analogRead(SensorPorta);
    if (!alarmeArmado && leituraLuz >= LIMITE_LUZ) {
      alarmeArmado = true;
    }

    bool feixeCortado = (leituraLuz < LIMITE_LUZ);
    if (alarmeArmado && feixeCortado && !feixeEstavaCortado) {
      alarmeDisparado = true;
      atualizarLinha1 = true;
      tone(Buzzer, 440);
      estadoSom = true;
      tempoAnteriorBuzzer = millis();
    }
    feixeEstavaCortado = feixeCortado;

    tempSensor = (analogRead(Temp) * 5.0 / 1024.0 - 0.5) * 100.0;
    bool tempAlta = (tempSensor >= TEMP_LIMITE);

    if (!tempAlta) {
      desligadoManual = false;
    }

    if (tempAlta && !arLigado && !desligadoManual) {
      arLigado = true;
      voltandoAoAmbiente = false;
      atualizarLinha0 = true;
    }
  }

  // 2. Buzzer com bip curto (100ms ligado, 500ms desligado) para diminuir lag no Tinkercad
  if (alarmeDisparado) {
    unsigned long agora = millis();
    if (estadoSom && (agora - tempoAnteriorBuzzer >= 100)) {
      noTone(Buzzer);
      estadoSom = false;
      tempoAnteriorBuzzer = agora;
    } else if (!estadoSom && (agora - tempoAnteriorBuzzer >= 500)) {
      tone(Buzzer, 440);
      estadoSom = true;
      tempoAnteriorBuzzer = agora;
    }
  } else if (estadoSom) {
    noTone(Buzzer);
    estadoSom = false;
  }

  // 3. Transição da Temperatura (250ms)
  if (arLigado) {
    if (millis() - tempoAnteriorTemp >= 250) {
      tempoAnteriorTemp = millis();
      if (tempAtual > TEMP_ALVO) {
        tempAtual--;
        atualizarLinha0 = true;
      }
    }
  } else {
    if (voltandoAoAmbiente) {
      if (millis() - tempoAnteriorTemp >= 250) {
        tempoAnteriorTemp = millis();
        if (tempAtual < tempSensor) {
          tempAtual++;
          atualizarLinha0 = true;
        } else {
          voltandoAoAmbiente = false;
        }
      }
    } else if (tempAtual != tempSensor) {
      tempAtual = tempSensor;
      atualizarLinha0 = true;
    }
  }
  