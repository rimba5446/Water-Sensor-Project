#include <LiquidCrystal.h>
#define THRESHOLD   300
#define LED_PIN 13
#define POWER_PIN  7
#define SIGNAL_PIN A5
#define SENSOR_MIN 0
#define SENSOR_MAX 521
#define BUZZER_PIN 10
// lcd
#define PIN_RS 12
#define PIN_E 11
#define PIN_D4 4
#define PIN_D5 6
#define PIN_D6 2
#define PIN_D7 8
// 
int value = 0; // variable to store the sensor value
int level = 0; // variable to store the water level

LiquidCrystal lcd(PIN_RS, PIN_E, PIN_D4, PIN_D5, PIN_D6, PIN_D7);

void setup() {
  lcd.begin(16,2);
  Serial.begin(9600);
  pinMode(BUZZER_PIN, OUTPUT); //configure pin 10 as an OUTPUT Buzzer
  pinMode(POWER_PIN, OUTPUT);   // configure D7 pin as an OUTPUT
  digitalWrite(POWER_PIN, LOW); // turn the sensor OFF
  digitalWrite(LED_PIN,   LOW); // turn LED OFF
}

void loop() {
  lcd.clear();
  digitalWrite(POWER_PIN, HIGH);  // turn the sensor ON
  delay(10);                      // wait 10 milliseconds
  value = analogRead(SIGNAL_PIN); // read the analog value from sensor
  digitalWrite(POWER_PIN, LOW);   // turn the sensor OFF

  level = map(value, SENSOR_MIN, SENSOR_MAX, 0, 5); // 5 levels
  lcd.print("Water level: ");
  lcd.println(level);
  if (value > THRESHOLD) {
    lcd.setCursor(0,1);
    lcd.print("WaterSensor: ON");
    digitalWrite(BUZZER_PIN, HIGH); // turn BUZZER ON
    delay(1000);
    digitalWrite(BUZZER_PIN, LOW); // turn BUZZER OFF
    delay(1000);
    digitalWrite(LED_PIN, HIGH);  // turn LED ON
    delay(1000);
    digitalWrite(LED_PIN, LOW);   // turn LED OFF
    delay(1000);
  } else {
    lcd.setCursor(0,1);
    lcd.print("WaterSensor: OFF");
    digitalWrite(LED_PIN, LOW);   // turn LED OFF
  }

  delay(1000);
}
