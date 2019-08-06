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
  const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;
  this->pmenu = new PauseMenu(vm, this->font);

  this->pmenu->addButton("QUIT", gui::p2pY(74.f, vm), gui::p2pX(13.f, vm), gui::p2pY(6.f, vm), gui::calcCharSize(vm), "Quit");
  this->pmenu->addButton("SAVE", gui::p2pY(46.f, vm), gui::p2pX(13.f, vm), gui::p2pY(6.f, vm), gui::calcCharSize(vm), "Save");
  this->pmenu->addButton("LOAD", gui::p2pY(37.f, vm), gui::p2pX(13.f, vm), gui::p2pY(6.f, vm), gui::calcCharSize(vm), "Load");

}



void EditorState::initVariables() {
  this->cameraSpeed = 1000.f;
}

void EditorState::initEditorStateData() {
  this->editorStateData.view = &this->view;
  this->editorStateData.font = &this->font;
  this->editorStateData.keytime = &this->keytime;
  this->editorStateData.keytimeMax = &this->keytimeMax;
  this->editorStateData.keybinds = &this->keybinds;
  this->editorStateData.mousePosScreen = &this->mousePosScreen;
  this->editorStateData.mousePosWindow = &this->mousePosWindow;
  this->editorStateData.mousePosView = &this->mousePosView;
  this->editorStateData.mousePosGrid = &this->mousePosGrid;

}

void EditorState::initGui() {}

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

void EditorState::initButtons() {

}

void EditorState::initTileMap() {
  this->tileMap = new TileMap(this->stateData->gridSize, 100, 100, "Resource/images/tiles/tilesheet3.png");
}

void EditorState::initModes() {
  this->modes.push_back(new DefaultEditorMode(this->stateData, this->tileMap, &this->editorStateData));
  this->modes.push_back(new EnemyEditorMode(this->stateData, this->tileMap, &this->editorStateData));

  this->activeMode = EditorModes::DEFAULT_EDITOR_MODE;
}

EditorState::EditorState(StateData* state_data) : State(state_data) {
  this->initVariables();
  this->initEditorStateData();
  this->initView();
  this->initKeybinds();
  this->initFonts();
  this->initPauseMenu();
  this->initButtons();
  this->initTileMap();
  this->initModes();

}

EditorState::~EditorState() {

  for(auto it = this->buttons.begin(); it != this->buttons.end(); ++it) {
    if(it->second) {
      delete it->second;
    }
  }

  delete this->pmenu;

  delete this->tileMap;

  for(size_t i = 0; i < this->modes.size(); i++) {
    delete this->modes[i];
  }

}


void EditorState::updateModes(const float& dt) {
  this->modes[this->activeMode]->update(dt);
}

void EditorState::updateGui(const float& dt) {


}

void EditorState::update(const float& dt) {
  this->updateMousePositions(&this->view);
  this->updateInput(dt);
  this->updateKeytime(dt);

  if(!this->paused) {
    this->updateButtons();
    this->updateGui(dt);
    this->updateEditorInput(dt);
    this->updateModes(dt);
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

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MODE_UP")))) {
    if(this->activeMode < this->modes.size() - 1) {
      this->activeMode++;
    } else {
      std::cout << "ERROR::EDITORSTATE::CANNOT CHANGE MODE UP!" << std::endl;
    }
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MODE_DOWN")))) {
    if (this->activeMode > 0) {
      this->activeMode--;
    } else {
      std::cout << "ERROR::EDITORSTATE::CANNOT CHANGE MODE DOWN!" << std::endl;
    }
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


void EditorState::renderModes(sf::RenderTarget& target) {

  this->modes[this->activeMode]->render(target);
}


void EditorState::renderGui(sf::RenderTarget& target) {

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
  this->tileMap->render(*target, this->mousePosGrid, nullptr, sf::Vector2f(), true);
  this->tileMap->renderDeferred(*target);

  target->setView(this->window->getDefaultView());
  this->renderButtons(*target);
  this->renderGui(*target);
  this->renderModes(*target);
  //target->draw(this->cursorText);

  if(this->paused) {
    target->setView(this->window->getDefaultView());
    this->pmenu->render(*target);
  }




}
