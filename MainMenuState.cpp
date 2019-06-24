#include "include/stdafx.h"
#include "include/MainMenuState.h"

// Initiaizlier Function
void MainMenuState::initKeybinds() {
  std::ifstream ifs("config/mainmenustate_keybinds.ini");
  if(ifs.is_open()) {
    std::string key = "";
    std::string key_binding = "";
    while(ifs >> key_binding >> key) {
      this->keybinds[key_binding] = this->supportedKeys->at(key);
    }
  } else {
    std::cout << "file not exist: config/mainmenustate_keybinds.ini" << std::endl;
  }
  ifs.close();
}


void MainMenuState::initBackground() {
  this->background.setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y)));

  if(!this->backgroundTexture.loadFromFile("Resource/images/backgrounds/bg1.png")) {

    throw("ERROR::MAINMENUSTATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE");
  }
  this->background.setTexture(&this->backgroundTexture);

}

void MainMenuState::initVariables() {}


MainMenuState::MainMenuState(sf::RenderWindow* window, GraphicsSettings& gfxSettings, std::map<std::string, int>* supportedKeys, std::stack<State*>*  states) : State(window, supportedKeys, states), gfxSettings(gfxSettings) {
  this->initVariables();
  this->initBackground();
  this->initKeybinds();
  this->initFonts();
  this->initButtons();

}

MainMenuState::~MainMenuState() {

  for(auto it = this->buttons.begin(); it != this->buttons.end(); ++it) {
    if(it->second) {
      delete it->second;
    }
  }

}

void MainMenuState::update(const float& dt) {
  this->updateMousePositions();
  this->updateInput(dt);
  this->updateButtons();

}

void MainMenuState::render(sf::RenderTarget* target) {
  if(!target)
    target = this->window;

  target->draw(this->background);
  this->renderButtons(*target);

  // REMOVE LATER!!
  // sf::Text mouseText;
  // mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 50;);
  // mouseText.setFont(this->font);
  // mouseText.setCharacterSize(12);
  // std::stringstream ss;
  // ss << this->mousePosView.x << " " << this->mousePosView.y;
  // mouseText.setString(ss.str());

  // target->draw(mouseText);

}

void MainMenuState::updateInput(const float& dt) {


}


void MainMenuState::initFonts() {
  if(!this->font.loadFromFile("fonts/DroidSans.ttf")) {
    throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
  }

}

void MainMenuState::initButtons() {
  this->buttons["GAME_STATE"] = new gui::Button(300.f, 480.f, 250.f, 50.f, &this->font, "New Game", 50,
                                                   sf::Color(70, 70, 70, 200),  sf::Color(250, 250, 250, 250),  sf::Color(20, 20, 20, 50),
                                                   sf::Color(70, 70, 70, 0),  sf::Color(150, 150, 150, 0),  sf::Color(20, 20, 20, 0)
                                                   );

  this->buttons["SETTINGS_STATE"] = new gui::Button(300.f, 580.f, 250.f, 50.f, &this->font, "Settings", 50,
                                         sf::Color(70, 70, 70, 200),  sf::Color(250, 250, 250, 250),  sf::Color(20, 20, 20, 50),
                                         sf::Color(70, 70, 70, 0),  sf::Color(150, 150, 150, 0),  sf::Color(20, 20, 20, 0)
                                         );

  this->buttons["EDITOR_STATE"] = new gui::Button(300.f, 680.f, 250.f, 50.f, &this->font, "Editor", 50,
                                             sf::Color(70, 70, 70, 200),  sf::Color(250, 250, 250, 250),  sf::Color(20, 20, 20, 50),
                                             sf::Color(70, 70, 70, 0),  sf::Color(150, 150, 150, 0),  sf::Color(20, 20, 20, 0)
                                             );

  this->buttons["EXIT_STATE"] = new gui::Button(300.f, 880.f, 250.f, 50.f, &this->font, "Quit", 50,
                                                   sf::Color(70, 70, 70, 200),  sf::Color(250, 250, 250, 250),  sf::Color(20, 20, 20, 50),
                                                   sf::Color(70, 70, 70, 0),  sf::Color(150, 150, 150, 0),  sf::Color(20, 20, 20, 0)
                                                   );

}

void MainMenuState::updateButtons() {

  /* update all the buttons in the state and hadle their functionality */

  for (auto &it : this->buttons) {
    it.second->update(this->mousePosView);
  }


  // New Game
  if(this->buttons["GAME_STATE"]->isPressed()) {
    // State를 push할 수 있어야한다.
    this->states->push(new GameState(this->window, this->supportedKeys, this->states));
  }


  // Settings

  if(this->buttons["SETTINGS_STATE"]->isPressed()) {
    // State를 push할 수 있어야한다.
    this->states->push(new SettingsState(this->window, this->gfxSettings, this->supportedKeys, this->states));
  }


  // Editor

  if(this->buttons["EDITOR_STATE"]->isPressed()) {
    // State를 push할 수 있어야한다.
    this->states->push(new EditorState(this->window, this->supportedKeys, this->states));
  }

  // Quit the Game
  if(this->buttons["EXIT_STATE"]->isPressed()) {
    this->endState();
  }

}

void MainMenuState::renderButtons(sf::RenderTarget& target) {
  for (auto &it : this->buttons) {
    it.second->render(target);
  }

}
