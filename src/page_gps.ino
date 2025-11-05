void drawGPS(){
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE,TFT_BLACK);
  tft.setTextSize(3); tft.setCursor(10,10); tft.print("GPS");
  tft.setTextSize(2);
  tft.setCursor(10,60);  tft.printf("Fix : %s", gpsFix ? "OK" : "Non");
  tft.setCursor(10,90);  tft.printf("Vit.: %.0f km/h", gpsSpeed);
  tft.setCursor(10,120); tft.printf("Lat : %.5f", gpsLat);
  tft.setCursor(10,150); tft.printf("Lon : %.5f", gpsLon);
  drawVoltageFooter();
}