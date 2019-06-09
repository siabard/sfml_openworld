#include "include/State.h"

State::State(sf::RenderWindow* window,  std::map<std::string, int>* supportedKeys, std::stack<State*>* states) {

  this->window = window;
  this->quit = false;

  this->states = states;
  this->supportedKeys = supportedKeys;
}

State::~State() {
}

void State::checkForQuit() {
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE")))) {
    this->quit = true;
  }
}


const bool& State::getQuit() const {
  return this->quit;
}

void State::updateMousePosition() {
  this->mousePosScreen = sf::Mouse::getPosition();
  this->mousePosWindow = sf::Mouse::getPosition(*this->window);
  this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}
