#include <FastLED.h>

// --- Définitions des pins et paramètres du ruban LED ---
#define LED_PIN     4         // Pin connectée au ruban LED (D4)
#define NUM_LEDS    141       // Nombre total de LEDs sur le ruban
#define BRIGHTNESS  120       // Luminosité maximale (0 à 255)
#define LED_TYPE    WS2812    // Type de LED WS2812 (NeoPixel)
#define COLOR_ORDER GRB       // Ordre des couleurs (Green, Red, Blue)

CRGB leds[NUM_LEDS];         // Tableau pour stocker l’état de chaque LED

// --- Palette dynamique de couleurs pour la zone 1 ---
CRGB couleurs[] = {
  CHSV(200, 255, 80),   // Violet foncé
  CHSV(210, 180, 120),  // Mauve
  CHSV(0, 255, 180),    // Rouge vif
  CHSV(330, 100, 255),  // Rose
  CHSV(25, 255, 220),   // Orange
  CHSV(96, 255, 220),   // Vert vif
  CHSV(128, 180, 240),  // Bleu turquoise
  CHSV(160, 100, 255)   // Bleu clair
};

const int NB_COULEURS = sizeof(couleurs) / sizeof(couleurs[0]);  // Nombre de couleurs

int couleurIndex = 0;                   // Index couleur actuelle dans la palette
unsigned long dernierChangement = 0;   // Temps du dernier changement de couleur
const unsigned long intervalle = 2000; // Intervalle entre changements (en ms)

void setup() {
  // Initialisation du ruban LED
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);

  // Initialisation des zones statiques :
  setZone2WhiteFade();   // Zone 2 en blanc doux dégradé
  setZone3Mauve();       // Zone 3 en mauve fixe

  // Initialisation de la zone 1 avec la première couleur de la palette
  setZone1Color(couleurs[couleurIndex]);

  FastLED.show();  // Mise à jour du ruban LED avec les couleurs définies
}

void loop() {
  unsigned long maintenant = millis();  // Temps actuel

  // Vérifie si l'intervalle est écoulé pour changer de couleur
  if (maintenant - dernierChangement >= intervalle) {
    int prochainIndex = (couleurIndex + 1) % NB_COULEURS; // Passage à la couleur suivante (boucle)

    // Fondu progressif de la couleur actuelle vers la suivante sur la zone 1
    fonduZone1(couleurs[couleurIndex], couleurs[prochainIndex]);

    couleurIndex = prochainIndex;      // Mise à jour de la couleur courante
    dernierChangement = maintenant;    // Mise à jour du temps du dernier changement
  }
}

// --- Fonctions pour gérer les zones du ruban LED ---

// Appliquer une couleur uniforme à la zone 1 (LEDs 0 à 82)
void setZone1Color(CRGB couleur) {
  for (int i = 0; i < 83; i++) {
    leds[i] = couleur;
  }
}

// Zone 2 (LEDs 83 à 129) : blanc doux fixe (fade)
void setZone2WhiteFade() {
  for (int i = 83; i < 130; i++) {
    leds[i] = CRGB(60, 60, 60);  // Blanc doux, luminosité moyenne
  }
}

// Zone 3 (LEDs 130 à 140) : mauve fixe
void setZone3Mauve() {
  for (int i = 130; i < NUM_LEDS; i++) {
    leds[i] = CHSV(210, 180, 120);  // Mauve, saturation et luminosité modérées
  }
}

// Effectue un fondu progressif entre deux couleurs pour la zone 1
void fonduZone1(CRGB couleurDepart, CRGB couleurArrivee) {
  const int etapes = 50;     // Nombre d’étapes dans le fondu
  for (int e = 0; e <= etapes; e++) {
    for (int i = 0; i < 83; i++) {
      // Calcul de la couleur intermédiaire selon la progression du fondu
      leds[i] = blend(couleurDepart, couleurArrivee, (255 * e) / etapes);
    }

    // Remet à jour les zones statiques pour ne pas les écraser
    setZone2WhiteFade();
    setZone3Mauve();

    FastLED.show();  // Mise à jour du ruban LED
    delay(20);       // Pause pour rendre le fondu visible et fluide
  }
}

