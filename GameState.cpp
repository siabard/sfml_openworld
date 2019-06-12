#include "include/GameState.h"

// Initiaizlier function
void GameState::initKeybinds() {
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

void GameState::initTextures() {
  if(!this->textures["PLAYER_SHEET"].loadFromFile("Resource/images/sprites/player/player_sheet.png")) {
    throw "GAMESTATE::PLAYER_SHEET::CANNOT_LOAD_PLAYER_SHEET";
  }

}

void GameState::initPlayers() {
  this->player = new Player(0, 0, this->textures["PLAYER_SHEET"]);

}

// Constructor
GameState::GameState(sf::RenderWindow* window,  std::map<std::string, int>* supportedKeys, std::stack<State*>* states) : State(window, supportedKeys, states) {
  this->initKeybinds();
  this->initTextures();
  this->initPlayers();
}

GameState::~GameState() {
  if(this->player) {
    delete this->player;
  }
}

void GameState::update(const float& dt) {
  this->updateInput(dt);
  this->player->update(dt);
}

void GameState::render(sf::RenderTarget* target) {
  if(!target)
    target = this->window;

  this->player->render(target);
}

void GameState::updateInput(const float& dt) {
  // Update player input
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
    this->player->move(-1.f, 0.f, dt);

  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
    this->player->move(1.f, 0.f, dt);

  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
    this->player->move(0.f, -1.f, dt);

  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
    this->player->move(0.f, 1.f, dt);

  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))))
    this->endState();
}
