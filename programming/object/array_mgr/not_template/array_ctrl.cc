#include <iostream>

#include "array_ctrl.h"
#include "array_itr.h"

namespace marsdb {
  ArrayCtrl::ArrayCtrl() {
    initial_array = new ArrayMgr(MAX_ELEMENTS);
  }

  void ArrayCtrl::run() {
    int choice = menu();
    while (choice != EXIT) {
      switch(choice) {
        case ADD:
          add();
          break;
        case DELETE:
          remove();
          break;
        case RETRIEVE:
          retrieve();
          break;
        case FIND:
          find();
          break;
        case LIST:
          list();
          break;
        case SIZE:
          size();
          break;
      }
      choice = menu();
    }
  }

  int ArrayCtrl::menu() {
    int choice;
    std::cout << "\nYou can: ";
    std::cout << "\n 1. Add an item.";
    std::cout << "\n 2. Delete an item.";
    std::cout << "\n 3. Retrieve an item by its position in the structure.";
    std::cout << "\n 4. Find ordinal position of element.";
    std::cout << "\n 5. List all items.";
    std::cout << "\n 6. Get size of structure.";
    std::cout << "\n 9. Exit";
    std::cout << "\n\nChoice.";
    std::cin >> choice;
    return choice;
  }

  void ArrayCtrl::add() {
    int value;
    std::cout << "\nEnter a nre value: ";
    std::cin >> value;
    bool result = initial_array->AddElement(value);
    if (result) {
      std::cout << "\nElement address successfully." << std::endl;
    } else {
      std::cout << "\nCouldn't add an because ";
      std::cout << "the array is full." << std::endl;
    }
  }

  void ArrayCtrl::remove() {
    int pos;
    std::cout << "\nEnter the position to delete: ";
    std::cin >> pos;
    bool result = initial_array->DeleteElement(pos);
    if (result) {
      std::cout << "\nThe deletion was successfull." << std::endl;
    } else {
      std::cout << "\nThe position was out of range. ";
      std::cout << "No deletion was performed." << std::endl;
    }
  }

  void ArrayCtrl::retrieve() {
    int pos, value;
    std::cout << "\nEnter an array position: ";
    std::cin >> pos;
    bool result = initial_array->GetElement(pos, value);
    if (result)
      std::cout << "\nThe value at " << pos << " is " << value << "." << std::endl;
    else
      std::cout << "\nThe array position you entered is out of range." << std::endl;
  }

  void ArrayCtrl::find() {
    int value, pos;
    std::cout << "\nEnter a value to find: ";
    std::cin >> value;
    bool result = initial_array->FindElement(value, pos);
    if (!result)
      std::cout << "\n" << value << " is not in the array." << std::endl;
    else
      std::cout << "\n" << value << " is an position " << pos << "." << std::endl;
  }

  void ArrayCtrl::list() {
    int value;
    ArrayItr *the_itr = new ArrayItr(initial_array, initial_array->GetSize());
    bool result = the_itr->GetNext(value);
    int i = 0;
    while (result) {
      std::cout << i+1 << ": " << value << std::endl;
      result = the_itr->GetNext(value);
      i++;
    }
  }

  void ArrayCtrl::size() {
    std::cout << "There are " << initial_array->GetSize() << " elements in the array." << std::endl;
  }
}
