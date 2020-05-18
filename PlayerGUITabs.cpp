#include "include/stdafx.h"
#include "include/PlayerGUITabs.h"

PlayerGUITabs::PlayerGUITabs(sf::VideoMode& vm, sf::Font& font, Player& player)
  : vm(vm), font(font), player(player), characterTab(vm, font, player)
{

}

PlayerGUITabs::~PlayerGUITabs() {};

void PlayerGUITabs::update() {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {

    if(this->characterTab.getHidden()) {
      this->characterTab.show();
    } else {
      this->characterTab.hide();
    }
  }

  this->characterTab.update();

}
void PlayerGUITabs::render(sf::RenderTarget& target) {
  this->characterTab.render(target);
}
