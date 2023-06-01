#include <TFT_eSPI.h> // Hardware-specific library
#include <SPI.h>
#include <WiFi.h>
#include "time.h"

TFT_eSPI tft = TFT_eSPI();

const char* ssid = "Maxi";
const char* password = "Tacosarecool";

void setup(void) {
  Serial.begin(9600);

  //connect to wifi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");

  // Init and get the time
  configTime(0, 3600, "pool.ntp.org");
  updateTime();

  //disconnect WiFi as it's no longer needed
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
  
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);

  tft.setTextSize(0.8);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
}

void loop() {
    delay(1000);
    updateTime();
  }
void updateTime(){
  struct tm timeinfo;
    if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  char timeHour[3];
  strftime(timeHour,3, "%H", &timeinfo);

  char timeMin[3];
  strftime(timeMin,3, "%M", &timeinfo);

    int xpos = -10;
    int ypos = 30;
    int ysecs = ypos + 24;

    xpos += tft.drawString(timeHour, xpos, ypos, 8);    
    xpos += tft.drawChar(':', xpos, ypos - 8, 8);
    xpos += tft.drawString(timeMin, xpos, ypos, 8);   
}





