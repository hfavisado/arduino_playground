#define CYCLE_MS 500
#define MAX_DUTY_CYCLE 100
#define MIN_DUTY_CYCLE 2

bool breatheIn = false;
int dutyCyclePercent = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  Serial.println("Initialized\n");
}

void loop()
{
  digitalWrite(LED_BUILTIN, HIGH);
  calculateDelay(false);
  digitalWrite(LED_BUILTIN, LOW);
  calculateDelay(true);
}

void calculateDelay(bool isLEDon)
{
  if (!breatheIn && (--dutyCyclePercent < MIN_DUTY_CYCLE))
  {
    dutyCyclePercent = MIN_DUTY_CYCLE;
    breatheIn = true;
  }
  else if (breatheIn && (++dutyCyclePercent > MAX_DUTY_CYCLE))
  {
    dutyCyclePercent = MAX_DUTY_CYCLE;
    breatheIn = false;
  }
  delayLoop(breatheIn, isLEDon);
}

void delayLoop(bool isBreatheIn, bool isLEDon)
{
  int calculatedDelay = 0;
  int divisor = 0;

  Serial.println(dutyCyclePercent);
  if (isLEDon)
  {
    divisor = dutyCyclePercent;
    calculatedDelay = CYCLE_MS / dutyCyclePercent;
  }
  else
  {
    divisor = MAX_DUTY_CYCLE - dutyCyclePercent;
    if (divisor < 1)
      divisor = 1;
    calculatedDelay = CYCLE_MS / (MAX_DUTY_CYCLE - dutyCyclePercent);
    if (calculatedDelay < 1)
      calculatedDelay = 1;
  }
  Serial.print(dutyCyclePercent);
  Serial.print(" ");
  Serial.println(calculatedDelay);
  delay(calculatedDelay);
}
