#include <Arduino.h>

#define PINO_PRIMEIRO_SENSOR A1
#define PINO_SEGUNDO_SENSOR A2
#define PINO_TERCEIRO_SENSOR A3
#define PINO_PUSH_BUTTON 1
#define PINO_LED_VERDE 2
#define PINO_LED_AMARELO 3

const double POSICAO_DO_SENSOR[3] = {25, 50, 85};

double tempo_do_sensor[4];

// cppcheck-suppress unusedFunction
void setup() {
  pinMode(PINO_PRIMEIRO_SENSOR, INPUT);
  pinMode(PINO_SEGUNDO_SENSOR, INPUT);
  pinMode(PINO_TERCEIRO_SENSOR, INPUT);

  pinMode(PINO_PUSH_BUTTON, INPUT);

  pinMode(PINO_LED_VERDE, OUTPUT);
  pinMode(PINO_LED_AMARELO, OUTPUT);

  Serial.begin(115200);
  while (!Serial) {
    delay(250);
  }

  digitalWrite(PINO_LED_VERDE, LOW);
  digitalWrite(PINO_LED_AMARELO, LOW);
}

// cppcheck-suppress unusedFunction
void loop() {
  tempo_do_sensor[0] = millis();
  if (digitalRead(PINO_PUSH_BUTTON) == HIGH) {
    digitalWrite(PINO_LED_VERDE, HIGH);
    Serial.println("INICIANDO SENSORES");
    Serial.println("LIBERE O OBJETO");

    while (1) {
      if (analogRead(PINO_PRIMEIRO_SENSOR) < 600) {
        tempo_do_sensor[1] = millis() - tempo_do_sensor[0];
        digitalWrite(PINO_LED_VERDE, LOW);
        digitalWrite(PINO_LED_AMARELO, HIGH);
        Serial.println("PRIMEIRO SENSOR INTERROMPIDO");

        while (1) {
          if (analogRead(PINO_SEGUNDO_SENSOR) < 600) {
            tempo_do_sensor[2] = millis() - tempo_do_sensor[0];
            Serial.println("SEGUNDO SENSOR INTERROMPIDO");

            while (1) {
              if (analogRead(PINO_TERCEIRO_SENSOR) < 600) {
                tempo_do_sensor[3] = millis() - tempo_do_sensor[0];
                Serial.println("TERCEIRO SENSOR INTERROMPIDO");
                return;
              }
              digitalWrite(PINO_LED_AMARELO, LOW);
              Serial.println("LEITURA FINALIZADA");
            }
          }
        }
      }
      if (digitalRead(PINO_PUSH_BUTTON) == HIGH) {
        digitalWrite(PINO_LED_VERDE, LOW);
        return;
      }
    }
  }
}
