#include "include/Game.h"
#include "States/GameState.h"

// Static functions

// Initializer
void Game::initWindow() {
  /* Create a SFML window using options from a window.ini file*/
  std::ifstream ifs("config/window.ini");

  std::string title = "None";
  sf::VideoMode window_bounds(800, 600);
  unsigned int framerate_limit = 120;
  bool vertical_sync_enabled = false;

  if(ifs.is_open()) {
    std::getline(ifs, title);
    ifs >> window_bounds.width >> window_bounds.height;
    ifs >> framerate_limit;
    ifs >> vertical_sync_enabled;
  }

  ifs.close();

  this->window = new sf::RenderWindow(window_bounds, title);
  this->window->setFramerateLimit(framerate_limit);
  this->window->setVerticalSyncEnabled(vertical_sync_enabled);
}

void Game::initStates() {
  this->states.push(new GameState(this->window));
}

// Constructor
Game::Game() {
  this->initWindow();
  this->initStates();
}


// Destructor
Game::~Game() {
  delete this->window;

  while(!this->states.empty()) {
    delete this->states.top();
    this->states.pop();
  }
}

void Game::updateSFMLEvents() {

  while(this->window->pollEvent(this->sfEvent)) {
    if (this->sfEvent.type == sf::Event::Closed) this->window->close();
  }

}

void Game::endApplication() {
  std::cout << "Ending Appliation" << std::endl;
}

void Game::update() {
  this->updateSFMLEvents();

  if (!this->states.empty()) {
    this->states.top()->update(this->dt);

    if(this->states.top()->getQuit()) {
      this->states.top()->endState();
      delete this->states.top();
      this->states.pop();
    }
  } else {
    this->endApplication();
    this->window->close();
  }
};

void Game::render() {
  this->window->clear();

  // render items

  if(!this->states.empty()) {
    this->states.top()->render();
  }


  this->window->display();
};

void Game::run() {

  while(this->window->isOpen()) {
    this->updateDt();
    this->update();
    this->render();
  }

};


void Game::updateDt() {
  /* update the dt value with the time it takes to update and render one frame */

  this->dt = this->dtClock.getElapsedTime().asSeconds();
  this->dtClock.restart();

}
