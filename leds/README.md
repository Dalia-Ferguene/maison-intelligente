# 🌈 Ruban LED WS2812 – Effets lumineux dynamiques

Ce projet Arduino contrôle un ruban LED WS2812 de 141 LED en le divisant en 3 zones indépendantes avec des effets lumineux différents.

## 🔧 Matériel utilisé

- Carte UCA (RFThings)
- Ruban LED WS2812 (141 LED)
- Alimentation externe 5V
- Bibliothèque [FastLED](https://github.com/FastLED/FastLED)

> Pour l’installer :  
> **Arduino IDE > Croquis > Inclure une bibliothèque > Gérer les bibliothèques > Rechercher "FastLED"**

---


## ⚡ Connexions

| Composant    | Broche Arduino |
|--------------|----------------|
| Ruban LED    | D4             |
| GND Ruban    | GND            |
| 5V Ruban     | 5V externe     |

## 🧠 Structure du code

- `setup()` : initialise les LED et assigne les couleurs aux 3 zones.
- `loop()` : applique un fondu de couleur à la **zone 1** toutes les 2 secondes.
- Fonctions personnalisées :
  - `setZone1Color()` : applique une couleur dynamique à la zone 1.
  - `setZone2WhiteFade()` : applique un blanc doux fixe à la zone 2.
  - `setZone3Mauve()` : applique un mauve fixe à la zone 3.
  - `fonduZone1()` : gère la transition fluide entre deux couleurs dans la zone 1.

## 🟦 Répartition des zones

- **Zone 1 (LED 0 à 82)** : Couleurs dynamiques (violet, mauve, rouge, rose, orange, vert, bleu…).
- **Zone 2 (LED 83 à 129)** : Lumière blanche douce et fixe.
- **Zone 3 (LED 130 à 140)** : Mauve fixe.

## 🎥 Aperçu visuel

Tu peux ajouter une capture GIF ou vidéo pour visualiser le rendu des effets lumineux :

```markdown
![Aperçu LED](./preview.gif)

