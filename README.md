# 🚗 Dash Mini Retro V1

**Tableau de bord numérique pour Austin Mini (1993 – moteur HIF38)**  
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

## 🧩 Organisation du projet

Dash_Mini_Retro_V1/
│
├── README.md
├── platformio.ini
│
├── src/
│ ├── main.ino
│ ├── page_classic.ino
│ ├── page_racing.ino
│ ├── page_gps.ino
│ ├── page_settings.ino
│ └── wifi_upload.ino
│
├── include/
│ └── config.h
│
├── lib/
│ └── TFT_eSPI/
│ └── User_Setup.h
│
├── data/
│ ├── mini_logo.bmp
│ ├── page_bg.bmp
│ └── gps_map_tiles/
│
├── 3D_models/
│ ├── screen_mount.stl
│ ├── esp32_box.stl
│ └── led_frame.stl
│
├── docs/
│ ├── wiring_diagram.png
│ ├── pinout_table.pdf
│ └── Dash_Mini_Retro_V1_Guide.pdf
│
└── assets/
├── preview_dashboard.jpg
└── mini_logo_preview.png

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
