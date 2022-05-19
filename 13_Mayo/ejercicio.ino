/*

1. En la Farmacia S.A. se requiere instalar un cartel luminoso en la entrada 
que muestre la siguiente información:
	- En la primera fila del display, la temperatura. P.e.: Temp: 10⁰
	- En la segunda fila la humedad relativa. P.e.: HR: 80%
2. Pasados cinco segundos, el comportamiento de la visualización será el siguiente:
	- En la primera fila la información de la temperatura se desplazará de izquierda a derecha
	- En la segunda fila, la información de la humedad se desplazará de derecha a izquierda

*/

#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int pinTemperatura=A0;
// Para el uso de tinkercad, usamos otro de temperatura. El funcionamiento
// es equivalente.
int pinHumedad=A1;

float temperatura;
float rh;

float getTemperatura() {
  return ( analogRead(pinTemperatura) * (500.0 / 1024.0) ) - 50.0;
}

float getRH() {
  float adcValue = analogRead(0); // Read voltage coming from sensor (adcValue will be between 0-1023)
  float voltage = (adcValue/1023.0)*5.0; // Translate ADC value into a voltage value
  float percentRH = (voltage-0.958)/0.0307; // Translate voltage into percent relative humidity
  return percentRH;
}

void setup() {
  Serial.begin(9600); // TODO debug
  lcd.begin(16, 2);

  lcd.setCursor(0,0);
  lcd.print("Temp: ");
  lcd.setCursor(0, 1);
  lcd.print("RH  : ");

  pinMode(pinTemperatura, INPUT);
  pinMode(pinHumedad, INPUT);
  
  lcd.setCursor(6, 0);
  lcd.print(getTemperatura());
  lcd.setCursor(11, 0);
  lcd.print(" C");
  
  lcd.setCursor(6, 1);
  lcd.print(getRH());
  lcd.setCursor(11, 1);
  lcd.print(" %");
  
  // delay(5000);
}


#define TEMP_STR "Temp: XX.XX C"
#define DATA_LEN (sizeof(TEMP_STR) - 1)

#define HUM_STR  "RH  : XX.XX %%"

#define DATA_OFFSET 5
void printIndex() {
  static int index = -DATA_LEN;
  static char *text[] = {0, 0};

  if (!text[0]) {
    text[0] = (char *) malloc(sizeof(TEMP_STR));
    text[1] = (char *) malloc(sizeof(HUM_STR));
    sprintf(text[0], TEMP_STR);
    sprintf(text[1], HUM_STR);
  }

  lcd.setCursor(0, 0);
  if (index < 0) {
    lcd.print(text[0] - index);
  } else {
    for (int i = 0; i < index; i++) {
      lcd.print(" ");
    }
    lcd.print(text[0]);
  }

  // lcd.setCursor(0, 1);
  // if (index >= 0) {
  //   lcd.print(text[1] + index + DATA_LEN);
  // } else {
  //   // for (int i = 0; i < index; i++) {
  //   //   lcd.print(" ");
  //   // }
  //   // lcd.print(text[1]);
  // }

  index++;
  if (index > 16)
    index = -DATA_LEN;
}

void loop() {
  printIndex();
  delay(100);
}
 