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
    bool done;

    int width;
    int height;

    sf::IntRect startRect;
    sf::IntRect currentRect;
    sf::IntRect endRect;

    Animation(sf::Sprite& sprite, sf::Texture& textureSheet, float animationTimer, int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height)
      : sprite(sprite), textureSheet(textureSheet), animationTimer(animationTimer), timer(0.f), done(false), width(width), height(height) {

      this->startRect = sf::IntRect(start_frame_x * width, start_frame_y * height, width, height);
      this->currentRect = this->startRect;
      this->endRect = sf::IntRect(frames_x * width, frames_y * height, width, height);

      this->sprite.setTexture(this->textureSheet, true);
      this->sprite.setTextureRect(this->startRect);
    }

    // Accessors
    const bool& isDone() const {
      return this->done;
    }

    // functions
    const bool& play(const float& dt) {
      this->done = false;
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
          this->done = true;
        }

        this->sprite.setTextureRect( this->currentRect );

      }

      return this->done;
    }


    const bool& play(const float& dt, float mod_percent) {
      this->done = false;
      // update timer
      if(mod_percent < 0.5f)
        mod_percent = 0.5f;

      this->timer += mod_percent * 100.f * dt;
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
          this->done = true;
        }

        this->sprite.setTextureRect( this->currentRect );

      }

      return this->done;
    }

    void reset() {
      this->timer = this->animationTimer;
      this->currentRect = this->startRect;
    }
  };

  sf::Sprite& sprite;
  sf::Texture& textureSheet;
  std::map<std::string, Animation*> animations;
  Animation* lastAnimation;
  Animation* priorityAnimation;

public:
  AnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet);
  virtual ~AnimationComponent();

  // Accessors
  const bool& isDone(const std::string key);

  // functions
  void addAnimation(const std::string key,
                    float animation_timer,
                    int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height);

  const bool& play(const std::string key, const float& dt, const bool priority = false);
  const bool&  play(const std::string key, const float& dt, const float& modifier, const float& modifier_max, const bool priority = false);
};


#endif
