void drawRacing(){
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE,TFT_BLACK);
  tft.setTextSize(4); tft.setCursor(10,10); tft.print("Racing");
  tft.setTextSize(3); tft.setCursor(10,80); tft.printf("RPM: %.0f / %u", rpmValue, cfg.shiftRpm);
  drawVoltageFooter();
}