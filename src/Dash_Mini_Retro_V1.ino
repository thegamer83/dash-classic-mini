/* Dash_Mini_Retro_V1 - Full */
#include <Arduino.h>
#include <TFT_eSPI.h>
#include <SPI.h>
#include <Adafruit_NeoPixel.h>
#include <HardwareSerial.h>
#include <EEPROM.h>

#define TFT_CS   5
#define TFT_DC   26
#define TFT_RST  25
#define TFT_BL   27

#define LED_PIN        13
#define LED_COUNT      24

#define GPS_RX   16
#define GPS_TX   17
HardwareSerial GPS(2);

#define RPM_PIN        34
#define FUEL_AIN       32
#define TEMP_AIN       33
#define VBAT_AIN       36
#define IND_L_PIN      14
#define IND_R_PIN       4
#define LOW_BEAM_PIN   22
#define HIGH_BEAM_PIN  35
#define OIL_PIN        39

#define ENC_A          2
#define ENC_B          15
#define ENC_BTN        0

TFT_eSPI tft = TFT_eSPI();
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

enum Page {PAGE_CLASSIC, PAGE_RACING, PAGE_GPS, PAGE_MENU};
Page currentPage = PAGE_CLASSIC;

struct Persist {
  uint8_t version = 1;
  uint16_t shiftRpm = 6500;
  uint8_t ledBrightness = 160;
  float voltageRatio = 4.03f;
  uint8_t lastPage = PAGE_CLASSIC;
} cfg;

volatile uint32_t rpmPulseCount = 0;
uint32_t lastRpmMillis = 0;
float rpmValue = 0.0, vbat=0.0, fuelPct=0.0, waterC=0.0;
bool gpsFix=false; float gpsSpeed=0.0, gpsLat=0.0, gpsLon=0.0;

void drawClassic(); void drawRacing(); void drawGPS(); void drawMenu();
void drawVoltageFooter(); void updateShiftLed(float rpm);
void IRAM_ATTR onRpmPulse(){ rpmPulseCount++; }

float readVoltage(){ int raw=analogRead(VBAT_AIN); return (raw/4095.0f)*3.3f*cfg.voltageRatio; }
float readFuelPct(){ int raw=analogRead(FUEL_AIN); return constrain(map(raw,3000,500,0,100),0,100); }
float readWaterC(){ int raw=analogRead(TEMP_AIN); float c=map(raw,600,2800,30,110); return constrain(c,30,130); }

void readInputs(){
  uint32_t now=millis();
  if(now-lastRpmMillis>=250){
    noInterrupts(); uint32_t p=rpmPulseCount; rpmPulseCount=0; interrupts();
    float revs=(float)p/1.0f; rpmValue=(revs*1000.0f*60.0f)/(now-lastRpmMillis); lastRpmMillis=now;
  }
  vbat=readVoltage(); fuelPct=readFuelPct(); waterC=readWaterC();
  while(GPS.available()){ GPS.read(); gpsFix=true; }
  bool indL=digitalRead(IND_L_PIN), indR=digitalRead(IND_R_PIN);
  bool lowB=digitalRead(LOW_BEAM_PIN), highB=digitalRead(HIGH_BEAM_PIN), oil=digitalRead(OIL_PIN);
  strip.setPixelColor(0,  indL?strip.Color(255,200,0):0);
  strip.setPixelColor(1,  highB?strip.Color(255,255,255):0);
  strip.setPixelColor(2,  lowB ?strip.Color(0,120,255):0);
  strip.setPixelColor(3,  (waterC>105)?strip.Color(255,0,0):strip.Color(0,180,200));
  strip.setPixelColor(20, indR?strip.Color(255,200,0):0);
  strip.setPixelColor(21, (fuelPct<15)?strip.Color(255,0,0):0);
  strip.setPixelColor(22, gpsFix?strip.Color(0,200,0):strip.Color(255,80,0));
  strip.setPixelColor(23, oil?strip.Color(255,0,0):0);
  updateShiftLed(rpmValue); strip.show();
}

