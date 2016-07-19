#include "module.h"

#include "tools/cref.h"

#include <string>
#include <unordered_map>

#include <cstdlib>
#include <cstring>

namespace abject {
// Static
Module *Module::LookFor(const std::string &identifier) {
  typedef std::unordered_map<std::string, cref<Module>> TCache;

  static TCache cache;
  TCache::const_iterator it = cache.find(identifier);
  Module *result;

  if (it == cache.end()) {
    result = new Module(identifier);
    cache[identifier] = result;
  } else {
    result = it->second.get();
  }

  return result;
}

Module::Module(const std::string &identifier) {
  identifier_.assign(identifier);
}

Module::~Module() {}

}  // namespace abject
