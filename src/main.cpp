#include <Arduino.h>
#include <M5Core2.h>
#include "r5gui.h"


 




void menuTest2() {
  R5Menu menu = R5Menu("Main Menu");
  menu.addMenu("Enable Wifi");
  menu.addMenu("configure WiFi");
  menu.addMenu("Scan Bluetooth");
  menu.addMenu("set Temperature"); 
  menu.addMenu("Scan heaters");
  menu.addMenu("Configure heaters");
  menu.addMenu("Control heaters");
  menu.addMenu("Control heaters2");
  menu.addMenu("Control heaters3");
  menu.addMenu("Search Thermometer");
  menu.addMenu("Exit");
  int sel = menu.doMenu();
  Serial.printf("Pressed option %d\n", sel);
}

void setup() {
  M5.begin();
  Serial.begin(115200);
  delay(100);
  Serial.println("Booting up");
  

  
  menuTest2(); 
}






void loop() {
  delay(100);
}