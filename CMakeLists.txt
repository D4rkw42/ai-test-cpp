cmake_minimum_required(VERSION 3.29.7)

project(
    ai-test-cpp
    VERSION 1.0
    DESCRIPTION "teste de IA simples com entidades e path finding"
    HOMEPAGE_URL ""
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)
find_package(effolkronium_random CONFIG REQUIRED)

add_compile_options(-O2) # optmization
add_compile_options(-pipe) # fast compiling
add_compile_options(-pedantic) # error handling

include_directories(
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
    ${SDL2_INCLUDE_DIRS}
)

add_executable(
    ai-test-cpp

    src/main.cpp

    src/system/system.cpp
    src/system/subsystems.cpp
    src/system/global.cpp
    
    src/system/graphics/window.cpp
    src/system/graphics/image-handler.cpp

    src/app/global.cpp
    src/app/app.cpp

    src/controllers/mob-controller.cpp
    src/controllers/ambient-controller.cpp
    src/controllers/collision-controller.cpp

    src/core/entity/entity.cpp
    src/core/object/object.cpp

    src/core/entity/mobs/wolf/wolf.cpp
    src/core/entity/mobs/bunny/bunny.cpp

    src/core/object/objects/tree/tree.cpp
    src/core/object/objects/bush/bush.cpp

    src/utils/game/entity/animation.cpp
    src/utils/game/entity/behavior-handler.cpp
)

target_link_libraries(
    ai-test-cpp PRIVATE

    ${SDL2_LIBRARIES}
    SDL2_image::SDL2_image
    effolkronium_random
)
