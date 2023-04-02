#include <Arduino.h>
#include <Ultrasonic.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(7,6,5,4,3,2);


Ultrasonic ultrasonic(11, 12); // Trigger na porta 11 e Echo na porta 12

//Declarando os LED como constantes em seus respectivos pinos
#define ledvermelho 9
#define ledVerde 10

//Declarando buzzer
#define buzzer 8

long microsec = 0; // variaveis de controle
float distanciacm = 0;

void setup() {
  Serial.begin(9600); //Inicializando o serial monitor
  pinMode(ledvermelho, OUTPUT);
  pinMode(ledVerde, OUTPUT);
  lcd.begin(16, 2);
  lcd.clear();
}

void loop() {

      microsec = ultrasonic.timing();

       //Convertendo a distância em CM
      distanciacm = ultrasonic.convert(microsec, Ultrasonic::CM);

      Serial.print("DISTÂNCIA-> ");
      Serial.print(distanciacm);// mostrar a distancia na porta serial
      Serial.println(" cm");// colocar unidade de medida
      ledDistancia();
      alerDist();
      lcdPrint();
      musicBuzzer();

}

void ledDistancia() {

  //Desliga todos os LEDs
  digitalWrite(ledvermelho, LOW);
  digitalWrite(ledVerde, LOW);

  // criando as condicoes se a distancia for entre 30 cm e 20 cm
  if (distanciacm >= 50) {
    digitalWrite(ledVerde, HIGH); //liga o LED verde
  }
  if (distanciacm < 50 and distanciacm >= 30) {
    digitalWrite(ledvermelho, HIGH); //liga o LED vermelho
    delay(400);
    digitalWrite(ledvermelho, LOW); //desliga o LED vermelho
    delay(400);
  }
  if (distanciacm < 30 and distanciacm >= 15) {
    digitalWrite(ledvermelho, HIGH);
    delay(200);
    digitalWrite(ledvermelho, LOW);
    delay(200);
  }
  if (distanciacm < 15 and distanciacm >= 5) {
    digitalWrite(ledvermelho, HIGH);
    delay(90);
    digitalWrite(ledvermelho, LOW);
    delay(90);   
  }
  if (distanciacm < 5 and distanciacm >= 0) {
    digitalWrite(ledvermelho, HIGH);
    delay(20);
    digitalWrite(ledvermelho, LOW);
    delay(20);
  }
} 

void alerDist(){
  if (distanciacm >= 50) {
    Serial.println("DISTANCIA SEGURA");
    delay(500);

    lcd.setCursor(5, 0);
    lcd.print(distanciacm);

    lcd.setCursor(0, 1);
    lcd.print("DISTANCIA SEGURA");
  }

  if (distanciacm < 50 and distanciacm >= 30) {
    Serial.println("FIQUE ATENTO!");


    lcd.setCursor(5, 0);
    lcd.print(distanciacm);

    lcd.setCursor(0, 1);
    lcd.print("  FIQUE ATENTO! ");
  }
  if (distanciacm < 30 and distanciacm >= 15) {
    Serial.println("CUIDADO! MENOS DE 30CM");

    lcd.setCursor(5, 0);
    lcd.print(distanciacm);

    lcd.setCursor(0, 1);
    lcd.print(" CUIDADO! < 30cm");
  }
  if (distanciacm < 15 and distanciacm >= 5) {
    Serial.println("ALERTA! LIMITE RECOMENDADO ATINGIDO");

    lcd.setCursor(5, 0);
    lcd.print(distanciacm);

    lcd.setCursor(0, 1);
    lcd.print("LIMITE ATINGIDO!");
  }
  if (distanciacm < 5 and distanciacm >= 0) {
    Serial.println("VAI BATER, PORR*!!!!!");

    lcd.setCursor(5, 0);
    lcd.print(distanciacm);

    lcd.setCursor(0, 1);
    lcd.print(" VAI BATER PORRA!");
  }
}

void lcdPrint(){
  if (distanciacm >= 50) {
    delay(300);

    lcd.setCursor(5, 0);
    lcd.print(distanciacm);

    lcd.setCursor(0, 1);
    lcd.print("DISTANCIA SEGURA");
  }

  if (distanciacm < 50 and distanciacm >= 30) {

    lcd.setCursor(5, 0);
    lcd.print(distanciacm);

    lcd.setCursor(0, 1);
    lcd.print("  FIQUE ATENTO! ");
  }
  if (distanciacm < 30 and distanciacm >= 15) {

    lcd.setCursor(5, 0);
    lcd.print(distanciacm);

    lcd.setCursor(0, 1);
    lcd.print(" CUIDADO! < 30cm");
  }
  if (distanciacm < 15 and distanciacm >= 5) {

    lcd.setCursor(5, 0);
    lcd.print(distanciacm);

    lcd.setCursor(0, 1);
    lcd.print("LIMITE ATINGIDO!");
  }
  if (distanciacm < 5 and distanciacm >= 0) {

    lcd.setCursor(5, 0);
    lcd.print(distanciacm);

    lcd.setCursor(0, 1);
    lcd.print(" VAI BATER PORRA!");
  }
}

void musicBuzzer(){
  if (distanciacm >= 50) {
    tone(buzzer, 900);
    delay(150);
    noTone(buzzer);
    delay(200);
  }

  if (distanciacm < 50 and distanciacm >= 30) {
    tone(buzzer, 900);
    delay(100);
    noTone(buzzer);
    delay(200);
  }
  if (distanciacm < 30 and distanciacm >= 15) {

    tone(buzzer, 900);
    delay(90);
    noTone(buzzer);
    delay(110);

  }
  if (distanciacm < 15 and distanciacm >= 5) {
    tone(buzzer, 900);
    delay(35);
    noTone(buzzer);
    delay(55);

  }
  if (distanciacm < 5 and distanciacm >= 0) {
    tone(buzzer, 800);
    delay(300);
    tone(buzzer, 400);
    delay(300);

  }
}

