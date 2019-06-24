#include "include/stdafx.h"
#include "include/EditorState.h"

// Initiaizlier Function
void EditorState::initKeybinds() {
  std::ifstream ifs("config/editorstate_keybinds.ini");
  if(ifs.is_open()) {
    std::string key = "";
    std::string key_binding = "";
    while(ifs >> key_binding >> key) {
      this->keybinds[key_binding] = this->supportedKeys->at(key);
    }
  } else {
    std::cout << "file not exist: config/editorstate_keybinds.ini" << std::endl;
  }
  ifs.close();
}


void EditorState::initPauseMenu() {
  this->pmenu = new PauseMenu(*this->window, this->font);

  this->pmenu->addButton("QUIT", 800.f, "Quit");

}


void EditorState::initBackground() {

}

void EditorState::initVariables() {
}


void EditorState::initFonts() {
  if(!this->font.loadFromFile("fonts/DroidSans.ttf")) {
    throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
  }

}

void EditorState::initButtons() {
}


EditorState::EditorState(sf::RenderWindow* window,  std::map<std::string, int>* supportedKeys, std::stack<State*>*  states) : State(window, supportedKeys, states) {
  this->initVariables();
  this->initBackground();
  this->initKeybinds();
  this->initFonts();
  this->initPauseMenu();
  this->initButtons();

}

EditorState::~EditorState() {

  for(auto it = this->buttons.begin(); it != this->buttons.end(); ++it) {
    if(it->second) {
      delete it->second;
    }
  }

  delete this->pmenu;

}

void EditorState::update(const float& dt) {
  this->updateMousePositions();
  this->updateInput(dt);
  this->updateKeytime(dt);

  if(!this->paused) {
    this->updateButtons();
  } else {
    this->pmenu->update(this->mousePosView);
    this->updatePauseMenuButtons();
  }


}

void EditorState::render(sf::RenderTarget* target) {
  if(!target)
    target = this->window;

  this->renderButtons(*target);

  this->map.render(*target);

  if(this->paused) {
    this->pmenu->render(*target);
  }

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

void EditorState::updateInput(const float& dt) {
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeytime()) {
    if(!this->paused)
      this->pauseState();
    else
      this->unpauseState();
  }
}

void EditorState::updatePauseMenuButtons() {
  if(this->pmenu->isButtonPressed("QUIT"))
    this->endState();


}


void EditorState::updateButtons() {

  /* update all the buttons in the state and hadle their functionality */

  for (auto &it : this->buttons) {
    it.second->update(this->mousePosView);
  }


}

void EditorState::renderButtons(sf::RenderTarget& target) {
  for (auto &it : this->buttons) {
    it.second->render(target);
  }

}
