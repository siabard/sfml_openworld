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
  this->initFonts();

  this->gamestate_btn = new Button(100, 100, 150, 50, &this->font, "New Game", sf::Color(70, 70, 70, 200),  sf::Color(150, 150, 150, 255),  sf::Color(20, 20, 20, 200));

  this->background.setSize(sf::Vector2f((float)window->getSize().x, (float)window->getSize().y));
  this->background.setFillColor(sf::Color::Magenta);
}

MainMenuState::~MainMenuState() {
  if(this->gamestate_btn)
    delete this->gamestate_btn;
}

void MainMenuState::update(const float& dt) {
  this->updateMousePosition();
  this->updateInput(dt);

  this->gamestate_btn->update(this->mousePosView);
}

void MainMenuState::render(sf::RenderTarget* target) {
  if(!target)
    target = this->window;

  target->draw(this->background);

  this->gamestate_btn->render(target);
}

void MainMenuState::updateInput(const float& dt) {
  this->checkForQuit();


}


void MainMenuState::endState() {
  std::cout << "MainMenuState endState " << std::endl;
}


void MainMenuState::initFonts() {
  if(!this->font.loadFromFile("fonts/DroidSans.ttf")) {
    throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
  }

}
