#ifndef __REGULARTILE_H__
#define __REGULARTILE_H__

#include "Tile.h"
class RegularTile
  : public Tile {
private:

protected:

public:
  RegularTile(short type, int x, int y, float gridSizeF,
               const sf::Texture& texture, const sf::IntRect& rect,
               bool collision = false);
  virtual ~RegularTile();

  // accessors
  virtual const std::string getAsString() const;

  // functions
  virtual void update();
  virtual void render(sf::RenderTarget& target, sf::Shader* shader = nullptr, const sf::Vector2f playerPosition = sf::Vector2f());
};
#endif
