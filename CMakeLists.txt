project(Abject)

add_subdirectory(vendor/tanuki)
include_directories(vendor/tanuki)
include_directories(src)

# Names
set(ABJECT_COMMON "AbjectCommon") # lib for common classes
set(ABJECT_METAMODEL_CORE "MetamodelCore") # lib for metamodel
set(ABJECT_COMPILER_TOOLS "AbjectCompilerTools") # lib for compiling
set(ABJECT_COMPILER "AbjectC") # Front end compiler
set(ABJECT_ONIRISM "Onirism") # front end executor (jit)
set(ABJECT_LETHARGY "Lethargy") # front end executor (interpreter)

cmake_minimum_required(VERSION 3.4)

add_library(${ABJECT_COMMON}
  src/common/cref.cc
  src/common/countable.cc
  src/common/memory.cc
  src/common/murmur.cc

  misc/examples/Simple.abj
)

add_library(${ABJECT_METAMODEL_CORE}
  # metamodel
  src/metamodel/metamodel.cc
  src/metamodel/module.cc
  src/metamodel/modular.cc
  src/metamodel/types.cc
  src/metamodel/function.cc

  # cfg
  src/metamodel/cfg/code.cc
  src/metamodel/cfg/statements.cc
  src/metamodel/cfg/identifier.cc

  # Abstract
  src/abstract/abstract.cc

  # Loader
  src/metamodel/loader/loader.cc

  ## Filesystem
  src/metamodel/loader/filesystem/filesystem.cc
)

add_library(${ABJECT_COMPILER_TOOLS}
  src/compiler/parser/ast.cpp
  src/compiler/parser/parse.cpp
)

add_executable(${ABJECT_COMPILER}
  src/compilermain.cpp
)

add_executable(${ABJECT_LETHARGY}
  src/lethargy.cc

  src/execution/lethargy/interpreter.cc
  src/execution/lethargy/executor.cc
  src/execution/lethargy/runtime.cc
)

# Common
set_target_properties(${ABJECT_COMMON} PROPERTIES
    LINKER_LANGUAGE CXX
    CXX_STANDARD 14
)

# Metamodel Core
target_link_libraries(${ABJECT_METAMODEL_CORE} ${ABJECT_COMMON})
set_target_properties(${ABJECT_METAMODEL_CORE} PROPERTIES
    LINKER_LANGUAGE CXX
    CXX_STANDARD 14
)

# Compiler tools
target_link_libraries(${ABJECT_COMPILER_TOOLS} tanuki)
set_target_properties(${ABJECT_COMPILER_TOOLS} PROPERTIES
    LINKER_LANGUAGE CXX
    CXX_STANDARD 14
)

# Compiler
target_link_libraries(${ABJECT_COMPILER} ${ABJECT_COMPILER_TOOLS})
set_target_properties(${ABJECT_COMPILER} PROPERTIES
    LINKER_LANGUAGE CXX
    CXX_STANDARD 14
)

# Onirism
add_executable(${ABJECT_ONIRISM} src/onirism.cc)
target_link_libraries(${ABJECT_ONIRISM} ${ABJECT_METAMODEL_CORE} ${ABJECT_COMPILER_TOOLS} LLVM)  # ${ABJECT_COMPILER_TOOLS}
set_target_properties(${ABJECT_ONIRISM} PROPERTIES
    LINKER_LANGUAGE CXX
    CXX_STANDARD 14
)

# Lethargy
target_link_libraries(${ABJECT_LETHARGY} ${ABJECT_METAMODEL_CORE})  # ${ABJECT_COMPILER_TOOLS}
set_target_properties(${ABJECT_LETHARGY} PROPERTIES
    LINKER_LANGUAGE CXX
    CXX_STANDARD 14
)
