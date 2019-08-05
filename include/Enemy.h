#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "Entity.h"
#include "EnemySpawner.h"

class Enemy :
  public Entity {

private:
  // Variables
  bool attacking;
  //  EnemySpawner& enemySpawner;

  // initializer functions
  void initVariables();
  void initAnimation();

public:

  Enemy(float x, float y, sf::Texture& texture);
  virtual ~Enemy();

  // function
  void updateAnimation(const float& dt);
  void update(const float& dt, sf::Vector2f& mouse_pos_view);
  void render(sf::RenderTarget& target, sf::Shader* shader = nullptr, const sf::Vector2f light_position = sf::Vector2f(), const bool show_hitbox = false);
};

#endif
