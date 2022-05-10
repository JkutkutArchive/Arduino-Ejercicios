#define LED1 5
#define LED2 6
#define LED3 7

#define A 'a'
#define B 'b'
#define C 'c'

char leer;
int estado;

void accionA() {
    digitalWrite(LED1, HIGH); // Enciende el LED1
    digitalWrite(LED2, HIGH); // Enciende el LED2
    digitalWrite(LED3, HIGH); // Enciende el LED3
}

void accionB() {
    digitalWrite(LED1, HIGH); // Enciende el LED1
    delay (1000);
    digitalWrite(LED1, LOW); // Apaga el LED
    digitalWrite(LED2, HIGH); // Apaga el LED
    delay (1000);
    digitalWrite(LED2, LOW); // Apaga el LED
    digitalWrite(LED3, HIGH); // Enciende el LED3
    delay (1000);
    digitalWrite(LED3, LOW); // Apaga el LED
    digitalWrite(LED1, HIGH); // Enciende el LED1
}

void accionC() {
    digitalWrite(LED1, LOW); // Apaga el LED1
    digitalWrite(LED2, LOW); // Apaga el LED2
    digitalWrite(LED3, LOW); // Apaga el LED3
}

void setup() {
    Serial.begin(9600);

    // Configura los LEDs como salidas digitales.
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);

    estado = C; // Empieza con los LEDs apagados

    Serial.println("Setup inicializado");
}

void loop() {
    switch (estado) { // Se podría usar un if, pero así la lógica está lista para añadir más estados
        case B:
            accionB();
            break;
        // No ejecutamos A ni C ya que sólo los ejecutamos una vez.
        default:
            break;
    }

    if (!Serial.available()) { // Si no hay nada que leer
        delay(90); // Evitar heat up
        return;
    }
    leer = Serial.read(); // Lee el caracter introducido
    if (leer != estado)
        Serial.println("Cambiando al estado: " + String(leer));
    switch (leer) {
        case A:
            accionA();
            break;
        case C:
            accionC();
            break;
        // No hacemos, B. B se realiza en bucle
        default:
            Serial.println("Error, no existe ese estado");
            return; // Ojo, no es break. No queremos que se actualice el estado
    }
    estado = leer; // Actualiza el estado
}
