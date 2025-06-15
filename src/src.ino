#include <Arduino.h>

// Definição dos pinos
const int PINO_SENSOR = A1;
const int PINO_PUSH_BUTTON = 2;
const int PINO_LED = 3;

// Variáveis globais
unsigned long tempo_inicio_leitura;
int sensor_threshold = 0; // Será definido na calibração

void setup() {
  // Configuração dos pinos
  pinMode(PINO_SENSOR, INPUT);
  pinMode(PINO_PUSH_BUTTON, INPUT);
  pinMode(PINO_LED, OUTPUT);
  digitalWrite(PINO_LED, LOW);

  // Inicializa comunicação serial
  Serial.begin(19200);
  while (!Serial) {}

  // Executa a calibração do sensor
  calibrateSensor();

  // Exibe instruções após calibração
  printInstructions();
}

void printInstructions() {
  Serial.println("===================== INSTRUÇÕES =====================");
  Serial.println("- Pressione o botão para iniciar a leitura.");
  Serial.println("- O LED irá piscar por 5s com brilho baixo.");
  Serial.println("- Após, o LED ficará com brilho alto.");
  Serial.println("- Solte o objeto quando o LED estiver com brilho alto.");
  Serial.println("- O LED se apagará quando o objeto for detectado.");
  Serial.println("=======================================================  ");
}

bool isButtonPressed() {
  static unsigned long lastDebounceTime = 0;
  const unsigned long debounceDelay = 50;
  if (digitalRead(PINO_PUSH_BUTTON) == HIGH) {
    unsigned long currentTime = millis();
    if (currentTime - lastDebounceTime > debounceDelay) {
      lastDebounceTime = currentTime;
      return true;
    }
  }
  return false;
}

void calibrateSensor() {
  // Passo 1: LED aceso por 4s para indicar início da calibração
  Serial.println("CALIBRAÇÃO INICIADA");
  Serial.println("Pressione o botão em 4 segundos para capturar o valor mínimo.");
  digitalWrite(PINO_LED, HIGH);
  delay(4000);
  digitalWrite(PINO_LED, LOW);

  // Passo 2: Captura o menor valor enquanto o botão está pressionado
  Serial.println("Pressione e segure o botão para capturar o valor mínimo.");
  int lowest_value = 1023; // Inicializa com o maior valor possível
  while (!isButtonPressed()) {} // Aguarda o primeiro pressionar
  unsigned long start_time = millis();
  while (digitalRead(PINO_PUSH_BUTTON) == HIGH && millis() - start_time < 4000) {
    int sensor_value = analogRead(PINO_SENSOR);
    if (sensor_value < lowest_value) {
      lowest_value = sensor_value;
    }
    delay(10); // Pequeno delay para evitar leituras excessivas
  }
  Serial.print("Valor mínimo capturado: ");
  Serial.println(lowest_value);

  // Passo 3: LED pisca três vezes
  for (int i = 0; i < 3; i++) {
    digitalWrite(PINO_LED, HIGH);
    delay(300);
    digitalWrite(PINO_LED, LOW);
    delay(300);
  }

  delay(2000);

  // Passo 4: LED aceso até o próximo pressionar
  Serial.println("Pressione o botão novamente para capturar o valor máximo (obstrua o sensor).");
  digitalWrite(PINO_LED, HIGH);
  while (!isButtonPressed()) {} // Aguarda o segundo pressionar

  // Passo 5: Captura o maior valor por 4s com sensor obstruído
  int highest_value = 0; // Inicializa com o menor valor possível
  start_time = millis();
  while (digitalRead(PINO_PUSH_BUTTON) == HIGH && millis() - start_time < 4000) {
    int sensor_value = analogRead(PINO_SENSOR);
    if (sensor_value > highest_value) {
      highest_value = sensor_value;
    }
    delay(10); // Pequeno delay para evi>= tar leituras excessivas
  }
  digitalWrite(PINO_LED, LOW);
  Serial.print("Valor máximo capturado: ");
  Serial.println(highest_value);

  // Define o threshold como maior valor - 10
  sensor_threshold = highest_value - 5;
  Serial.print("Threshold definido: ");
  Serial.println(sensor_threshold);
  Serial.println("CALIBRAÇÃO CONCLUÍDA\n");
  delay(2000);
}

void startMeasurement() {
  // Contagem regressiva de 5s com LED piscando
  for (uint8_t i = 5; i > 0; i--) {
    Serial.print("O LED PARA DE PISCAR EM: ");
    Serial.print(i);
    Serial.println("s");
    digitalWrite(PINO_LED, LOW);
    delay(200);
    analogWrite(PINO_LED, 128);
    delay(800);
  }

  // Inicia leitura
  tempo_inicio_leitura = millis();
  digitalWrite(PINO_LED, HIGH);
  Serial.println("\nSOLTE O OBJETO.");

  // Monitora sensor
  const unsigned long DETECTION_TIMEOUT = 50000; // 10s timeout
  while (true) {
    if (analogRead(PINO_SENSOR) >= sensor_threshold) {
      unsigned long tempo_objeto_detectado = millis() - tempo_inicio_leitura;
      digitalWrite(PINO_LED, LOW);
      Serial.print("OBJETO DETECTADO APOS ");
      Serial.print(tempo_objeto_detectado);
      Serial.println("ms");
      Serial.println("LEITURA FINALIZADA\n\n");
      return;
    }
    if (isButtonPressed()) {
      Serial.println("LEITURA INTERROMPIDA\n\n");
      digitalWrite(PINO_LED, LOW);
      delay(500);
      return;
    }
    if (millis() - tempo_inicio_leitura > DETECTION_TIMEOUT) {
      Serial.println("TIMEOUT: OBJETO NÃO DETECTADO");
      digitalWrite(PINO_LED, LOW);
      return;
    }
  }
}

void loop() {
  if (isButtonPressed()) {
    startMeasurement();
  }
}