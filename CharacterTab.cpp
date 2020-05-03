#include "include/stdafx.h"
#include "include/CharacterTab.h"

CharacterTab::CharacterTab(sf::VideoMode& vm, sf::Font& font,  Player& player)
  : Tab(vm, font, player) {
  //Background
  this->back.setFillColor(sf::Color(50, 50, 50, 200));
  this->back.setSize(sf::Vector2f(gui::p2pX(30.f, this->vm), static_cast<float>(this->vm.height)));

  // Text
  this->infoText.setFont(this->font);
  this->infoText.setCharacterSize(gui::calcCharSize(this->vm, 50));
  this->infoText.setFillColor(sf::Color::White);
  this->infoText.setPosition(this->back.getPosition().x + 20.f, this->back.getPosition().y + 20.f);
}

CharacterTab::~CharacterTab() {}


void CharacterTab::update() {}

void CharacterTab::render(sf::RenderTarget* target) {
  target->draw(this->back);
  target->draw(this->infoText);
}
