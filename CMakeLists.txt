cmake_minimum_required(VERSION 3.25)
project(checkers)

set(CMAKE_CXX_STANDARD 23)

#set O2
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")

#set o0
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")

include(FetchContent)

FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)


add_executable(checkers
        main.cpp
        classes/Scene.h
        classes/SceneManager.cpp
        classes/SceneManager.h
        scenes/MainMenuS.cpp
        scenes/MainMenuS.h
        classes/Settings.cpp
        classes/Settings.h classes/UI/Menu.cpp classes/UI/Menu.h classes/UI/Button.cpp classes/UI/Button.h classes/UI/Label.cpp classes/UI/Label.h scenes/OfflineGameS.cpp scenes/OfflineGameS.h scenes/SettingsS.cpp scenes/SettingsS.h scenes/AboutS.cpp scenes/AboutS.h classes/UI/Select.cpp classes/UI/Select.h classes/GameBoard.cpp classes/GameBoard.h scenes/OnlineGame.cpp scenes/OnlineGame.h classes/UI/CheckBox.cpp classes/UI/CheckBox.h resource_loader.cpp resource_loader.h)

target_link_libraries(checkers PRIVATE sfml-graphics sfml-audio sfml-window sfml-system sfml-network)

target_compile_features(checkers PRIVATE cxx_std_17)

if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET checkers POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:checkers> $<TARGET_FILE_DIR:checkers> COMMAND_EXPAND_LISTS)
endif()

install(TARGETS checkers)
