#ifndef __INVENTORY_H__
#define __INVENTORY_H__

#include "Item.h"

class Inventory {
private:
  Item** itemArray;
  unsigned nrOfItems;
  unsigned capacity;

  // private functions
  void initialize();
  void expand();
  void nullify(const unsigned from = 0);
  void freeMemory();

public:
  Inventory(unsigned capacity);
  virtual ~Inventory();

  // accessors
  const unsigned& size() const;
  const unsigned& maxSize() const;

  // modifiers


  // functions
  void clear();
  const bool empty() const;

  const bool add(Item* item);
  const bool remove(const unsigned index);

  const bool saveToFile(const std::string fileName);
  const bool loadFromFile(const std::string fileName);
};

#endif
