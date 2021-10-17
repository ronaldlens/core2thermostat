#include <Arduino.h>
#include <M5Core2.h>
#include "r5gui.h"


R5Event R5GetEvent()
{
  R5Event event;
  event.type = R5EventType::None;
  M5.update();
  Event& e = M5.Buttons.event;
  
  if (e & E_RELEASE) {
    int dx = e.to.x - e.from.x;
    int dy = e.to.y - e.from.y;

    event.x = e.to.x;
    event.y = e.to.y;

    int d = (int) sqrt(dx * dx + dy * dy);
    if (d < 8) {
      event.type = R5EventType::Pressed;
    } else {
      if (abs(dx) < abs(dy)) {
        event.type = (dy < 0) ? R5EventType::MoveUp : R5EventType::MoveDown;
      } else {
        event.type = (dx < 0) ? R5EventType::MoveLeft : R5EventType::MoveRight;
      }
    }
  }
  return event;
}




R5Menu::R5Menu(String _title = "") {
  title = _title;
  offset = 0;
  
}

void R5Menu::addMenu(String text) {
  R5MenuItem item;
  item.text = text;
  item.x = 150 - M5.Lcd.textWidth(text, 4)/2;
  items.push_back(item);
  noItems = items.size();
}

#define MENUSIZE 6

int R5Menu::doMenu() {
  drawMenu();
  while(true) {
    bool changed = false;
    R5Event event = R5GetEvent();
    switch (event.type) {
    
    case R5EventType::MoveUp:
      {
        if (offset < noItems - MENUSIZE) {
          offset++;
          changed = true;
        }
      }
      break;
    case R5EventType::MoveDown:
      {
        if (offset > 0) {
          offset--;
          changed = true;
        }
      }
      break;
    case R5EventType::Pressed:
      {
        int selected = (event.y - 34) / 34 + offset;
        return selected;
      }
      break;
    default: {

    }
    }
    if (changed) {
      drawMenu();
      delay(50);
    }
  }
}

void R5Menu::drawMenu()  {

  int x = 150 - M5.Lcd.textWidth(title, 4)/2;
  M5.Lcd.setTextColor(RED);
  M5.Lcd.drawString(title, x, 0, 4);

  if (noItems > MENUSIZE) {
    // scrollbar needed
    M5.Lcd.fillRect(300, 34, 22, 202, DARKCYAN);
  
    int item_height = (6*34) / noItems;
    int y = offset * item_height + 37;
    int h = item_height * 6 - 4;
    M5.Lcd.fillRect(303, y, 14, h, YELLOW); 
     
  }
  int to = (noItems < 6) ? noItems : MENUSIZE;
  to += offset;
  Serial.printf("from: %d to %d\n", offset, to);
  for(int i=offset; i<to; i++) {
    drawMenuItem(i);
  }  
}

void R5Menu::drawMenuItem(int i) {
  int y = (i - offset)*34 + 34;
  int bgcolor = DARKCYAN;
  int fgcolor = YELLOW;
  M5.Lcd.fillRoundRect(10, y, 280, 32, 6, bgcolor);
  M5.Lcd.setTextColor(fgcolor, bgcolor);
  R5MenuItem item = items.at(i);         
  M5.Lcd.drawString(item.text, item.x, y + 5, 4);
}