#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Adafruit_GFX.h>


#define DHTPIN 4
#define DHTTYPE DHT11

#define RED_LED_PIN 2
#define GREEN_LED_PIN 23
#define BUTTON1_PIN 15
#define BUTTON2_PIN 18
#define RELAY5V_PIN 5
#define RELAY12V_PIN 19
#define FAN_PIN 19
#define MOTOR_PIN 5

#define VOLTAGE_SENSOR1_PIN 36 // VP
#define VOLTAGE_SENSOR2_PIN 39 // VN
#define CURRENT_SENSOR1_PIN 34
#define CURRENT_SENSOR2_PIN 35

DHT dht(DHTPIN, DHTTYPE);
Adafruit_SSD1306 display(128, 64, &Wire, -1);

void setup() {
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(BUTTON1_PIN, INPUT_PULLUP);
  pinMode(BUTTON2_PIN, INPUT_PULLUP);
  pinMode(RELAY5V_PIN, OUTPUT);
  pinMode(RELAY12V_PIN, OUTPUT);
  pinMode(FAN_PIN, OUTPUT);
  pinMode(MOTOR_PIN, OUTPUT);

  digitalWrite(RED_LED_PIN, HIGH);
  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(RELAY5V_PIN, LOW);
  digitalWrite(RELAY12V_PIN, LOW);
  digitalWrite(FAN_PIN, LOW);
  digitalWrite(MOTOR_PIN, LOW);

  dht.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  delay(2000);
  display.clearDisplay();
}

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  float voltage1 = analogRead(VOLTAGE_SENSOR1_PIN) * (3.3 / 4095.0) * 5.0;
  float voltage2 = analogRead(VOLTAGE_SENSOR2_PIN) * (3.3 / 4095.0) * 5.0;
  float current1 = analogRead(CURRENT_SENSOR1_PIN) * (3.3 / 4095.0) * 5.0;
  float current2 = analogRead(CURRENT_SENSOR2_PIN) * (3.3 / 4095.0) * 5.0;

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  if (temperature > 40) {
    digitalWrite(FAN_PIN, HIGH);
  } else {
    digitalWrite(FAN_PIN, LOW);
  }

  if (digitalRead(BUTTON1_PIN) == LOW) {
    digitalWrite(GREEN_LED_PIN, HIGH);
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(MOTOR_PIN, HIGH);
  }

  if (digitalRead(BUTTON2_PIN) == LOW) {
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(RED_LED_PIN, HIGH);
    digitalWrite(MOTOR_PIN, LOW);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("Temp: ");
  display.print(temperature);
  display.print(" C");
  display.setCursor(0, 10);
  display.print("Humidity: ");
  display.print(humidity);
  display.print(" %");
  display.setCursor(0, 20);
  display.print("Voltage1: ");
  display.print(voltage1);
  display.print(" V");
  display.setCursor(0, 30);
  display.print("Voltage2: ");
  display.print(voltage2);
  display.print(" V");
  display.setCursor(0, 40);
  display.print("Current1: ");
  display.print(current1);
  display.print(" A");
  display.setCursor(0, 50);
  display.print("Current2: ");
  display.print(current2);
  display.print(" A");
  display.display();

  delay(2000);
}
