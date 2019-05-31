#include "include/State.h"

State::State(sf::RenderWindow* window,  std::map<std::string, int>* supportedKeys) {
  this->window = window;
  this->quit = false;
  this->supportedKeys = supportedKeys;
}

State::~State() {
}

void State::checkForQuit() {
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
    this->quit = true;
  }
}


const bool& State::getQuit() const {
  return this->quit;
}
