#define S_RED 7
#define S_YELLOW 6
#define S_GREEN 5

#define S_DELAY 1000
#define S_AMBAR_DELAY 500

void setup()
{
  pinMode(S_RED, OUTPUT);
  pinMode(S_YELLOW, OUTPUT);
  pinMode(S_GREEN, OUTPUT);
}

void loop()
{
	digitalWrite(S_RED, HIGH);
	delay(S_DELAY);
	digitalWrite(S_RED, LOW);
	digitalWrite(S_GREEN, HIGH);
	delay(S_DELAY);
	digitalWrite(S_GREEN, LOW);
	digitalWrite(S_YELLOW, HIGH);
	delay(S_AMBAR_DELAY);
	digitalWrite(S_YELLOW, LOW);
}