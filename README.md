# \# 🚗 Dash Mini Retro V1

# \_Tableau de bord numérique ESP32 pour Austin Mini – style racing, minimal et fiable.\_

# 

# !\[Version](https://img.shields.io/badge/version-1.0-blue)

# !\[Platform](https://img.shields.io/badge/platform-ESP32-orange)

# !\[License](https://img.shields.io/badge/license-MIT-green)

# 

# ---

# 

# \## 🧠 Fonctionnalités principales

# 

# \- \*\*ESP32 DevKit V1\*\* + écran \*\*TFT 4" ST7796S\*\*

# \- \*\*Affichages dynamiques\*\* : Classic / Racing / GPS / Menu

# \- \*\*EEPROM persistante\*\* (shift RPM, ratio tension, luminosité)

# \- \*\*WS2812B 24 LED\*\* → shift light + clignotants + état GPS

# \- \*\*Entrées analogiques\*\* : température eau, niveau essence, tension batterie

# \- \*\*Entrées digitales\*\* : clignotants, feux, pression huile

# \- \*\*GPS NEO-6M / BN-220\*\* (UART2)

# \- \*\*Encodeur rotatif\*\* (navigation et réglages)

# \- \*\*Sauvegarde automatique\*\* à la sortie du menu

# 

# ---

# 

# \## ⚙️ Matériel requis

# 

# | Élément | Référence | Alimentation |

# |----------|------------|---------------|

# | ESP32 DevKit V1 | NodeMCU 38 pins | 5V |

# | Écran TFT | ST7796S SPI 4.0" | 5V |

# | LED | WS2812B x24 | 5V |

# | GPS | NEO-6M / BN-220 | 5V |

# | Modules capteurs | JZK opto \& analogiques | 5–12V |

# | Alim DC | Buck 12V→5V 3A | 12V |

# 

# ---

# 

# \## 🧩 Structure du code

# Projet de tableau de bord numérique pour Austin Mini.

# Compatible ESP32 DevKit V1 + écran TFT 4" ST7796S + LEDs WS2812B + GPS NEO-6M.

# 

# \## Pages disponibles

# \- \*\*Classic\*\* : RPM, vitesse, eau, essence, tension

# \- \*\*Racing\*\* : RPM grand format, shift-light

# \- \*\*GPS\*\* : position, vitesse, fix

# \- \*\*Menu\*\* : réglage du shift RPM, luminosité LED, calibration tension

# 

# \## Commandes

# \- Rotation encodeur : changer de page

# \- Appui long : accéder / quitter Menu

# \- Dans le Menu : rotation = ajustement, appui long = sauvegarde (EEPROM)

# 

# \## Fichiers

# \- `Dash\_Mini\_Retro\_V1.ino` → code principal

# \- `page\_\*.ino` → affichage de chaque page

# \- `GX16\_10\_Cablage.txt` → câblage complet

# \- `lib/TFT\_eSPI/User\_Setup.h` → configuration TFT ST7796S

