#include <Wire.h>                 // Communication I2C (pour OLED et capteur SHTC3)
#include <Adafruit_SSD1306.h>     // Bibliothèque pour écran OLED SSD1306
#include <Adafruit_SHTC3.h>       // Bibliothèque pour capteur température/humidité SHTC3
#include <Servo.h>                // Bibliothèque pour contrôler le servo-moteur

// --- Définitions des pins ---
#define PIR_PIN 5        // Pin connectée au capteur de présence PIR (entrée digitale)
#define SERVO_PIN 8      // Pin connectée au servo moteur

// --- Configuration écran OLED ---
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1    // Pas de pin reset utilisé

// Création de l'objet écran OLED
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Création de l'objet capteur température/humidité
Adafruit_SHTC3 shtc3 = Adafruit_SHTC3();

// --- Servo ---
Servo monServo;        // Création de l'objet servo
int angle = 0;         // Angle initial du servo (0 = porte fermée)
bool porteOuverte = false;  // État de la porte (fermée au départ)

// --- Bitmap goutte d’eau pour affichage OLED ---
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
  Serial.begin(9600);       // Démarrage du port série pour debug

  pinMode(PIR_PIN, INPUT);  // Configure le pin PIR en entrée

  monServo.attach(SERVO_PIN); // Attache le servo au pin défini
  monServo.write(angle);       // Position initiale du servo (porte fermée)

  Wire.begin();               // Démarrage de la communication I2C

  // Initialisation de l'écran OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {  
    Serial.println(F("Erreur d'initialisation OLED"));
    while (1);  // Bloque si erreur OLED
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  // Initialisation du capteur SHTC3
  if (!shtc3.begin()) {
    display.clearDisplay();
    display.setCursor(0, 20);
    display.println(F("Erreur capteur SHTC3"));
    display.display();
    while (1);  // Bloque si erreur capteur
  }
}

void loop() {
  // Lecture de la température et de l'humidité avec le capteur SHTC3
  sensors_event_t humidity, temp;
  if (shtc3.getEvent(&humidity, &temp)) {
    float tempC = temp.temperature;            // Température en °C
    float hum = humidity.relative_humidity;    // Humidité relative en %

    // Affichage sur l'écran OLED
    display.clearDisplay();
    display.drawRect(2, 2, SCREEN_WIDTH - 4, SCREEN_HEIGHT - 4, SSD1306_WHITE); // Cadre

    display.setTextSize(2);
    display.setCursor(29, 22);
    display.print(tempC, 1);   // Affiche la température avec 1 décimale
    display.print((char)247);  // Affiche le symbole degré °
    display.print("C");

    display.setTextSize(1);
    display.setCursor(30, 6);
    display.print(F("Temperature"));

    // Affiche la petite goutte d'eau pour symboliser l'humidité
    display.drawBitmap(18, SCREEN_HEIGHT - 13, dropBitmap, 6, 8, SSD1306_WHITE);

    // Affiche le pourcentage d'humidité
    display.setCursor(30, SCREEN_HEIGHT - 12);
    display.print(hum, 0);  // Affiche l’humidité sans décimale
    display.print("%");

    display.display();
  }

  // Lecture du capteur PIR (détection de présence)
  int detection = digitalRead(PIR_PIN);

  // Si présence détectée et porte fermée → ouverture progressive
  if (detection == HIGH) {
    if (!porteOuverte) {
      Serial.println("Presence detectee → Ouverture de la porte...");
      for (angle = 0; angle <= 90; angle++) {
        monServo.write(angle);  // Ouvre la porte progressivement jusqu'à 90°
        delay(15);
      }
      porteOuverte = true; // Met à jour l'état de la porte
    }
  } 
  // Si absence détectée et porte ouverte → fermeture progressive
  else {
    if (porteOuverte) {
      Serial.println("Absence → Fermeture de la porte...");
      for (angle = 90; angle >= 0; angle--) {
        monServo.write(angle);  // Ferme la porte progressivement jusqu'à 0°
        delay(15);
      }
      porteOuverte = false; // Met à jour l'état de la porte
    }
  }

  delay(100);  // Petite pause pour limiter la vitesse de la boucle
}
