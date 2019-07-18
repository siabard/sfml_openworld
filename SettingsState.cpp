#include "include/stdafx.h"
#include "include/SettingsState.h"

SettingsState::SettingsState(StateData* state_data) : State(state_data) {
  this->initVariables();
  this->initBackground();
  this->initKeybinds();
  this->initFonts();
  this->initGui();
  this->initText();
}

SettingsState::~SettingsState() {

  for(auto it = this->buttons.begin(); it != this->buttons.end(); ++it) {
    if(it->second) {
      delete it->second;
    }
  }


  for(auto it = this->dropdownLists.begin(); it != this->dropdownLists.end(); ++it) {
    if(it->second) {
      delete it->second;
    }
  }


}



// Initiaizlier Function
void SettingsState::initKeybinds() {
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


void SettingsState::initBackground() {
  this->background.setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y)));

  if(!this->backgroundTexture.loadFromFile("Resource/images/backgrounds/bg1.png")) {

    throw("ERROR::MAINMENUSTATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE");
  }
  this->background.setTexture(&this->backgroundTexture);

}

void SettingsState::initVariables() {
  this->modes = sf::VideoMode::getFullscreenModes();
}



void SettingsState::initFonts() {
  if(!this->font.loadFromFile("fonts/DroidSans.ttf")) {
    throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
  }

}

void SettingsState::initGui() {
  this->buttons["BACK"] =
    new gui::Button(this->p2pX(72.f), this->p2pY(81.5f),
                    this->p2pX(13.0f), this->p2pY(6.f),
                    &this->font, "Back", this->calcCharSize(),
                    sf::Color(70, 70, 70, 200),  sf::Color(250, 250, 250, 250),  sf::Color(20, 20, 20, 50),
                    sf::Color(100, 100, 100, 0),  sf::Color(150, 150, 150, 0),  sf::Color(20, 20, 20, 0)
                    );

  this->buttons["APPLY"] =
    new gui::Button(this->p2pX(60.f), this->p2pY(81.5f),
                    this->p2pX(13.0f), this->p2pY(6.f),
                    &this->font, "Apply", this->calcCharSize(),
                    sf::Color(70, 70, 70, 200),  sf::Color(250, 250, 250, 250),  sf::Color(20, 20, 20, 50),
                    sf::Color(100, 100, 100, 0),  sf::Color(150, 150, 150, 0),  sf::Color(20, 20, 20, 0)
                    );

  std::vector<std::string> modes_str;

  for(auto &i : this->modes) {
    modes_str.push_back(std::to_string(i.width) + 'x' + std::to_string(i.height));
  }

  std::string li[] = {
                      "1920x1080", "800x600", "640x480"
  };
  this->dropdownLists["RESOLUTION"] =
    new gui::DropDownList(this->p2pX(42.f), this->p2pY(42.f),
                          this->p2pX(10.4f), this->p2pY(4.5f),
                          font, modes_str.data(), modes_str.size(), 0);

}


void SettingsState::initText() {
  this->optionsText.setFont(font);

  this->optionsText.setPosition(sf::Vector2f(100.f, 450.f));

  this->optionsText.setCharacterSize(30);
  this->optionsText.setFillColor(sf::Color(255, 255, 255, 200));

  this->optionsText.setString(
                              "TEST"
                              // "Resolution " + "\n\n" +
                              // "Fullscreen " + "\n\n" +
                              // "Vsync " + "\n\n" +
                              // "Antialiasing " + "\n\n"
                              );

}

void SettingsState::update(const float& dt) {
  this->updateMousePositions();
  this->updateInput(dt);
  this->updateGui(dt);


}


void SettingsState::updateInput(const float& dt) {


}



void SettingsState::render(sf::RenderTarget* target) {
  if(!target)
    target = this->window;

  target->draw(this->background);
  this->renderGui(*target);

  target->draw(this->optionsText);

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

void SettingsState::updateGui(const float& dt) {

  /* update all the buttons in the state and hadle their functionality */

  for (auto &it : this->buttons) {
    it.second->update(this->mousePosWindow);
  }


  // Button functionality
  // Quit the Game
  if(this->buttons["BACK"]->isPressed()) {
    this->endState();
  }

  // apply
  if(this->buttons["APPLY"]->isPressed()) {
    // TODO: Test Remove later
    this->stateData->gfxSettings->resolution = this->modes[this->dropdownLists["RESOLUTION"]->getActiveElementId()];

    this->window->create(this->stateData->gfxSettings->resolution, this->stateData->gfxSettings->title, sf::Style::Default);
  }

  // Dropdown lists
  for (auto &it : this->dropdownLists) {
    it.second->update(this->mousePosWindow, dt);
  }

  // dropdown lists functionality
}

void SettingsState::renderGui(sf::RenderTarget& target) {
  for (auto &it : this->buttons) {
    it.second->render(target);
  }

  for (auto &it : this->dropdownLists) {
    it.second->render(target);
  }

}
