#include "GameState.h"

void GameState::initKeybinds() {
  std::ifstream ifs("config/gamestate_keybinds.ini");
  if(ifs.is_open()) {
    std::string key = "";
    std::string key_binding = "";
    while(ifs >> key_binding >> key) {
      this->keybinds[key_binding] = this->supportedKeys->at(key);
    }
  } else {
    std::cout << "file not exist: gamestate_keybinds.ini" << std::endl;
  }
  ifs.close();
}

GameState::GameState(sf::RenderWindow* window,  std::map<std::string, int>* supportedKeys, std::stack<State*>* states) : State(window, supportedKeys, states) {
  this->initKeybinds();
}

GameState::~GameState() {
}

void GameState::update(const float& dt) {
  this->updateInput(dt);
  this->player.update(dt);
}

void GameState::render(sf::RenderTarget* target) {
  if(!target)
    target = this->window;

  this->player.render(target);
}

void GameState::updateInput(const float& dt) {
  this->checkForQuit();

  // Update player input
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
    this->player.move(dt, -1.f, 0.f);

  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
    this->player.move(dt, 1.f, 0.f);

  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
    this->player.move(dt, 0.f, -1.f);

  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
    this->player.move(dt, 0.f, 1.f);
}


void GameState::endState() {
  std::cout << "GameState endState " << std::endl;
}
