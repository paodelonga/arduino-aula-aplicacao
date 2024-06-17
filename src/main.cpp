#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Servo.h>
#include <math.h>


#define PINO_PRIMEIRO_SENSOR A1
#define PINO_SEGUNDO_SENSOR A2
#define PINO_TERCEIRO_SENSOR A3
#define PINO_PUSH_BUTTON A5

double posicao_do_sensor[3] = {25, 50, 85};
double tempo_do_sensor[4];

// cppcheck-suppress unusedFunction
void setup() {
  pinMode(PINO_PRIMEIRO_SENSOR, INPUT);
  pinMode(PINO_SEGUNDO_SENSOR, INPUT);
  pinMode(PINO_TERCEIRO_SENSOR, INPUT);

  Serial.begin(115200);
  while (!Serial) {
    delay(250);
  }

}

// cppcheck-suppress unusedFunction
void loop() {

if(button.pressed()) {
  while(1) {
    if (analogRead() < 600) {
    }
    while(1) {
      if (analogRead() < 600) {
      }
      while(1) {
      }
    }
  }
}


}