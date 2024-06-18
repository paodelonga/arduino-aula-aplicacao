#include <Arduino.h>

#define PINO_SENSOR A1
#define PINO_PUSH_BUTTON 2
#define PINO_LED 3

double tempo_do_sensor[1];

void setup() {
  pinMode(PINO_SENSOR, INPUT);
  pinMode(PINO_PUSH_BUTTON, INPUT);
  pinMode(PINO_LED, OUTPUT);

  Serial.begin(115200);
  while (!Serial) {
    delay(250);
  }

  digitalWrite(PINO_LED, LOW);
}

void loop() {
  Serial.println("PRESSIONE O BOTÃO PARA INICIAR A LEITURA");
  Serial.println("E AGUARDE O LED ACENDER PARA LIBERAR O OBJETO\n");

  while (1) {
    if (digitalRead(PINO_PUSH_BUTTON) == HIGH) {
      for (byte i = 5; i > 0; i--) {
        Serial.println((String) "LIBERE O OBJETO EM: " + i + "s");
        digitalWrite(PINO_LED, LOW);
        delay(200);
        analogWrite(PINO_LED, 524);
        delay(1000);
      }

      tempo_do_sensor[0] = millis();
      digitalWrite(PINO_LED, HIGH);
      Serial.println("\nLEITURA INICIADA");
      while (1) {
        if (analogRead(PINO_SENSOR) > 1020) {
          tempo_do_sensor[1] = millis() - tempo_do_sensor[0];

          digitalWrite(PINO_LED, LOW);
          Serial.println((String)"OBJETO DETECTADO APOS " + tempo_do_sensor[1] + "ms");
          Serial.println("LEITURA FINALIZADA\n");

          digitalWrite(PINO_LED, HIGH);
          delay(800);
          digitalWrite(PINO_LED, LOW);
          return;
        }
        if (digitalRead(PINO_PUSH_BUTTON) == HIGH) {
          Serial.println("LEITURA INTERROMPIDA\n");
          digitalWrite(PINO_LED, LOW);
          return;
        }
      }
    }
  }
}
