#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

class Entity {
 private:

 protected:
  sf::RectangleShape shape; // place holder
  float movementSpeed;

 public:
  Entity();
  virtual ~Entity();

  // functions
  virtual void move(const float& dt, const float, const float);
  virtual void update(const float& dt);
  virtual void render(sf::RenderTarget* target);
};

#endif
