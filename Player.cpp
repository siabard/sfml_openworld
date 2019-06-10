#include "include/Player.h"

// Initializer Function
void Player::initVariables() {

}
void Player::initComponents() {
  this->createMovementComponent(100.f, 5.f, 3.f);
}


Player::Player(float x, float y, sf::Texture& texture) {
  this->initVariables();
  this->initComponents();
  this->setTexture(texture);
  this->setPosition(x, y);
}

Player::~Player() {}
