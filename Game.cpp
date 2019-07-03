#include "include/stdafx.h"
#include "include/Game.h"
#include "include/GameState.h"
#include "include/MainMenuState.h"

// Static functions

// Initializer

void Game::initGraphicsSettings() {
  this->gfxSettings.loadFromFile("config/graphics.ini");
}

void Game::initVariables() {
  this->window = nullptr;

  this->dt = 0.f;
  this->gridSize = 100.f;
}


void Game::initWindow() {
  /* Create a SFML window using options from a window.ini file*/
  if(this->gfxSettings.fullscreen)
    this->window = new sf::RenderWindow(this->gfxSettings.resolution, this->gfxSettings.title, sf::Style::Fullscreen , this->gfxSettings.contextSettings);
  else
    this->window = new sf::RenderWindow(this->gfxSettings.resolution, this->gfxSettings.title, sf::Style::Titlebar | sf::Style::Close, this->gfxSettings.contextSettings);

  this->window->setFramerateLimit(this->gfxSettings.frameRateLimit);
  this->window->setVerticalSyncEnabled(this->gfxSettings.verticalSync);
}

void Game::initStates() {
  this->states.push(new MainMenuState(&this->stateData));
  //this->states.push(new GameState(this->window, &this->supportedKeys));
}

void Game::initStateData() {
  this->stateData.window = this->window;
  this->stateData.gfxSettings = &this->gfxSettings;
  this->stateData.supportedKeys = &this->supportedKeys;
  this->stateData.states = &this->states;
  this->stateData.gridSize = this->gridSize;
}

// Constructor
Game::Game() {
  this->initVariables();
  this->initGraphicsSettings();
  this->initWindow();
  this->initKeys();
  this->initStateData();
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

  if (!this->states.empty() ) {
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
