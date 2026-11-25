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

