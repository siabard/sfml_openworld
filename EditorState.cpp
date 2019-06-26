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
  this->textureRect = sf::IntRect(0, 0, static_cast<int>(this->stateData->gridSize), static_cast<int>(this->stateData->gridSize));

}


void EditorState::initFonts() {
  if(!this->font.loadFromFile("fonts/DroidSans.ttf")) {
    throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
  }

}

void EditorState::initText() {
  // REMOVE LATER!!
  this->cursorText.setFont(this->font);
  this->cursorText.setFillColor(sf::Color::White);
  this->cursorText.setCharacterSize(12);
  this->cursorText.setPosition(this->mousePosView.x, this->mousePosView.y - 50);

}

void EditorState::initButtons() {
}

void EditorState::initTileMap() {
  this->tileMap = new TileMap(this->stateData->gridSize, 10.f, 10.f);
}

EditorState::EditorState(StateData* state_data) : State(state_data) {
  this->initVariables();
  this->initBackground();
  this->initKeybinds();
  this->initFonts();
  this->initText();
  this->initPauseMenu();
  this->initButtons();
  this->initTileMap();
  this->initGui();

}

void EditorState::initGui() {
  this->selectorRect.setSize(sf::Vector2f(this->stateData->gridSize, this->stateData->gridSize));

  this->selectorRect.setFillColor(sf::Color(255, 255, 255, 150));
  this->selectorRect.setOutlineThickness(1.f);
  this->selectorRect.setOutlineColor(sf::Color::Green);
  this->selectorRect.setTexture(this->tileMap->getTileSheet());
  this->selectorRect.setTextureRect(this->textureRect);
}

EditorState::~EditorState() {

  for(auto it = this->buttons.begin(); it != this->buttons.end(); ++it) {
    if(it->second) {
      delete it->second;
    }
  }

  delete this->pmenu;

  delete this->tileMap;

}

void EditorState::updateGui() {
  this->selectorRect.setTextureRect(this->textureRect);
  this->selectorRect.setPosition(this->mousePosGrid.x * this->stateData->gridSize, this->mousePosGrid.y * this->stateData->gridSize);

  this->cursorText.setPosition(this->mousePosView.x, this->mousePosView.y - 50);
  std::stringstream ss;
  ss << this->mousePosView.x << " " << this->mousePosView.y << std::endl << this->textureRect.left << " " << this->textureRect.top;
  this->cursorText.setString(ss.str());
}

void EditorState::update(const float& dt) {
  this->updateMousePositions();
  this->updateInput(dt);
  this->updateKeytime(dt);

  if(!this->paused) {
    this->updateButtons();
    this->updateGui();
    this->updateEditorInput(dt);
  } else {
    this->pmenu->update(this->mousePosView);
    this->updatePauseMenuButtons();
  }


}

void EditorState::updateInput(const float& dt) {
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeytime()) {
    if(!this->paused)
      this->pauseState();
    else
      this->unpauseState();
  }
}

void EditorState::updateEditorInput(const float& dt) {

  // Add a Tile
  if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->getKeytime()) {
    this->tileMap->addTile(this->mousePosGrid.x, this->mousePosGrid.y, 0, this->textureRect);
  } else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->getKeytime()) {
    this->tileMap->removeTile(this->mousePosGrid.x, this->mousePosGrid.y, 0);
  }

  // Change texture
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && this->getKeytime()) {
    if(this->textureRect.left < 100) {
      this->textureRect.left += 100;
      std::cout << "RIGHT TEXTURE : " << this->textureRect.left << std::endl;
    }

  } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && this->getKeytime()) {
    if(this->textureRect.left > 0) {
      this->textureRect.left -= 100;
      std::cout << "LEFT TEXTURE : " << this->textureRect.left << std::endl;
    }
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

void EditorState::renderGui(sf::RenderTarget& target) {
  target.draw(this->selectorRect);
  target.draw(this->cursorText);

}

void EditorState::renderButtons(sf::RenderTarget& target) {
  for (auto &it : this->buttons) {
    it.second->render(target);
  }

}


void EditorState::render(sf::RenderTarget* target) {
  if(!target)
    target = this->window;


  this->tileMap->render(*target);
  this->renderButtons(*target);
  this->renderGui(*target);
  target->draw(this->cursorText);

  if(this->paused) {
    this->pmenu->render(*target);
  }




}
