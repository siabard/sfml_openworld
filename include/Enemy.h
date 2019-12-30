#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "Entity.h"
#include "EnemySpawnerTile.h"

class Enemy :
  public Entity {

private:
  // Variables

  //  EnemySpawner& enemySpawner;

  // initializer functions
  virtual void initVariables() = 0;
  virtual void initAnimation() = 0;

public:

  Enemy();
  virtual ~Enemy();


  // function

  virtual void loseHP(const int hp);
  virtual const AttributeComponent* getAttributeComp();
  virtual void updateAnimation(const float& dt) = 0;
  virtual void update(const float& dt, sf::Vector2f& mouse_pos_view) = 0;
  virtual void render(sf::RenderTarget& target, sf::Shader* shader = nullptr, const sf::Vector2f light_position = sf::Vector2f(), const bool show_hitbox = false) = 0;
};

#endif
