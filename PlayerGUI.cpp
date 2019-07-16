#include "include/stdafx.h"
#include "include/PlayerGUI.h"

void PlayerGUI::initFont() {
  this->font.loadFromFile("fonts/DroidSans.ttf");
}

void PlayerGUI::initHpBar() {

  float width = 300.f;
  float height = 50.f;
  float x = 20.f;
  float y = 20.f;
  this->hpBarMaxWidth = width;

  this->hpBarText.setFont(this->font);

  this->hpBarBack.setSize(sf::Vector2f(width, height));
  this->hpBarBack.setFillColor(sf::Color(50, 50, 50, 200));
  this->hpBarBack.setPosition(x, y);

  this->hpBarInner.setSize(sf::Vector2f(width, height));
  this->hpBarInner.setFillColor(sf::Color(250, 50, 50, 200));
  this->hpBarInner.setPosition(this->hpBarBack.getPosition());

  this->hpBarText.setPosition(this->hpBarInner.getPosition().x , this->hpBarInner.getPosition().y + 5.f );
}

PlayerGUI::PlayerGUI(Player* player) {
  this->player = player;

  this->initFont();
  this->initHpBar();
}

PlayerGUI::~PlayerGUI() {

}

// functions
void PlayerGUI::updateHpBar() {
  float percent =
    static_cast<float>(this->player->getAttributeComponent()->hp)
    / static_cast<float>(this->player->getAttributeComponent()->hpMax);
  this->hpBarInner.setSize(sf::Vector2f(static_cast<float>(std::floor(this->hpBarMaxWidth * percent)), this->hpBarInner.getSize().y));

  this->hpBarString =
    std::to_string(this->player->getAttributeComponent()->hp)
    + " / "
    + std::to_string(this->player->getAttributeComponent()->hpMax);
  this->hpBarText.setString(this->hpBarString);
}

void PlayerGUI::update(const float& dt) {
  this->updateHpBar();
}

void PlayerGUI::renderHpBar(sf::RenderTarget& target) {
  target.draw(this->hpBarBack);
  target.draw(this->hpBarInner);
  target.draw(this->hpBarText);
}

void PlayerGUI::render(sf::RenderTarget& target) {
  this->renderHpBar(target);
}
