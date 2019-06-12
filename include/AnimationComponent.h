#ifndef __ANIMATION_COMPONENT_H__
#define __ANIMATION_COMPONENT_H__

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include <map>
#include <string>
class AnimationComponent {

private:
  class Animation {
  public:
    // variables
    sf::Sprite& sprite;
    sf::Texture& textureSheet;
    float animationTimer;
    float timer;
    int width;
    int height;

    sf::IntRect startRect;
    sf::IntRect currentRect;
    sf::IntRect endRect;

    Animation(sf::Sprite& sprite, sf::Texture& textureSheet, float animationTimer, int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height)
      : sprite(sprite), textureSheet(textureSheet), animationTimer(animationTimer), width(width), height(height) {
      this->timer = 0.f;

      this->startRect = sf::IntRect(start_frame_x * width, start_frame_y * height, width, height);
      this->currentRect = this->startRect;
      this->endRect = sf::IntRect(frames_x * width, frames_y * height, width, height);

      this->sprite.setTexture(this->textureSheet, true);
      this->sprite.setTextureRect(this->startRect);
    }

    // functions
    void play(const float& dt) {
      // update timer
      this->timer += 100.f * dt;
      if(this->timer >= this->animationTimer) {
        // reset timer
        this->timer = 0.f;

        if(this->currentRect != this->endRect) {
          // Animate
          this->currentRect.left += this->width;

          //std::cout << "current_rect_left" << this->currentRect.left << std::endl;
        } else {
          // Reset
          this->currentRect.left = this->startRect.left;
        }

        this->sprite.setTextureRect( this->currentRect );

      }
    }

    void reset() {
      this->timer = 0.f;
      this->currentRect = this->startRect;
    }
  };

  sf::Sprite& sprite;
  sf::Texture& textureSheet;
  std::map<std::string, Animation*> animations;
  Animation* lastAnimation;

public:
  AnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet);
  virtual ~AnimationComponent();

  // functions
  void addAnimation(const std::string key,
                    float animation_timer,
                    int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height);

  void play(const std::string key, const float& dt);
};


#endif
