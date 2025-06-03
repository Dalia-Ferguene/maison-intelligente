# Code : Servo - Présence - OLED - Température/Humidité 🌡️🚪📺

Ce code combine plusieurs capteurs et actionneurs pour créer un système intelligent de **porte automatique** basée sur la **détection de présence**, avec affichage **OLED** de la température et de l'humidité.

## 🔧 Composants utilisés

- 🔌 **Carte UCA** ( RFThings)
- 🚶 **Capteur de présence PIR** (connecté à D5)
- ⚙️ **Servo moteur** (connecté à D8)
- 🌡️ **Capteur de température/humidité SHTC3** 
- 📺 **Écran OLED 128x64**

---

## ⚙️ Fonctionnement

- 📡 Lorsqu’une **présence est détectée** :
  - Le servo ouvre une porte (rotation de 0° à 90°)
  - Un message est affiché sur le moniteur série

- ⏳ Lorsqu’**aucune présence** n’est détectée :
  - Le servo referme la porte (rotation de 90° à 0°)

- 🌡️ En continu, l’écran OLED affiche :
  - La **température en °C**
  - L’**humidité relative (%)**
  - Un **cadre graphique** + une **goutte d’eau** en icône

---


## 🧠 Bibliothèques nécessaires

- [`Adafruit_SSD1306`](https://github.com/adafruit/Adafruit_SSD1306)
- [`Adafruit_GFX`](https://github.com/adafruit/Adafruit-GFX-Library)
- [`Adafruit_SHTC3`](https://github.com/adafruit/Adafruit_SHTC3)
- `Servo`
- `Wire`

Installe-les via le **Library Manager** de l'IDE Arduino (`Croquis > Inclure une bibliothèque > Gérer les bibliothèques...`).
---

## 🔌 Schéma de câblage (résumé)

| Composant         | Broche carte UCA |
|-------------------|------------------|
| PIR               | D5               |
| Servo             | D8               |
| OLED              | SDA/SCL (I2C)    |
| SHTC3             | SDA/SCL (I2C)    |

---


## 📷 Aperçu visuel

![Aperçu du projet](./preview.gif)

> ![Ouverture de la porte](https://github.com/Dalia-Ferguene/maison-intelligente/blob/main/servo_presence_oled/d%C3%A9monstration/Ouvrir%20la%20porte.gif?raw=true)

> ![Écran OLED](https://github.com/Dalia-Ferguene/maison-intelligente/blob/main/servo_presence_oled/d%C3%A9monstration/%C3%A9cran_oled.jpeg?raw=true)
> ### 🖼️ Affichage OLED

<img src="https://github.com/Dalia-ari/maison-intelligente/blob/main/servo_presence_oled/d%C3%A9monstration/%C3%A9cran_oled.jpeg?raw=true" width="300"/>




---


## 🧪 Idée d'amélioration

- 🔊 Ajouter un **buzzer** pour émettre un signal sonore lors de l'ouverture de la porte.
- 📡 Utiliser **LoRaWAN** pour transmettre les données de température et d’humidité à distance vers un serveur ou une application mobile.
- 🔐 Intégrer un **clavier numérique** (4x4) pour permettre l’entrée d’un **code PIN** afin de déverrouiller manuellement la porte.
