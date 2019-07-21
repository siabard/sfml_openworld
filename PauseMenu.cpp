#include "include/stdafx.h"
#include "include/PauseMenu.h"

PauseMenu::PauseMenu(const sf::VideoMode& vm, sf::Font& font) :
  font(font)
{

  // init background
  this->background
    .setSize(
             sf::Vector2f(static_cast<float>(vm.width)
                          , static_cast<float>(vm.height)));
  this->background
    .setFillColor(sf::Color(20, 20, 20, 100));

  // init container
  this->container
    .setSize(
             sf::Vector2f(static_cast<float>(vm.width) / 4.f
                          , static_cast<float>(vm.height) - gui::p2pY(9.3f, vm)));
  this->container
    .setFillColor(sf::Color(20, 20, 20, 200));

  this->container
    .setPosition(
                 static_cast<float>(vm.width) / 2.f - this->container.getSize().x / 2.f,
                 gui::p2pY(3.f, vm));

  // init text
  this->menuText.setFont(font);
  this->menuText.setFillColor(sf::Color(255, 255, 255, 200));
  this->menuText.setCharacterSize(gui::calcCharSize(vm));
  this->menuText.setString("PAUSED");
  this->menuText.setPosition(this->container.getPosition().x +
                             this->container.getSize().x / 2.f -
                             this->menuText.getGlobalBounds().width / 2.f
                             ,  this->container.getPosition().y + gui::p2pY(4.f, vm));
}


PauseMenu::~PauseMenu() {
  auto it = this->buttons.begin();
  for(it = this->buttons.begin(); it != this->buttons.end(); it++) {
    delete it->second;
  }
}

void PauseMenu::update(const sf::Vector2i& mousePos) {
  for(auto &i: this->buttons) {
    i.second->update(mousePos);
  }
}

void PauseMenu::render(sf::RenderTarget& target) {
  target.draw(this->background);
  target.draw(this->container);

  for(auto &i: this->buttons) {
    i.second->render(target);
  }

  target.draw(this->menuText);

}


std::map<std::string, gui::Button*>& PauseMenu::getButtons() {
  return this->buttons;
}

void PauseMenu::addButton(const std::string key,
                          const float y,
                          const float width,
                          const float height,
                          const unsigned charSize,
                          const std::string text) {

  float x = this->container.getPosition().x + this->container.getSize().x / 2.f - width / 2.f;

  this->buttons[key] = new gui::Button(x, y, width, height, &this->font, text, charSize,
                                           sf::Color(70, 70, 70, 200),  sf::Color(250, 250, 250, 250),  sf::Color(20, 20, 20, 50),
                                           sf::Color(70, 70, 70, 0),  sf::Color(150, 150, 150, 0),  sf::Color(20, 20, 20, 0)
                                           );

}


const bool PauseMenu::isButtonPressed(const std::string key) {
  return this->buttons[key]->isPressed();
}
