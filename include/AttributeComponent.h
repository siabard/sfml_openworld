#ifndef __ATTRIBUTECOMPONENT_H__
#define __ATTRIBUTECOMPONENT_H__

class AttributeComponent {

private:

public:

  // Leveling
  unsigned level;
  unsigned exp;
  unsigned expNext;
  unsigned attributePoints;

  // Attribute
  int vitality;
  int strength;
  int dexterity;
  int agility;
  int intelligence;

  // Stats
  int hp;
  int hpMax;
  int damageMin;
  int damageMax;
  int accuracy;
  int defence;
  int luck;

  // Constructor & Destructor
  AttributeComponent(unsigned level);
  virtual ~AttributeComponent();

  // Functions
  std::string debugPrint() const;

  void gainExp(const unsigned exp);
  void updateStats(const bool reset);
  void updateLevel();


  void update();
};

#endif
