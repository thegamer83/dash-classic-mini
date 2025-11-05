void drawMenu(){
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_CYAN,TFT_BLACK);
  tft.setTextSize(3); tft.setCursor(10,10); tft.print("Reglages");
  tft.setTextSize(2); tft.setTextColor(TFT_WHITE,TFT_BLACK);
  tft.setCursor(10,60);  tft.printf("1. Shift: %u RPM", cfg.shiftRpm);
  tft.setCursor(10,90);  tft.printf("2. LED  : %u /255", cfg.ledBrightness);
  tft.setCursor(10,120); tft.printf("3. Ratio V: %.2f", cfg.voltageRatio);
  tft.setCursor(10,150); tft.print ("Appui long: sauvegarde");
  drawVoltageFooter();
}