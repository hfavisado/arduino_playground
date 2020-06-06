/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Blink
*/

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
  //  Serial.println(dutyCyclePercent);
  //  Serial.print("delay: ");
  // Serial.println(calculatedDelay);
  // delay(100);
  delay(calculatedDelay);
}
