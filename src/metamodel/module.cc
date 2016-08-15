#include "module.h"

#include "common/cref.h"

#include <string>
#include <unordered_map>

#include <cstdlib>
#include <cstring>

namespace ai {
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

// Static
Module *Module::Core() {
  static Module *core = LookFor("core");

  return core;
}

Module::Module(const std::string &identifier) {
  identifier_.assign(identifier);
}

Module::~Module() {}

}  // namespace ai
