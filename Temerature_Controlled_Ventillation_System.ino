#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// DHT11 Sensor
#define DHTPIN 2
#define DHTTYPE DHT11

// LED Pins
#define RED_LED 8
#define YELLOW_LED 9
#define GREEN_LED 10

DHT dht(DHTPIN, DHTTYPE);

// LCD Address
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {

  Serial.begin(9600);

  dht.begin();

  lcd.init();
  lcd.backlight();

  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

  digitalWrite(RED_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(GREEN_LED, LOW);

  lcd.setCursor(0, 0);
  lcd.print("TEMP CONTROLLED");

  lcd.setCursor(0, 1);
  lcd.print("VENTILATION SYS");

  delay(2000);

  lcd.clear();
}

void loop() {

  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(temperature) || isnan(humidity)) {

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Sensor Error!");

    digitalWrite(RED_LED, LOW);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(GREEN_LED, LOW);

    delay(2000);
    return;
  }

  // Display Temperature
  lcd.setCursor(0, 0);
  lcd.print("Temp:");
  lcd.print(temperature, 1);
  lcd.print((char)223);
  lcd.print("C   ");

  // HIGH TEMPERATURE - RED LED
  if (temperature >= 35) {

    digitalWrite(RED_LED, HIGH);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(GREEN_LED, LOW);

    lcd.setCursor(0, 1);
    lcd.print("Status: HIGH    ");

    Serial.println("HIGH TEMPERATURE");
  }

  // MEDIUM TEMPERATURE - YELLOW LED
  else if (temperature >= 25) {

    digitalWrite(RED_LED, LOW);
    digitalWrite(YELLOW_LED, HIGH);
    digitalWrite(GREEN_LED, LOW);

    lcd.setCursor(0, 1);
    lcd.print("Status: MEDIUM  ");

    Serial.println("MEDIUM TEMPERATURE");
  }

  // NORMAL TEMPERATURE - GREEN LED
  else {

    digitalWrite(RED_LED, LOW);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);

    lcd.setCursor(0, 1);
    lcd.print("Status: NORMAL  ");

    Serial.println("NORMAL TEMPERATURE");
  }

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  delay(2000);
}
