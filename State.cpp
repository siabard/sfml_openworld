#include "include/State.h"

State::State(sf::RenderWindow* window,  std::map<std::string, int>* supportedKeys, std::stack<State*>* states) {

  this->window = window;
  this->quit = false;

  this->states = states;
  this->supportedKeys = supportedKeys;
}

State::~State() {
}


const bool& State::getQuit() const {
  return this->quit;
}

void State::updateMousePosition() {
  this->mousePosScreen = sf::Mouse::getPosition();
  this->mousePosWindow = sf::Mouse::getPosition(*this->window);
  this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}

void State::endState() {
  this->quit = true;
}
