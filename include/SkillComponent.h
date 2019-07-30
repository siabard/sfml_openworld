#ifndef __SKILLCOMPONENT_H__
#define __SKILLCOMPONENT_H__

#include <map>
#include <vector>

enum SKILLS {
             HEALTH = 0, ATTACK, ACCURACY, ENDURANCE
};

class SkillComponent {

private:
  class Skill {
  private:
    SKILLS type;
    int level;
    int levelCap;
    int exp;
    int expNext;

  public:

    Skill(const SKILLS type) {
      this->type = type;
      this->level = 1;
      this->levelCap = 99;
      this->exp = 0;
      this->expNext = 100;
    }

    ~Skill() {}

    // accessors
    inline const SKILLS& getType() const {
      return this->type;
    }

    inline const int& getLevel() const {
      return this->level;
    }

    inline const int& getExp() const {
      return this->exp;
    }

    inline const int& getExpNext() const {
      return this->expNext;
    }

    // modifiers
    void setLevel(const int level) {
      this->level = level;
    }

    void setLevelCap(const int levelCap) {
      this->levelCap = levelCap;
    }

    // functions
    void gainExp(const int exp) {
      this->exp += exp;
      this->updateLevel();
    }

    void loseExp(const int exp) {
      this->exp -= exp;
    }

    void updateLevel(const bool up = true) {
      /*
       * Increase or Decrease the level of the skill depending on if there is an a deficit in the exp or not.
       */

      if(up) {
        while(this->exp >= this->expNext) {
          if(this->level < this->levelCap) {
            this->level++;
            this->exp -= this->expNext;
            this->expNext = static_cast<int>(std::pow(this->level, 2)) + this->level * 10 + this->level * 2;
          } else {
            break;
          }
        }
      } else {
        while(this->exp < 0) {
          if(this->level > 0) {
            this->level--;
            this->exp += this->expNext;
            this->expNext = static_cast<int>(std::pow(this->level, 2)) + this->level * 10 + this->level * 2;
          }
        }
      }
    }


    void update() {

    }

  };

  std::vector<Skill> skills;
public:
  SkillComponent();
  virtual ~SkillComponent();

  const int getSkill(const SKILLS skill) const;
  void gainExp(const SKILLS skill, const int exp);
};

#endif
