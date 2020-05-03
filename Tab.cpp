#include "include/stdafx.h"
#include "include/Tab.h"

Tab::Tab(sf::VideoMode& vm, sf::Font& font, Player& player)
  : vm(vm), font(font), player(player) {}

Tab::~Tab() {}
