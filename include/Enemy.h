#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "Entity.h"
#include "EnemySpawnerTile.h"

class Enemy :
  public Entity {

private:
  // Variables
  unsigned gainExp;

  //  EnemySpawner& enemySpawner;

  // initializer functions
  virtual void initVariables();
  virtual void initAnimation();

protected:
  sf::RectangleShape hpBar;

public:

  Enemy();
  virtual ~Enemy();


  // function
  virtual void generateAttributes(const unsigned level);
  virtual void loseHP(const int hp);
  virtual const bool isDead() const;

  virtual const unsigned getGainExp() const;
  virtual const AttributeComponent* getAttributeComp();
  virtual void updateAnimation(const float& dt) = 0;
  virtual void update(const float& dt, sf::Vector2f& mouse_pos_view) = 0;
  virtual void render(sf::RenderTarget& target, sf::Shader* shader = nullptr, const sf::Vector2f light_position = sf::Vector2f(), const bool show_hitbox = false) = 0;
};

#endif
