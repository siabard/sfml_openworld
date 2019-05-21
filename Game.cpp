#include "include/Game.h"

// Static functions

// Initializer
void Game::initWindow() {
  this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "C++ SFML RPG");
}

// Constructor
Game::Game() {
  this->initWindow();
}


// Destructor
Game::~Game() {
  delete this->window;
}

void Game::updateSFMLEvents() {

  while(this->window->pollEvent(this->sfEvent)) {
    if (this->sfEvent.type == sf::Event::Closed) this->window->close();
  }

}

void Game::update() {
  this->updateSFMLEvents();
};

void Game::render() {
  this->window->clear();

  // render items


  this->window->display();
};

void Game::run() {

  while(this->window->isOpen()) {
    this->update();
    this->render();
  }

};
