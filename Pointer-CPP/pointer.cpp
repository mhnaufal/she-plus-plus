#include "pointer.h"
#include <iostream>
#include <memory>
#include <utility>

void basic_pointer() {
  int *null_ptr; // initialize a pointer using "*" next to variable name
  std::cout << null_ptr << std::endl;

  int level = 1;
  null_ptr = (int *)level; // WARN: we can set null_ptr to a non memory address
                           // value, but it's a stupid things to do, however at
                           // least you know that we can do this
  std::cout << null_ptr << std::endl;

  null_ptr = &level; // set the variable null_ptr point to a memory address
  std::cout << null_ptr << std::endl;

  int &ref =
      *null_ptr; // "*" in null_ptr means we dereference memory address pointed
                 // by null_ptr, and we will get the original value back
                 // "&" reference to another variable. Reference it's just a
                 // way to give a memory address/variable another name
  std::cout << null_ptr << " " << ref << std::endl;

  int &ref2 = level;
  level = 2;
  std::cout << null_ptr << " " << ref2 << std::endl;

  // reference need to point to an EXISTING variable
  // it means that we cant create a new reference variable and put a new value
  // on it. Reference doesn't have actual memory, because IT IS JUST A REFERENCE
  // int &ref2 = 2; // ERROR: lvalue of type int& with rvalue of type int

  int score = 100;
  increase(score);
  std::cout << "score: " << score << std::endl;
}

void increase(int &score) { score++; }

/* It is not directly correlate with pointer (it's class and object thing), but
 * put it inside pointer part is the correct thing to do */
class Pokemon {
private:
  std::string name_;

public:
  Pokemon() : name_("Pocketol") {}
  explicit Pokemon(std::string name) : name_(std::move(name)) {}
  [[nodiscard]] const std::string &getName() const { return name_; }
};

void play_pokemon() {
  /* Allocate object in static world
   * no need to manually delete because it will automatically get deleted when
   * goes out of scope, object can only live inside the scope */
  {
    Pokemon pk1;
    std::cout << "pk1 name: " << pk1.getName() << std::endl;
  }
  //  std::cout << "pk1 name: " << pk1.getName() << std::endl; // ERROR: beside
  //  the variable pk1 is undeclared, the
  // object in static world is already dead too

  /* Allocate object in heap world
   * need to manually call delete, object can live even already out of scope */
  auto *pk2 = new Pokemon("Fire Blast");
  std::cout << "pk2 name: " << pk2->getName() << std::endl;
  delete pk2;

  /* The 'new' keyword
   * can be used in any data type, not just for classes
   * allocation done on the heap
   * it will find X bytes of memory and return a pointer to it */
  int *num = new int; // allocate 4 bytes of memory
  std::cout << num << std::endl;
  delete num;

  // if we allocate with [], so we need also define [] when we want to delete it
  int *nums = new int[25];
  delete[] nums;

  std::cout << std::endl;
}

class Sprite {
private:
  int pos_x, pos_y;

public:
  void set_initial_position(int pos_x, int pos_y) {
    // pos_x = pos_x; // we can't do this in C++
    // Sprite* const s = this; // what actually this is
    this->pos_x = pos_x;
    this->pos_y = pos_y;
  }

  int get_pos_x() {
    // const Sprite* s = this; // what actually this is
    return this->pos_x;
  }
};

class Entity {
public:
  Entity() { std::cout << "Entity created!" << std::endl; }
  ~Entity() { std::cout << "Entity destroyed!" << std::endl; }
  void PrintEntity() { std::cout << "entity: " << this << std::endl; }
};

void smartPointer() {
  {
    /* unique pointer */
    std::unique_ptr<Entity> entity1 = std::make_unique<Entity>();
    std::cout << "unique pointer: ";
    entity1->PrintEntity();
    // we can't copy unique_pointer
    // std::unique_ptr<Entity> entity2 = entity1;

    std::cout << std::endl;

    /* shared pointer */
    {
      std::shared_ptr<Entity> entity3;
      {
        std::shared_ptr<Entity> entity2 = std::make_shared<Entity>();
        entity3 = entity2;
        std::cout << "shared pointer 2: " << entity2.use_count() << std::endl;
      }
      // entity2 get out of scope, so the reference count decrease by 1
      std::cout << "shared pointer 3: " << entity3.use_count() << std::endl;
    }

    std::cout << std::endl;

    /* weak pointer */
    {
      std::shared_ptr<Entity> entity2 = std::make_shared<Entity>();
      {
        std::weak_ptr<Entity> entity4 = entity2;
        std::cout << "weak pointer 4: " << entity4.use_count() << std::endl;
        std::cout << "shared pointer 2: " << entity2.use_count()
                  << std::endl; // reference count doesn't get increased
      }
      std::cout << "shared pointer 2: " << entity2.use_count() << std::endl;
    }
  }
}