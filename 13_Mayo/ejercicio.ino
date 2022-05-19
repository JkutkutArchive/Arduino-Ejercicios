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
  float adcValue = analogRead(pinHumedad); // Read voltage coming from sensor (adcValue will be between 0-1023)
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
  // Puesto que empieza por los lados, tenemos que borrar el mensaje anterior y empezar de 0.
  lcd.clear();
}


#define TEMP_STR "Temp: XX.XX C"
#define HUM_STR  "RH  : XX.XX %%"
#define DATA_LEN (sizeof(TEMP_STR) - 1)
#define DATA_OFFSET 5

void updateData(int data, char **dataString) {
  int tmpInt1 = data;
  float tmpFrac = data - tmpInt1;
  int tmpInt2;
  if (data < -9)
    tmpInt2 = trunc(tmpFrac * 10);
  else
    tmpInt2 = trunc(tmpFrac * 100);

  if (tmpInt2 < 0)
    tmpInt2 *= -1;

  sprintf((*dataString) + 6, "%d.%d", tmpInt1, tmpInt2);
  (*dataString)[11] = ' ';
}

void printIndex() {
  static int index = -DATA_LEN;
  static int index2 = 16;
  static char *text[] = {0, 0};

  if (!text[0]) {
    text[0] = (char *) malloc(sizeof(TEMP_STR));
    text[1] = (char *) malloc(sizeof(HUM_STR));
    sprintf(text[0], TEMP_STR);
    sprintf(text[1], HUM_STR);
  }

  float temp = getTemperatura();
  int tmpInt1 = temp;
  float tmpFrac = temp - tmpInt1;
  int tmpInt2;
  if (temp < -9)
    tmpInt2 = trunc(tmpFrac * 10);
  else
    tmpInt2 = trunc(tmpFrac * 100);

  if (tmpInt2 < 0)
    tmpInt2 *= -1;

  sprintf(text[0] + 6, "%d.%d", tmpInt1, tmpInt2);
  text[0][11] = ' ';


  float rh = getRH();
  tmpInt1 = rh;
  tmpFrac = rh - tmpInt1;
  if (temp < -9)
    tmpInt2 = trunc(tmpFrac * 10);
  else
    tmpInt2 = trunc(tmpFrac * 100);
  if (tmpInt2 < 0)
    tmpInt2 *= -1;
  sprintf(text[1] + 6, "%d.%d", tmpInt1, tmpInt2);
  text[1][11] = ' ';

  // updateData(getTemperatura(), &(text[0]));
  // updateData(getRH(), &(text[1]));

  lcd.setCursor(0, 0);
  if (index < 0) {
    lcd.print(text[0] - index);
  } else {
    for (int i = 0; i < index; i++) {
      lcd.print(" ");
    }
    lcd.print(text[0]);
  }

  // humidity
  lcd.setCursor(0, 1);
  if (index2 >= 0) {
    for (int i = 0; i < index2; i++) {
      lcd.print(" ");
    }
    lcd.print(text[1]);
    for (int i = index2 + DATA_LEN; i <= 16; i++) {
      lcd.print(" ");
    }
  } else {
    lcd.print(text[1] - index2);
    for (int i = DATA_LEN; i <= 16; i++) {
      lcd.print(" ");
    }
  }

  index++;
  if (index > 16)
    index = -DATA_LEN;
  index2--;
  if (index2 < -10)
    index2 = 16;
}

void loop() {
  printIndex();
  delay(100);
}
 