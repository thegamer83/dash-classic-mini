# 🚗 Dash Mini Retro V1

**Tableau de bord numérique pour Austin Mini (1993 – moteur 1300cc carbu HIF38)**  
Basé sur un **ESP32** et un **écran TFT ST7796S 4" (480×320)**, avec un style inspiré des compteurs de voitures de course classiques 🏁

---

## ⚙️ Fonctionnalités principales

- 🧭 4 pages : **Classic / Racing / GPS / Réglages**
- 💡 **Shift-light** 16 LED WS2812B (progressif vert → rouge)
- 📈 Affichage des données :
  - Régime moteur (RPM)
  - Vitesse (via GPS)
  - Température d’eau
  - Niveau d’essence
  - Tension batterie
- 🌙 **Gestion automatique de la luminosité**
- 🌐 **Mise à jour OTA Wi-Fi**  
- 💾 **Support carte SD** (logos, cartes GPS, images personnalisées)
- 🔌 **Connecteur GX16-10** pour un montage propre et démontable
- ⚡ Alimentation 12 V → 5 V via convertisseur buck

---
## 🧠 Pages disponibles

| Page | Nom | Description |
|------|-----|--------------|
| 0 | **Classic** | Style compteur Mini 3 cadrans (RPM / Vitesse / Essence & Temp) |
| 1 | **Racing** | Affichage sport avec shift-light et tension |
| 2 | **Calibration** | Réglages capteurs & LED |
| 3 | **OTA** | Mise à jour Wi-Fi sans câble |

---v

## 💡 Conseils

- Le **5 V VIN** alimente l’écran et les LED via un **buck converter 12→5 V**.  
- Les signaux capteurs analogiques doivent passer par **ponts diviseurs de tension**.  
- Le **rétroéclairage** (GPIO 25) peut être atténué via PWM selon les phares.  
- Les **LED WS2812B** sont toutes sur **le même fil DATA (GPIO 4)**.  
- Les 6 modules **JZK optocoupleurs** sont branchés sur les GPIO listés ci-dessus.

---
## 🖥️ Écran TFT

- **Modèle :** ST7796S SPI  
- **Résolution :** 480 × 320  
- **Orientation :** paysage  
- **Librairie :** [TFT_eSPI](https://github.com/Bodmer/TFT_eSPI)  
- **Fichier de configuration :** `lib/TFT_eSPI/User_Setup.h`

---

## 🔌 Connectique GX16-10

| Broche | Nom | Fonction |
|:------:|:----|:----------|
| 1 | 5V | Alimentation écran |
| 2 | GND | Masse commune |
| 3 | Data LED | Signal WS2812B |
| 4 | RPM | Entrée optocoupleur |
| 5 | Température eau | Sonde analogique |
| 6 | Essence | Sonde analogique |
| 7 | GPS RX | Données GPS (vers ESP32) |
| 8 | GPS TX | Données GPS (depuis ESP32) |
| 9 | Phares | Entrée logique |
| 10 | Clignotants | Entrée logique |

---
---

## 🔧 Connexions principales

| Élément | Signal | GPIO ESP32 | Description |
|----------|---------|-------------|--------------|
| TFT MOSI | MOSI | **23** | Données SPI vers écran |
| TFT SCLK | SCK | **18** | Horloge SPI |
| TFT MISO | MISO | **19** | Lecture SPI |
| TFT CS | CS | **15** | Chip Select TFT |
| TFT DC | DC | **26** | Données / Commandes |
| TFT RST | RST | **27** | Reset de l’écran |
| TFT BL | BL | **25** | Rétroéclairage (PWM phares) |
| LED WS2812B | DATA | **4** | Chaîne de 24 LED (4 gauche, 16 centre, 4 droite) |
| JZK RPM | Signal | **32** | Entrée fréquence moteur |
| JZK huile | Signal | **33** | Voyant pression huile |
| JZK phares | Signal | **34** | Allumage feux |
| JZK pleins phares | Signal | **35** | Allumage plein phare |
| JZK clignotant gauche | Signal | **36** | Clignotant gauche |
| JZK clignotant droit | Signal | **39** | Clignotant droit |
| Sonde température | Analog | **A0 (GPIO36)** | Température eau |
| Sonde essence | Analog | **A3 (GPIO39)** | Niveau carburant |
| Batterie | Analog | **A6 (GPIO34)** | Mesure tension via pont diviseur |
| Encodeur | CLK/DT/SW | **16 / 17 / 5** | Navigation menu |
| Carte SD | MOSI/SCK/MISO/CS | **23/18/19/13** | Fichiers GPS et logos |

---

## 🧰 Matériel recommandé

| Composant | Référence |
|:-----------|:-----------|
| Microcontrôleur | ESP32 DevKit V1 |
| Écran TFT | ST7796S 4.0" 480×320 SPI |
| LED Shift-light | WS2812B (16 LED) |
| Modules d’entrée | 6× optocoupleurs JZK |
| Connecteur principal | GX16-10 |
| GPS | Module NEO-6M avec antenne déportée |
| Alimentation | Convertisseur DC-DC 12 V → 5 V 3 A |
| Boîtier imprimé | Support écran + boîtier ESP32 (PETG conseillé) |

---

## 🧠 Compilation & Téléversement

**Logiciel recommandé :**
- [Visual Studio Code](https://code.visualstudio.com/)
- [PlatformIO](https://platformio.org/)

**Carte cible :**
```ini
[env:esp32dev]
platform = espressif32
board = esp32dev
framework = arduino
monitor_speed = 115200
