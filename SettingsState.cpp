#include "include/SettingsState.h"

SettingsState::SettingsState(sf::RenderWindow* window,  std::map<std::string, int>* supportedKeys, std::stack<State*>*  states) : State(window, supportedKeys, states) {
  this->initVariables();
  this->initBackground();
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


void SettingsState::initBackground() {
  this->background.setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y)));

  if(!this->backgroundTexture.loadFromFile("Resource/images/backgrounds/bg1.png")) {

    throw("ERROR::MAINMENUSTATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE");
  }
  this->background.setTexture(&this->backgroundTexture);

}

void SettingsState::initVariables() {}



void SettingsState::initFonts() {
  if(!this->font.loadFromFile("fonts/DroidSans.ttf")) {
    throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
  }

}

void SettingsState::initGui() {
  this->buttons["EXIT_STATE"] = new gui::Button(900.f, 880.f, 250.f, 50.f, &this->font, "Back", 50,
                                                   sf::Color(70, 70, 70, 200),  sf::Color(250, 250, 250, 250),  sf::Color(20, 20, 20, 50),
                                                   sf::Color(70, 70, 70, 0),  sf::Color(150, 150, 150, 0),  sf::Color(20, 20, 20, 0)
                                                   );

  std::string li[] = {
                      "1920x1080", "800x600", "640x480"
  };

  this->dropdownLists["RESOLUTION"] = new gui::DropDownList(800, 450, 200, 50, font, li, 3, 0);

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
    it.second->update(this->mousePosView);
  }


  // Button functionality
  // Quit the Game
  if(this->buttons["EXIT_STATE"]->isPressed()) {
    this->endState();
  }

  // Dropdown lists
  for (auto &it : this->dropdownLists) {
    it.second->update(this->mousePosView, dt);
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
