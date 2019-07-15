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
  this->pmenu->addButton("SAVE", 500.f, "Save");
  this->pmenu->addButton("LOAD", 400.f, "Load");

}


void EditorState::initBackground() {

}

void EditorState::initVariables() {
  this->textureRect = sf::IntRect(0, 0, static_cast<int>(this->stateData->gridSize), static_cast<int>(this->stateData->gridSize));
  this->collision = false;
  this->type = TileTypes::DEFAULT;
  this->cameraSpeed = 100.f;
  this->layer = 0;

}

void EditorState::initView() {
  this->view.setSize(sf::Vector2f(
                                  static_cast<float>(this->stateData->gfxSettings->resolution.width),
                                  static_cast<float>(this->stateData->gfxSettings->resolution.height))
                     );
  this->view.setCenter(
                       static_cast<float>(this->stateData->gfxSettings->resolution.width) / 2.f,
                       static_cast<float>(this->stateData->gfxSettings->resolution.height) / 2.f
                       );
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
  this->cursorText.setPosition(this->mousePosView.x, this->mousePosView.y);

}

void EditorState::initButtons() {

}

void EditorState::initTileMap() {
  this->tileMap = new TileMap(this->stateData->gridSize, 100, 100, "Resource/images/tiles/tilesheet1.png");
}

EditorState::EditorState(StateData* state_data) : State(state_data) {
  this->initVariables();
  this->initView();
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
  this->sidebar.setSize(sf::Vector2f(80.f, static_cast<float>(this->stateData->gfxSettings->resolution.height)));
  this->sidebar.setFillColor(sf::Color(50, 50, 50, 100));
  this->sidebar.setOutlineColor(sf::Color(200, 200, 200, 150));
  this->sidebar.setOutlineThickness(1.f);

  this->selectorRect.setSize(sf::Vector2f(this->stateData->gridSize, this->stateData->gridSize));

  this->selectorRect.setFillColor(sf::Color(255, 255, 255, 150));
  this->selectorRect.setOutlineThickness(1.f);
  this->selectorRect.setOutlineColor(sf::Color::Green);
  this->selectorRect.setTexture(this->tileMap->getTileSheet());
  this->selectorRect.setTextureRect(this->textureRect);

  this->textureSelector = new gui::TextureSelector(20.f, 20.f, 800.f, 500.f,
                                                   this->stateData->gridSize,
                                                   this->tileMap->getTileSheet(),
                                                   this->font, "TS");


}

EditorState::~EditorState() {

  for(auto it = this->buttons.begin(); it != this->buttons.end(); ++it) {
    if(it->second) {
      delete it->second;
    }
  }

  delete this->pmenu;

  delete this->tileMap;

  delete this->textureSelector;

}

void EditorState::updateGui(const float& dt) {
  this->textureSelector->update(this->mousePosWindow, dt);

  if(!this->textureSelector->getActive()) {
    this->selectorRect.setTextureRect(this->textureRect);
    this->selectorRect.setPosition(this->mousePosGrid.x * this->stateData->gridSize, this->mousePosGrid.y * this->stateData->gridSize);
  }

  this->cursorText.setPosition(this->mousePosView.x + 100, this->mousePosView.y - 50);
  std::stringstream ss;
  ss
    << this->mousePosView.x << " " << this->mousePosView.y << std::endl
    << this->mousePosGrid.x << " " << this->mousePosGrid.y << std::endl
    << this->textureRect.left << " " << this->textureRect.top << std::endl
    << "Collisition: " << this->collision << std::endl
    << "Type: "  << this->type << std::endl
    << "tiles: "  << this->tileMap->getLayerSize(this->mousePosGrid.x, this->mousePosGrid.y, this->layer) << std::endl
    ;
  this->cursorText.setString(ss.str());

}

void EditorState::update(const float& dt) {
  this->updateMousePositions(&this->view);
  this->updateInput(dt);
  this->updateKeytime(dt);

  if(!this->paused) {
    this->updateButtons();
    this->updateGui(dt);
    this->updateEditorInput(dt);
  } else {
    this->pmenu->update(this->mousePosWindow);
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

  // Move view
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_UP")))) {
    this->view.move(0.f, -this->cameraSpeed * dt);
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_DOWN")))) {
    this->view.move(0.f, this->cameraSpeed * dt);
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_LEFT")))) {
    this->view.move(-this->cameraSpeed * dt, 0.f);
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_RIGHT")))) {
    this->view.move(this->cameraSpeed * dt, 0.f);
  }


  // Add a Tile
  if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->getKeytime()) {
    if(!this->sidebar.getGlobalBounds().contains(sf::Vector2f(this->mousePosWindow))) {
      if(!this->textureSelector->getActive()) {
        this->tileMap->addTile(this->mousePosGrid.x, this->mousePosGrid.y, 0, this->textureRect, this->collision, this->type);
      } else {
        this->textureRect = this->textureSelector->getTextureRect();
      }
    }
  } else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->getKeytime()) {
    if(!this->sidebar.getGlobalBounds().contains(sf::Vector2f(this->mousePosWindow))) {
      if(!this->textureSelector->getActive() )  {
        this->tileMap->removeTile(this->mousePosGrid.x, this->mousePosGrid.y, 0);
      }
    }
  }

  // toggle collision
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("TOGGLE_COLLISION"))) && this->getKeytime()) {
    this->collision = !this->collision;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("INCREASE_TYPE"))) && this->getKeytime()) {

    // toggle Type
    if (this->type < TileTypes::LIMIT)
      this->type++;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("DECREASE_TYPE"))) && this->getKeytime()) {
    if(this->type > TileTypes::DEFAULT)
      this->type--;
  }

}

void EditorState::updatePauseMenuButtons() {
  if(this->pmenu->isButtonPressed("QUIT"))
    this->endState();

  if(this->pmenu->isButtonPressed("SAVE"))
    this->tileMap->saveToFile("text.slmp");


  if(this->pmenu->isButtonPressed("LOAD"))
    this->tileMap->loadFromFile("text.slmp");

}


void EditorState::updateButtons() {

  /* update all the buttons in the state and hadle their functionality */

  for (auto &it : this->buttons) {
    it.second->update(this->mousePosWindow);
  }


}

void EditorState::renderGui(sf::RenderTarget& target) {

  if(!this->textureSelector->getActive()) {
    target.setView(this->view);
    target.draw(this->selectorRect);
  }

  target.setView(this->window->getDefaultView());
  this->textureSelector->render(target);
  target.draw(this->sidebar);

  target.setView(this->view);
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

  target->setView(this->view);
  this->tileMap->render(*target, this->mousePosGrid);
  this->tileMap->renderDeferred(*target);

  target->setView(this->window->getDefaultView());
  this->renderButtons(*target);
  this->renderGui(*target);
  //target->draw(this->cursorText);

  if(this->paused) {
    target->setView(this->window->getDefaultView());
    this->pmenu->render(*target);
  }




}
