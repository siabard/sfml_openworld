#include "include/stdafx.h"
#include "include/SettingsState.h"

SettingsState::SettingsState(StateData* state_data) : State(state_data) {
  this->initVariables();
  this->initKeybinds();
  this->initFonts();
  this->initGui();
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

void SettingsState::initVariables() {
  this->modes = sf::VideoMode::getFullscreenModes();
}



void SettingsState::initFonts() {
  if(!this->font.loadFromFile("fonts/DroidSans.ttf")) {
    throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
  }

}

void SettingsState::initGui() {
  const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;

  // Background stuff
  this->background.setSize(sf::Vector2f(static_cast<float>(vm.width), static_cast<float>(vm.height)));

  if(!this->backgroundTexture.loadFromFile("Resource/images/backgrounds/bg1.png")) {

    throw("ERROR::MAINMENUSTATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE");
  }
  this->background.setTexture(&this->backgroundTexture);

  // Buttons
  this->buttons["BACK"] =
    new gui::Button(gui::p2pX(72.f, vm), gui::p2pY(81.5f, vm),
                    gui::p2pX(13.0f, vm), gui::p2pY(6.f, vm),
                    &this->font, "Back", gui::calcCharSize(vm),
                    sf::Color(70, 70, 70, 200),  sf::Color(250, 250, 250, 250),  sf::Color(20, 20, 20, 50),
                    sf::Color(100, 100, 100, 0),  sf::Color(150, 150, 150, 0),  sf::Color(20, 20, 20, 0)
                    );

  this->buttons["APPLY"] =
    new gui::Button(gui::p2pX(60.f, vm), gui::p2pY(81.5f, vm),
                    gui::p2pX(13.0f, vm), gui::p2pY(6.f, vm),
                    &this->font, "Apply", gui::calcCharSize(vm),
                    sf::Color(70, 70, 70, 200),  sf::Color(250, 250, 250, 250),  sf::Color(20, 20, 20, 50),
                    sf::Color(100, 100, 100, 0),  sf::Color(150, 150, 150, 0),  sf::Color(20, 20, 20, 0)
                    );

  // Modes
  std::vector<std::string> modes_str;

  for(auto &i : this->modes) {
    modes_str.push_back(std::to_string(i.width) + 'x' + std::to_string(i.height));
  }

  // Dropdown list
  this->dropdownLists["RESOLUTION"] =
    new gui::DropDownList(gui::p2pX(42.f, vm), gui::p2pY(42.f, vm),
                          gui::p2pX(10.4f, vm), gui::p2pY(4.5f, vm),
                          font, modes_str.data(), modes_str.size());


  // Text
  this->optionsText.setFont(font);

  this->optionsText.setPosition(sf::Vector2f(gui::p2pX(5.2f, vm), gui::p2pY(41.7f, vm)));

  this->optionsText.setCharacterSize(gui::calcCharSize(vm, 70));
  this->optionsText.setFillColor(sf::Color(255, 255, 255, 200));

  this->optionsText.setString(
                              "TEST"
                              // "Resolution " + "\n\n" +
                              // "Fullscreen " + "\n\n" +
                              // "Vsync " + "\n\n" +
                              // "Antialiasing " + "\n\n"
                              );


}

void SettingsState::resetGui() {
  /**
     Clears the GUI elements and re-initialise the GUI


   */

  auto it = this->buttons.begin();
  for (it = this->buttons.begin(); it != this->buttons.end(); ++it) {
    delete it->second;
  }
  this->buttons.clear();

  auto it2 = this->dropdownLists.begin();
  for (it2 = this->dropdownLists.begin(); it2 != this->dropdownLists.end(); ++it2) {
    delete it2->second;
  }
  this->dropdownLists.clear();

  this->initGui();
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

    this->resetGui();
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
