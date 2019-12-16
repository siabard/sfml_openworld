#ifndef __ITEM_H__
#define __ITEM_H__

enum ItemTypes {IT_DEFAULT = 0, ITRANGEDWEAPON, ITMELEEWEAPON};
enum ItemRarities {COMMON = 0, UNCOMMON, RARE, EPIC, LEGENDARY, MYTHIC};
class Item {
private:
  void initVariables();

protected:
  // variables
  short unsigned type;
  unsigned value;


public:
  Item(unsigned value);
  virtual ~Item();

  // functions
  virtual Item* clone() = 0;
};

#endif
