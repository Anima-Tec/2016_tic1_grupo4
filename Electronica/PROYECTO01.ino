int ldr = A0;
int led = 11;
int estado = 0;
int objetivo = 0;
int voltaje = 0;
int lectura = 0;
int valorSalida = 0;
int lecturaAnterior = 0;
int errorAcumulado = 0;
int correccion = 0;
int KP = 0.1;
int KI = 0.01;
int KD = 0.005;
int tiempo = 500;
void setup()
{
  Serial.begin(9600);
  pinMode(led, OUTPUT);
}
void loop()
{
  char c = Serial.read();
  if (c == 'a') {
    estado = 1;
    objetivo = Serial.parseInt();
    Serial.println("a");
  }
  if (c == 'm') {
    Serial.println("m");
    estado = 0;
    voltaje = Serial.parseInt();
  }

  if (estado == 1) {
    Serial.println("estoy en automatico");
    lectura = analogRead(ldr);
    int diferencia = objetivo-lectura;
    errorAcumulado = diferencia+errorAcumulado;
    int cambio = lectura-lecturaAnterior;
    correccion = KP*diferencia+KI*errorAcumulado+KD*cambio;
    voltaje = voltaje-correccion;
    analogWrite(led,voltaje);
    lecturaAnterior = lectura;
    delay(tiempo);
  }
  if (estado == 0) {
    Serial.println("estoy en manual");
    Serial.print(voltaje);
    analogWrite(led,voltaje);
  }
}

