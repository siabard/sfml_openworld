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

  float width = gui::p2pX(10.4f, this->vm);
  float height = gui::p2pY(1.9f, this->vm);
  float x = gui::p2pX(1.f, this->vm);
  float y = gui::p2pY(5.6f, this->vm);
  this->expBarMaxWidth = width;

  this->expBarBack.setSize(sf::Vector2f(width, height));
  this->expBarBack.setFillColor(sf::Color(50, 50, 50, 200));
  this->expBarBack.setPosition(x, y);

  this->expBarInner.setSize(sf::Vector2f(width, height));
  this->expBarInner.setFillColor(sf::Color(20, 20, 250, 200));
  this->expBarInner.setPosition(this->expBarBack.getPosition());

  this->expBarText.setFont(this->font);
  this->expBarText.setCharacterSize(gui::calcCharSize(this->vm, 200));
  this->expBarText.setPosition(this->expBarInner.getPosition().x + gui::p2pX(0.53f, this->vm),
                               this->expBarInner.getPosition().y + gui::p2pY(0.15f, this->vm)
                               );
}


void PlayerGUI::initHpBar() {

  this->hpBar = new gui::ProgressBar(1.f, 8.3, 10.4, 2.8, this->player->getAttributeComponent()->hpMax, this->vm, &this->font);

}

PlayerGUI::PlayerGUI(Player* player, sf::VideoMode& vm) : vm(vm) {
  this->player = player;

  this->initFont();
  this->initLevelBar();
  this->initEXPBar();
  this->initHpBar();
}

PlayerGUI::~PlayerGUI() {
  delete this->hpBar;

}

// functions
void PlayerGUI::updateLevelBar() {
  this->levelBarString =
    std::to_string(this->player->getAttributeComponent()->level);
  this->levelBarText.setString(this->levelBarString);
}


void PlayerGUI::updateEXPBar() {
  float percent =
    static_cast<float>(this->player->getAttributeComponent()->exp)
    / static_cast<float>(this->player->getAttributeComponent()->expNext);
  this->expBarInner.setSize(sf::Vector2f(static_cast<float>(std::floor(this->expBarMaxWidth * percent)), this->expBarInner.getSize().y));

  this->expBarString =
    std::to_string(this->player->getAttributeComponent()->exp)
    + " / "
    + std::to_string(this->player->getAttributeComponent()->expNext);
  this->expBarText.setString(this->expBarString);
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
  target.draw(this->expBarBack);
  target.draw(this->expBarInner);
  target.draw(this->expBarText);
}


void PlayerGUI::renderHpBar(sf::RenderTarget& target) {
  this->hpBar->render(target);
}

void PlayerGUI::render(sf::RenderTarget& target) {
  this->renderLevelBar(target);
  this->renderEXPBar(target);
  this->renderHpBar(target);
}
