#include <Arduino.h>
#include <DHT.h>
#include <DHT_U.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(7,6,5,4,3,2);

#define DHTPIN A0
#define DHTTYPE DHT11

#define Umid 8
#define led 9

#define UR_MAX 60
#define UR_IDEAL 55
#define UR_MIN 50

#define INTERVALO_LEITURA 2000 //Intervalo de leitura do DHT11

float umidade;

int estado = 0; //estado 0 = Ar Ideal / estado -1 = Umidificador ligado / estado 1 = Ar(led) ligado
unsigned long controleLeitura;

DHT_Unified dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);

  pinMode(Umid, OUTPUT);
  pinMode(led, OUTPUT);

  lcd.begin(16, 2);
  lcd.clear();

  dht.begin();
}

void loop() {


  if(millis() - controleLeitura > INTERVALO_LEITURA){

  sensors_event_t event;
  dht.humidity().getEvent(&event);
  umidade = event.relative_humidity;

    if (isnan(umidade)) {
      Serial.println(F("Error reading humidity!"));
    
    }else {

      Serial.print("Umidade= ");
      Serial.print(umidade);
      Serial.println(F("%"));

      //Imprime apenas os valores de Umidade no LCD
      lcd.setCursor(5, 0);
      lcd.print(umidade);


      controleLeitura = millis();
    }
    }

    switch (estado)
    {
      case 0:
        if(umidade < UR_MIN){
          estado = -1;
          digitalWrite(Umid, LOW);
          
          //Imprime o estado do Umidificador no LCD
          lcd.setCursor(0, 1);
          lcd.print("UMIDIFICADOR ON ");

        }else if(umidade > UR_MAX){
          estado = 1;
          digitalWrite(led, HIGH);

          //Imprime o estado do Ar Cond. no LCD
          lcd.setCursor(0, 1);
          lcd.print("  AR-COND. ON   ");
        }
        
      break;

      case -1:
        if(umidade >= UR_IDEAL){
          estado = 0;
          digitalWrite(Umid, HIGH);

          //Imprime o estado do Umidificador no LCD
          lcd.setCursor(0, 1);
          lcd.print("UMIDIFICADOR OFF");
        }
        
      break;

      case 1:
        if(umidade <= UR_IDEAL){
          estado = 0;
          digitalWrite(led, LOW);
          
          //Imprime o estado do Ar Cond. no LCD
          lcd.setCursor(0, 1);
          lcd.print("  AR-COND. OFF  ");          
        }
      break;

    }
    
}