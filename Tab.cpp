#include "include/stdafx.h"
#include "include/Tab.h"

Tab::Tab(sf::VideoMode& vm, sf::Font& font, Player& player, bool hidden)
  : vm(vm), font(font), player(player), hidden(hidden) {}

Tab::~Tab() {}

const bool Tab::getHidden() const {
  return this->hidden;
}

void Tab::hide() { this->hidden = true;}
void Tab::show() { this->hidden = false;}
