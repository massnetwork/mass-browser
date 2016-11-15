#include "./cosmeticFilter.h"
#include "hashFn.h"

static HashFn fn(19);

uint64_t CosmeticFilter::hash() const {
  return fn(data, static_cast<int>(strlen(data)));
}