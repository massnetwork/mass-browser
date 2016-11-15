#ifndef HASHITEM_H_
#define HASHITEM_H_

#include "./base.h"

template<class T>
class HashItem {
 public:
  HashItem() : next(nullptr), hashItemStorage(nullptr) {
  }

  ~HashItem() {
    if (hashItemStorage) {
      delete hashItemStorage;
    }
  }

  HashItem *next;
  T *hashItemStorage;
};

#endif // HASHITEM_H_