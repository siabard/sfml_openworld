#include "include/Game.h"
#include "States/GameState.h"
#include "States/MainMenuState.h"

// Static functions

// Initializer

void Game::initVariables() {
  this->window = nullptr;
  this->fullscreen = false;

  this->dt = 0.f;
}

void Game::initWindow() {
  /* Create a SFML window using options from a window.ini file*/
  std::ifstream ifs("config/window.ini");
  this->videoModes = sf::VideoMode::getFullscreenModes();

  std::string title = "None";
  sf::VideoMode window_bounds = sf::VideoMode::getDesktopMode();
  bool fullscreen = false;
  unsigned int framerate_limit = 120;
  bool vertical_sync_enabled = false;
  unsigned antialiasing_level = 0;

  if(ifs.is_open()) {
    std::getline(ifs, title);
    ifs >> window_bounds.width >> window_bounds.height;
    ifs >> fullscreen;
    ifs >> framerate_limit;
    ifs >> vertical_sync_enabled;
    ifs >> antialiasing_level;
  }

  ifs.close();

  this->fullscreen = fullscreen;
  this->windowSettings.antialiasingLevel = antialiasing_level;

  if(this->fullscreen)
    this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Fullscreen , this->windowSettings);
  else
    this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Titlebar | sf::Style::Close, this->windowSettings);

  this->window->setFramerateLimit(framerate_limit);
  this->window->setVerticalSyncEnabled(vertical_sync_enabled);
}

void Game::initStates() {
  this->states.push(new MainMenuState(this->window, &this->supportedKeys, &this->states));
  //this->states.push(new GameState(this->window, &this->supportedKeys));
}

// Constructor
Game::Game() {
  this->initVariables();
  this->initWindow();
  this->initKeys();
  this->initStates();
}


// Destructor
Game::~Game() {
  while(!this->states.empty()) {
    std::cout << "Remove states" << std::endl;
    delete this->states.top();
    this->states.pop();
  }

  if(this->window) {
    std::cout << "Remove Window" << std::endl;
    delete this->window;
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

void Game::initKeys() {

  std::ifstream ifs("config/supported_key.ini");
  if(ifs.is_open()) {
    std::string key = "";
    int key_value = 0;
    while(ifs >> key >> key_value) {
      std::cout << key << " " << key_value << std::endl;
      this->supportedKeys[key] = key_value;
    }
  } else {
    std::cout << "file not exist: supported_keys.ini" << std::endl;
  }
  ifs.close();

  for(auto i: this->supportedKeys) {
    std::cout << i.first << " " << i.second << std::endl;
  }
}
