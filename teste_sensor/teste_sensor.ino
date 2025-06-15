// Definição dos pinos
#define PINO_SENSOR A1
#define PINO_PUSH_BUTTON 2
#define PINO_LED 3

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
  // Lê o valor do sensor no pino analógico
  int valorSensor = analogRead(PINO_SENSOR);

  // Exibe o valor no monitor serial
  Serial.println(valorSensor);

  // Aguarda 10ms antes da próxima leitura
  delay(10);
}