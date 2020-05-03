#include "include/stdafx.h"
#include "include/PlayerGUI.h"
#include "include/Gui.h"

void PlayerGUI::initFont() {
  this->font.loadFromFile("fonts/DroidSans.ttf");
}

void PlayerGUI::initLevelBar() {
  float width = gui::p2pX(1.6f, this->vm);
  float height = gui::p2pY(2.8f, this->vm);
  float x = gui::p2pX(1.f, this->vm);
  float y = gui::p2pY(1.9f, this->vm);

  this->levelBarBack.setSize(sf::Vector2f(width, height));
  this->levelBarBack.setFillColor(sf::Color(50, 50, 50, 200));
  this->levelBarBack.setPosition(x, y);

  this->levelBarText.setFont(this->font);
  this->levelBarText.setCharacterSize(gui::calcCharSize(this->vm, 150));
  this->levelBarText.setPosition(this->levelBarBack.getPosition().x + gui::p2pX(0.53f, this->vm),
                                 this->levelBarBack.getPosition().y + gui::p2pY(0.5f, this->vm));
}

void PlayerGUI::initEXPBar() {

  this->expBar = new gui::ProgressBar(1.f, 5.6, 10.4, 1.9f, this->player->getAttributeComponent()->expNext,
                                      sf::Color::Blue,
                                      202,
                                      this->vm, &this->font);

}


void PlayerGUI::initHpBar() {

  this->hpBar = new gui::ProgressBar(1.f, 8.3f, 10.4f, 2.8f, this->player->getAttributeComponent()->hpMax,
                                     sf::Color::Red,
                                     180,
                                     this->vm, &this->font);

}

void PlayerGUI::initPlayerTabs(sf::VideoMode& vm, sf::Font& font, Player& player) {
  this->playerTabs = new PlayerGUITabs(vm, font, player);
}

PlayerGUI::PlayerGUI(Player* player, sf::VideoMode& vm) : vm(vm) {
  this->player = player;

  this->initFont();
  this->initLevelBar();
  this->initEXPBar();
  this->initHpBar();

  // Tabs
  this->initPlayerTabs(this->vm, this->font, *this->player);
}

PlayerGUI::~PlayerGUI() {
  delete this->hpBar;
  delete this->expBar;

}

// functions
void PlayerGUI::updateLevelBar() {
  this->levelBarString =
    std::to_string(this->player->getAttributeComponent()->level);
  this->levelBarText.setString(this->levelBarString);
}


void PlayerGUI::updateEXPBar() {
  this->expBar->update(this->player->getAttributeComponent()->exp);
}


void PlayerGUI::updateHpBar() {
  this->hpBar->update(this->player->getAttributeComponent()->hp);

}


void PlayerGUI::update(const float& dt) {
  this->updateLevelBar();
  this->updateEXPBar();
  this->updateHpBar();

}


void PlayerGUI::renderLevelBar(sf::RenderTarget& target) {
  target.draw(this->levelBarBack);
  target.draw(this->levelBarText);
}

void PlayerGUI::renderEXPBar(sf::RenderTarget& target) {
  this->expBar->render(target);
}


void PlayerGUI::renderHpBar(sf::RenderTarget& target) {
  this->hpBar->render(target);
}


void PlayerGUI::render(sf::RenderTarget& target) {
  this->renderLevelBar(target);
  this->renderEXPBar(target);
  this->renderHpBar(target);

}
