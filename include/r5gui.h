#ifndef _R5GUI_H
#define _R5GUI_H

#include <Arduino.h>

enum R5EventType {
  None,
  MoveUp,
  MoveDown,
  MoveLeft,
  MoveRight,
  Pressed,
};

struct R5Event {
  R5EventType type;
  int x;
  int y;
};

R5Event R5GetEvent();

struct R5MenuItem {
  String text = "";
  int x = 0;
};


struct R5Menu {
public:
  R5Menu(String title);
  void addMenu(String str);
  int doMenu();
private:
  void drawMenu();
  void drawMenuItem(int i);
  String title;
  int offset;
  std::vector<R5MenuItem> items;
  int noItems;
};

#endif