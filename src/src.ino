#include <Arduino.h>

// Definição dos pinos
#define PINO_SENSOR = A1;
#define PINO_PUSH_BUTTON = 2;
#define PINO_LED = 3;

// Declara variaveis para marcação do horario dos sensores
unsigned long tempo_inicio_leitura;
unsigned long tempo_objeto_detectado;

void setup() {
  // Configuração do modo de atuação dos pinos
  pinMode(PINO_SENSOR, INPUT);
  pinMode(PINO_PUSH_BUTTON, INPUT);
  pinMode(PINO_LED, OUTPUT);

  // Configura a taxa de transferência da comunicação Serial
  Serial.begin(115200);

  // Espera até que a comunicação Serial esteja disponível
  while (!Serial) {
  }

  // Envia um sinal LOW para garantir que o LED
  // esteja desligado antes de iniciar a leitura
  digitalWrite(PINO_LED, LOW);
}

void loop() {
  // Instruções para o usuário
Serial.println("===================== INSTRUÇÕES =====================");
Serial.println("- Pressione o botão para iniciar a leitura.");
Serial.println("- O LED irá piscar durante 5 segundos com brilho baixo.");
Serial.println("- Após isso, o LED ficará com brilho alto.");
Serial.println("- Quando o LED estiver com brilho alto, solte o objeto.");
Serial.println("- O LED se apagará quando o objeto for detectado.");
Serial.println("- O tempo de detecção será exibido no monitor serial.");
Serial.println("=======================================================  ");

  // Espera até que o botão seja pressionado
  while (true) {
    if (digitalRead(PINO_PUSH_BUTTON) == HIGH) {
      /* Contagem regressiva de 5 segundos com o LED piscando.
        Itera sobre i 5 vezes e utiliza delay
        para criar um tempo de espera entre cada iteração */
      for (uint8_t i = 5; i > 0; i--) {
        Serial.print("O LED PARA DE PISCAR EM: ");
        Serial.print(i);
        Serial.println("s");

        // Pisca o LED para cada iteração (segundo).
        digitalWrite(PINO_LED, LOW);
        delay(200);
        analogWrite(PINO_LED, 128);

        // Aguarda 800 milissegundos para garantir
        // que cada iteração leve o total de 1000 milissegundos
        delay(800);
      }

      // Registra o tempo de início da leitura
      tempo_inicio_leitura = millis();

      // Envia um sinal HIGH para ligar o LED
      // que indica o inicio da leitura
      digitalWrite(PINO_LED, HIGH);

      Serial.println("\nSOLTE O OBJETO.");

      // Loop para monitorar o sensor
      while (true) {
        if (analogRead(PINO_SENSOR) > 1020) {
          // Calcula o tempo desde o início da leitura até a detecção do objeto
          unsigned long tempo_objeto_detectado = millis() - tempo_inicio_leitura;

          // Envia um sinal LOW para desligar o LED
          // indicando detecção do objeto
          digitalWrite(PINO_LED, LOW);

          // Exibe uma mensagem contendo o tempo de detecção do sensor
          Serial.print("OBJETO DETECTADO APOS ");
          Serial.print(tempo_objeto_detectado);
          Serial.println("ms");
          Serial.println("LEITURA FINALIZADA\n\n");

          // Retorna para iniciar o loop novamente
          return;
        }
        // Verifica se o botão foi pressionado para interromper a leitura
        if (digitalRead(PINO_PUSH_BUTTON) == HIGH) {
          Serial.println("LEITURA INTERROMPIDA\n\n");

          digitalWrite(PINO_LED, LOW);

          // Retorna para iniciar o loop novamente
          delay(500);
          return;
        }
      }
    }
  }
}
