#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_SHTC3.h>
#include <Servo.h>
#include <Adafruit_NeoPixel.h>

// --- Définitions des pins ---
#define PIR_PIN 5        // Capteur PIR sur D5
#define SERVO_PIN 8      // Servo moteur sur D8

// --- OLED ---
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Adafruit_SHTC3 shtc3 = Adafruit_SHTC3();

// --- Servo ---
Servo monServo;
int angle = 0;
bool porteOuverte = false;

const unsigned char dropBitmap[] PROGMEM = {
  0b00010000,
  0b00111000,
  0b01111100,
  0b01111100,
  0b01111100,
  0b00111000,
  0b00010000,
  0b00000000
};

void setup() {
  Serial.begin(9600);

  // Initialisation des pins
  pinMode(PIR_PIN, INPUT);

  // Initialisation servo
  monServo.attach(SERVO_PIN);
  monServo.write(angle);  // Porte fermée au départ

  // Initialisation OLED
  Wire.begin();
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("Erreur d'initialisation OLED"));
    while (1);
  }
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  // Initialisation capteur SHTC3
  if (!shtc3.begin()) {
    display.clearDisplay();
    display.setCursor(0, 20);
    display.println(F("Erreur capteur SHTC3"));
    display.display();
    while (1);
  }
}

void loop() {
  // Lecture température et humidité
  sensors_event_t humidity, temp;
  if (shtc3.getEvent(&humidity, &temp)) {
    float tempC = temp.temperature;
    float hum = humidity.relative_humidity;

    display.clearDisplay();
    display.drawRect(2, 2, SCREEN_WIDTH - 4, SCREEN_HEIGHT - 4, SSD1306_WHITE);

    display.setTextSize(2);
    display.setCursor(29, 22);
    display.print(tempC, 1);
    display.print((char)247); // symbole °
    display.print("C");

    display.setTextSize(1);
    display.setCursor(30, 6);
    display.print(F("Temperature"));

    display.drawBitmap(18, SCREEN_HEIGHT - 13, dropBitmap, 6, 8, SSD1306_WHITE);

    display.setCursor(30, SCREEN_HEIGHT - 12);
    display.print(hum, 0);
    display.print("%");

    display.display();
  }

  // Lecture capteur PIR
  int detection = digitalRead(PIR_PIN);

  if (detection == HIGH) {
    if (!porteOuverte) {
      Serial.println("Presence detectee → Ouverture de la porte...");
      for (angle = 0; angle <= 90; angle++) {
        monServo.write(angle);
        delay(15);
      }
      porteOuverte = true;
    }
  } else {
    if (porteOuverte) {
      Serial.println("Absence → Fermeture de la porte...");
      for (angle = 90; angle >= 0; angle--) {
        monServo.write(angle);
        delay(15);
      }
      porteOuverte = false;
    }
  }

  delay(100);
}
