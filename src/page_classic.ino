void drawClassic(){
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE,TFT_BLACK);
  tft.setTextSize(3); tft.setCursor(10,10); tft.print("Classic");
  tft.setTextSize(2);
  tft.setCursor(10,60);  tft.printf("RPM: %.0f", rpmValue);
  tft.setCursor(10,90);  tft.printf("Vit.: %.0f km/h", gpsSpeed);
  tft.setCursor(10,120); tft.printf("Eau : %.0f C", waterC);
  tft.setCursor(10,150); tft.printf("Fuel: %.0f %%", fuelPct);
  drawVoltageFooter();
}