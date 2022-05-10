#define S_RED 7
#define S_YELLOW 6
#define S_GREEN 5

#define P_RED 9
#define P_GREEN 8

#define S_DELAY 5000
#define S_AMBAR_DELAY 800

#define P_BLINKS 3
#define P_BLINK_START 2000

int t;

void setup()
{
  pinMode(S_RED, OUTPUT);
  pinMode(S_YELLOW, OUTPUT);
  pinMode(S_GREEN, OUTPUT);

  pinMode(P_RED, OUTPUT);
  pinMode(P_GREEN, OUTPUT);
}

void loop()
{
	digitalWrite(S_RED, HIGH);
	digitalWrite(P_RED, LOW);
	digitalWrite(P_GREEN, HIGH);

	delay(P_BLINK_START);
	t = 0;
	while(t++ <= P_BLINKS) {
		digitalWrite(P_GREEN, HIGH);
		delay((S_DELAY - P_BLINK_START) / (P_BLINKS * 2));
		digitalWrite(P_GREEN, LOW);
		delay((S_DELAY - P_BLINK_START) / (P_BLINKS * 2));
	}
	digitalWrite(P_RED, HIGH);


	digitalWrite(S_RED, LOW);
	digitalWrite(S_GREEN, HIGH);

	delay(S_DELAY);

	digitalWrite(S_GREEN, LOW);
	digitalWrite(S_YELLOW, HIGH);

	delay(S_AMBAR_DELAY);

	digitalWrite(S_YELLOW, LOW);
}