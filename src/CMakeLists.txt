project(Abject)

add_subdirectory(vendor/tanuki)

# Names
set(ABJECT_COMMON "AbjectCommon") # lib for common classes
set(ABJECT_METAMODEL_CORE "MetamodelCore") # lib for metamodel
set(ABJECT_COMPILER_TOOLS "AbjectCompilerTools") # lib for compiling
set(ABJECT_COMPILER "AbjectC") # Front end compiler
set(ABJECT_ONIRISM "Onirism") # front end executor (jit)
set(ABJECT_LETHARGY "Lethargy") # front end executor (interpreter)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

cmake_minimum_required(VERSION 2.8)

add_library(${ABJECT_COMMON}
  common/cref.cc
  common/countable.cc
  common/memory.cc
)

add_library(${ABJECT_METAMODEL_CORE}
  # metamodel
  metamodel/metamodel.cc
  metamodel/module.cc
  metamodel/modular.cc
  metamodel/types.cc

  # cfg
  metamodel/cfg/cfg.cc
  metamodel/cfg/statements.cc
  metamodel/cfg/identifier.cc

  # Abstract
  abstract/abstract.cc

  # Loader
  metamodel/loader/loader.cc

  ## Filesystem
  metamodel/loader/filesystem/filesystem.cc
)

add_library(${ABJECT_COMPILER_TOOLS}
  compiler/parser/ast.cpp
  compiler/parser/parse.cpp
)

add_executable(${ABJECT_COMPILER}
  compilermain.cpp
)

add_executable(${ABJECT_LETHARGY}
    lethargy.cc

    execution/lethargy/interpreter.cc
    execution/lethargy/executor.cc
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
add_executable(${ABJECT_ONIRISM} onirism.cc)
target_link_libraries(${ABJECT_ONIRISM} ${ABJECT_METAMODEL_CORE})  # ${ABJECT_COMPILER_TOOLS}
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
