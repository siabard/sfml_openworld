#include "MainMenuState.h"

void MainMenuState::initKeybinds() {
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

MainMenuState::MainMenuState(sf::RenderWindow* window,  std::map<std::string, int>* supportedKeys) : State(window, supportedKeys) {
  this->initKeybinds();

  this->background.setSize(sf::Vector2f((float)window->getSize().x, (float)window->getSize().y));
  this->background.setFillColor(sf::Color::Magenta);
}

MainMenuState::~MainMenuState() {
}

void MainMenuState::update(const float& dt) {
  this->updateInput(dt);
}

void MainMenuState::render(sf::RenderTarget* target) {
  if(!target)
    target = this->window;

  target->draw(this->background);
}

void MainMenuState::updateInput(const float& dt) {
  this->checkForQuit();


}


void MainMenuState::endState() {
  std::cout << "MainMenuState endState " << std::endl;
}
