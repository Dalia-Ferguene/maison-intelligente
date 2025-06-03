#include <FastLED.h>

#define LED_PIN     4
#define NUM_LEDS    141
#define BRIGHTNESS  120
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB

CRGB leds[NUM_LEDS];

// Couleurs dynamiques pour la zone 1
CRGB couleurs[] = {
  CHSV(200, 255, 80),   // Violet foncé
  CHSV(210, 180, 120),  // Mauve
  CHSV(0, 255, 180),    // Rouge
  CHSV(330, 100, 255),  // Rose
  CHSV(25, 255, 220),   // Orange
  CHSV(96, 255, 220),   // Vert
  CHSV(128, 180, 240),  // Bleu turquoise
  CHSV(160, 100, 255)   // Bleu clair
};

const int NB_COULEURS = sizeof(couleurs) / sizeof(couleurs[0]);

int couleurIndex = 0;
unsigned long dernierChangement = 0;
const unsigned long intervalle = 2000;

void setup() {
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);

  // Initialisation des zones statiques
  setZone2WhiteFade();
  setZone3Mauve();

  // Initialisation de la zone 1
  setZone1Color(couleurs[couleurIndex]);

  FastLED.show();
}

void loop() {
  unsigned long maintenant = millis();

  if (maintenant - dernierChangement >= intervalle) {
    int prochainIndex = (couleurIndex + 1) % NB_COULEURS;
    fonduZone1(couleurs[couleurIndex], couleurs[prochainIndex]);
    couleurIndex = prochainIndex;
    dernierChangement = maintenant;
  }
}

// Appliquer une couleur à la zone 1 (0 à 79)
void setZone1Color(CRGB couleur) {
  for (int i = 0; i < 83; i++) {
    leds[i] = couleur;
  }
}

// Zone 2 (80 à 119) : blanc fade
void setZone2WhiteFade() {
  for (int i = 83; i < 130; i++) {
    leds[i] = CRGB(60, 60, 60);  // Blanc doux
  }
}

// Zone 3 (120 à 140) : mauve fixe
void setZone3Mauve() {
  for (int i = 130; i < NUM_LEDS; i++) {
    leds[i] = CHSV(210, 180, 120);  // Mauve
  }
}

// Fondu uniquement pour zone 1
void fonduZone1(CRGB couleurDepart, CRGB couleurArrivee) {
  const int etapes = 50;
  for (int e = 0; e <= etapes; e++) {
    for (int i = 0; i < 83; i++) {
      leds[i] = blend(couleurDepart, couleurArrivee, (255 * e) / etapes);
    }

    // Réappliquer les zones statiques
    setZone2WhiteFade();
    setZone3Mauve();

    FastLED.show();
    delay(20);
  }
}
