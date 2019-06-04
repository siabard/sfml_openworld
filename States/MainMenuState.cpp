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
  this->initButtons();
  this->background.setSize(sf::Vector2f((float)window->getSize().x, (float)window->getSize().y));
  this->background.setFillColor(sf::Color::Magenta);
}

MainMenuState::~MainMenuState() {

  for(auto it = this->buttons.begin(); it != this->buttons.end(); ++it) {
    if(it->second) {
      delete it->second;
    }
  }

}

void MainMenuState::update(const float& dt) {
  this->updateMousePosition();
  this->updateInput(dt);
  this->updateButtons();

}

void MainMenuState::render(sf::RenderTarget* target) {
  if(!target)
    target = this->window;

  target->draw(this->background);
  this->renderButtons(target);
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

void MainMenuState::initButtons() {
  this->buttons["GAME_STATE_BUTTONS"] = new Button(100, 100, 150, 50, &this->font, "New Game", sf::Color(70, 70, 70, 200),  sf::Color(150, 150, 150, 255),  sf::Color(20, 20, 20, 200));

  this->buttons["EXIT_STATE_BUTTONS"] = new Button(100, 300, 150, 50, &this->font, "Quit", sf::Color(100, 100, 100, 200),  sf::Color(150, 150, 150, 255),  sf::Color(20, 20, 20, 200));

}

void MainMenuState::updateButtons() {

  /* update all the buttons in the state and hadle their functionality */

  for (auto &it : this->buttons) {
    it.second->update(this->mousePosView);
  }


  // New Game
  if(this->buttons["GAME_STATE_BUTTONS"]->isPressed()) {
    // State를 push할 수 있어야한다.
  }



  // Quit the Game
  if(this->buttons["EXIT_STATE_BUTTONS"]->isPressed()) {
    this->quit = true;
  }

}

void MainMenuState::renderButtons(sf::RenderTarget* target) {
  for (auto &it : this->buttons) {
    it.second->render(target);
  }

}
