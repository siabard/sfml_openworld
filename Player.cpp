#include "include/Player.h"

// Initializer Function
void Player::initVariables() {

}
void Player::initComponents() {
}


Player::Player(float x, float y, sf::Texture* texture) {
  this->initVariables();
  this->initComponents();
  this->createSprite(texture);
  this->setPosition(x, y);
}

Player::~Player() {}