void updateShiftLed(float rpm){
  const int first=4,last=19,total=last-first+1;
  float ratio=constrain(rpm/(float)cfg.shiftRpm,0.0f,1.2f); int lit=(int)round(ratio*total);
  for(int i=0;i<total;i++){ uint32_t col=0; if(i<lit){ float p=(float)i/(float)(total-1);
    uint8_t r=(p<0.5)?(uint8_t)(p*2*255):255; uint8_t g=(p<0.5)?255:(uint8_t)((1.0-(p-0.5)*2)*255);
    col=strip.Color(r,g,0);} strip.setPixelColor(first+i,col);
  }
}

void drawVoltageFooter(){
  if(vbat<11.5) tft.setTextColor(TFT_RED,TFT_BLACK);
  else if(vbat>14.8) tft.setTextColor(TFT_YELLOW,TFT_BLACK);
  else tft.setTextColor(TFT_GREEN,TFT_BLACK);
  tft.setTextSize(2); tft.setCursor(10,290); tft.printf("Vbat: %.1fV", vbat);
}

void loadEEP(){ EEPROM.begin(256); EEPROM.get(0,cfg); if(cfg.version!=1){ cfg=Persist(); EEPROM.put(0,cfg); EEPROM.commit(); } }
void saveEEP(){ EEPROM.put(0,cfg); EEPROM.commit(); }

int encLast=0;
int readEnc(){ int a=digitalRead(ENC_A), b=digitalRead(ENC_B); int e=(a<<1)|b, d=0;
  if(e!=encLast){ if((encLast==0b00&&e==0b01)||(encLast==0b01&&e==0b11)||(encLast==0b11&&e==0b10)||(encLast==0b10&&e==0b00)) d=+1;
                  if((encLast==0b00&&e==0b10)||(encLast==0b10&&e==0b11)||(encLast==0b11&&e==0b01)||(encLast==0b01&&e==0b00)) d=-1; encLast=e;}
  return d;
}

void setup(){
  pinMode(TFT_BL,OUTPUT); digitalWrite(TFT_BL,HIGH);
  pinMode(IND_L_PIN,INPUT); pinMode(IND_R_PIN,INPUT);
  pinMode(LOW_BEAM_PIN,INPUT); pinMode(HIGH_BEAM_PIN,INPUT); pinMode(OIL_PIN,INPUT);
  pinMode(ENC_A,INPUT_PULLUP); pinMode(ENC_B,INPUT_PULLUP); pinMode(ENC_BTN,INPUT_PULLUP);
  pinMode(RPM_PIN,INPUT); attachInterrupt(digitalPinToInterrupt(RPM_PIN), onRpmPulse, RISING);
  tft.init(); tft.setRotation(1); tft.fillScreen(TFT_BLACK);
  strip.begin(); strip.setBrightness(160); strip.show();
  GPS.begin(9600, SERIAL_8N1, GPS_RX, GPS_TX);
  loadEEP(); currentPage=(Page)cfg.lastPage; strip.setBrightness(cfg.ledBrightness); analogReadResolution(12);
  tft.setTextColor(TFT_WHITE,TFT_BLACK); tft.setTextSize(3); tft.setCursor(10,10); tft.print("Dash Mini Retro V1"); delay(600);
}

void handleUI(){
  int d=readEnc();
  if(d!=0){ if(currentPage==PAGE_MENU){ cfg.voltageRatio=constrain(cfg.voltageRatio+d*0.01f,3.50f,5.00f); }
            else{ int p=(int)currentPage+(d>0?1:-1); if(p<0)p=3; if(p>3)p=0; currentPage=(Page)p; cfg.lastPage=(uint8_t)currentPage; } }
  bool pressed=(digitalRead(ENC_BTN)==LOW); static uint32_t t0=0;
  if(pressed && t0==0) t0=millis(); if(!pressed && t0>0) t0=0;
  if(pressed && t0>0 && millis()-t0>700){ t0=0; if(currentPage==PAGE_MENU){ saveEEP(); currentPage=PAGE_CLASSIC; } else currentPage=PAGE_MENU; }
}

void loop(){
  readInputs(); handleUI();
  switch(currentPage){ case PAGE_CLASSIC: drawClassic(); break; case PAGE_RACING: drawRacing(); break; case PAGE_GPS: drawGPS(); break; case PAGE_MENU: drawMenu(); break; }
  delay(50);
}
