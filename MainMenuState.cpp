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

void MainMenuState::initVariables() {}


MainMenuState::MainMenuState(StateData* state_data) : State(state_data) {
  this->initVariables();
  this->initKeybinds();
  this->initFonts();
  this->initGui();
  this->resetGui();

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

  target->draw(this->btnBackground);

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

void MainMenuState::initGui() {
  const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;

  // Backgrounds

  this->background.setSize(sf::Vector2f(static_cast<float>(vm.width), static_cast<float>(vm.height)));
  if(!this->backgroundTexture.loadFromFile("Resource/images/backgrounds/bg1.png")) {

    throw("ERROR::MAINMENUSTATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE");
  }

  this->background.setTexture(&this->backgroundTexture);

  // Button Background
  this->btnBackground.setSize(
                              sf::Vector2f(
                                           static_cast<float>(vm.width / 5),
                                           static_cast<float>(vm.height))
                              );

  this->btnBackground.setPosition(gui::p2pX(11.5f, vm), 0.f);
  this->btnBackground.setFillColor(sf::Color(10, 10, 10, 220));

  // Buttons
  this->buttons["GAME_STATE"] =
    new gui::Button(gui::p2pX(15.6f, vm), gui::p2pY(30.4f, vm),
                    gui::p2pX(13.0f, vm), gui::p2pY(6.f, vm),
                    &this->font, "New Game", gui::calcCharSize(vm),
                    sf::Color(70, 70, 70, 200),  sf::Color(250, 250, 250, 250),  sf::Color(20, 20, 20, 50),
                    sf::Color(70, 70, 70, 0),  sf::Color(150, 150, 150, 0),  sf::Color(20, 20, 20, 0)
                    );

  this->buttons["SETTINGS_STATE"] =
    new gui::Button(gui::p2pX(15.6f, vm), gui::p2pY(40.f, vm),
                    gui::p2pX(13.0f, vm), gui::p2pY(6.f, vm),
                    &this->font, "Settings", gui::calcCharSize(vm),
                    sf::Color(70, 70, 70, 200),  sf::Color(250, 250, 250, 250),  sf::Color(20, 20, 20, 50),
                    sf::Color(70, 70, 70, 0),  sf::Color(150, 150, 150, 0),  sf::Color(20, 20, 20, 0)
                    );

  this->buttons["EDITOR_STATE"] =
    new gui::Button(gui::p2pX(15.6f, vm), gui::p2pY(50.f, vm),
                    gui::p2pX(13.0f, vm), gui::p2pY(6.f, vm),
                    &this->font, "Editor", gui::calcCharSize(vm),
                    sf::Color(70, 70, 70, 200),  sf::Color(250, 250, 250, 250),  sf::Color(20, 20, 20, 50),
                    sf::Color(70, 70, 70, 0),  sf::Color(150, 150, 150, 0),  sf::Color(20, 20, 20, 0)
                    );

  this->buttons["EXIT_STATE"] =
    new gui::Button(gui::p2pX(15.6f, vm), gui::p2pY(65.5f, vm),
                    gui::p2pX(13.0f, vm), gui::p2pY(6.f, vm),
                    &this->font, "Quit", gui::calcCharSize(vm),
                    sf::Color(70, 70, 70, 200),  sf::Color(250, 250, 250, 250),  sf::Color(20, 20, 20, 50),
                    sf::Color(70, 70, 70, 0),  sf::Color(150, 150, 150, 0),  sf::Color(20, 20, 20, 0)
                    );

}

void MainMenuState::resetGui() {
  auto it = this->buttons.begin();
  for(it = this->buttons.begin(); it != this->buttons.end(); ++it) {
    delete it->second;
  }
  this->buttons.clear();

  this->initGui();
}

void MainMenuState::updateButtons() {

  /* update all the buttons in the state and hadle their functionality */

  for (auto &it : this->buttons) {
    it.second->update(this->mousePosWindow);
  }


  // New Game
  if(this->buttons["GAME_STATE"]->isPressed()) {
    // State를 push할 수 있어야한다.
    this->states->push(new GameState(this->stateData));
  }


  // Settings

  if(this->buttons["SETTINGS_STATE"]->isPressed()) {
    // State를 push할 수 있어야한다.
    this->states->push(new SettingsState(this->stateData));
  }


  // Editor

  if(this->buttons["EDITOR_STATE"]->isPressed()) {
    // State를 push할 수 있어야한다.
    this->states->push(new EditorState(this->stateData));
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
