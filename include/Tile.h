#ifndef __TILE_H__
#define __TILE_H__

class Tile {
private:

protected:
  sf::RectangleShape shape;

public:
  Tile();
  Tile(float x, float y, float gridSizeF, const sf::Texture& texture, const sf::IntRect& rect);
  virtual ~Tile();

  // functions
  void update();
  void render(sf::RenderTarget& target);
};


#endif
