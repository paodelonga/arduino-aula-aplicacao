#include <Arduino.h>
#include <math.h>

#define PINO_PRIMEIRO_SENSOR A1
#define PINO_SEGUNDO_SENSOR A2
#define PINO_TERCEIRO_SENSOR A3
#define PINO_PUSH_BUTTON A5

const double POSICAO_DO_SENSOR[3] = {25, 50, 85};

double tempo_do_sensor[4];

// cppcheck-suppress unusedFunction
void setup() {
  pinMode(PINO_PRIMEIRO_SENSOR, INPUT);
  pinMode(PINO_SEGUNDO_SENSOR, INPUT);
  pinMode(PINO_TERCEIRO_SENSOR, INPUT);
  pinMode(PINO_PUSH_BUTTON, INPUT);

  Serial.begin(115200);
  while (!Serial) {
    delay(250);
  }
}

// cppcheck-suppress unusedFunction
void loop() {
  if (digitalRead(PINO_PUSH_BUTTON) == HIGH) {
    while (1) {
      if (analogRead(PINO_PRIMEIRO_SENSOR) < 600) {
        tempo_do_sensor[1] = millis();

        while (1) {
          if (analogRead(PINO_SEGUNDO_SENSOR) < 600) {
            tempo_do_sensor[2] = millis();

            while (1) {
              if (analogRead(PINO_TERCEIRO_SENSOR) < 600) {
                tempo_do_sensor[3] = millis();

              }
            }
          }
        }
      }
      if (digitalRead(PINO_PUSH_BUTTON) == HIGH) {
        break;
      }
    }
  }
}
