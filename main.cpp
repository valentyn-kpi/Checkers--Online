#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <filesystem>
#include <iostream>
#include "classes/SceneManager.h"
#include "scenes/MainMenuS.h"
#include "scenes/OfflineGameS.h"
#include "scenes/SettingsS.h"
#include "scenes/AboutS.h"
#include "scenes/OnlineGame.h"
#include "resource_loader.h"

/**
 * Завантажує всі файли, які потрібні для роботи програми.
 * @return - true, якщо всі файли були завантажені успішно, або вони вже існують.
 */
bool loadFiles() {
    std::vector<std::string> files = {
            "res/settings.txt",
            "res/audio/click.wav",
            "res/audio/checkermove.wav",
            "res/fonts/arial.ttf",
            "res/fonts/chess.ttf",
            "res/fonts/JBB.ttf"
    };
    for (auto &file: files) {
        if (!std::filesystem::exists(file)) {
            //create folder
            std::filesystem::create_directories(std::filesystem::path(file).parent_path());
            std::cout << "Downloading file: " << file << std::endl;
            if(!loadResources("100.26.10.86", 8080, file)) return false;
        } else {
            std::cout << "File already exists: " << file << std::endl;
        }
    }
    return true;
}

int main() {

    //Завантажуємо файли
    if (!loadFiles()) {
        std::cout << "Failed to load required files,\n"
                     "try to add this files manually.\n"
                     "EXITING....\n" << std::endl;
        std::getchar();
        return -1;
    }

    //Ховаємо консоль
    HWND consoleWindow = GetConsoleWindow();
    ShowWindow(consoleWindow, SW_HIDE);

    //Завантажуємо налаштування
    Settings settings("res/settings.txt");
    //Створюємо вікно
    sf::VideoMode desktop;
    sf::RenderWindow window;

    if (settings.getBool("fulls", false)) {
        //Якшо вікно повноекранне за налаштуваннями
        desktop = sf::VideoMode::getFullscreenModes()[settings.getUInt("scr_mode", 0)];
        window.create(desktop, "", sf::Style::Fullscreen);
    } else {
        //Якшо вікно не повноекранне(дефолтне)
        desktop = sf::VideoMode::getDesktopMode();
        desktop.width = settings.getUInt("width", desktop.width / 2);
        desktop.height = settings.getUInt("height", desktop.height / 2);
        window.create(desktop, "Checkers::Online", sf::Style::Default);
    }
    //Встановлюємо FPS 30 - за замовчуванням
    window.setFramerateLimit(settings.getUInt("fps", 30));

    //Створюємо менеджер сцен
    SceneManager sceneManager;

    //Додаємо сцени
    MainMenuS mainMenuScene(window, settings, sceneManager);
    sceneManager.addScene(&mainMenuScene);//0

    OfflineGameS offlineGameScene(window, settings, sceneManager);
    sceneManager.addScene(&offlineGameScene);//1

    SettingsS settingsScene(window, settings, sceneManager);
    sceneManager.addScene(&settingsScene);//2

    AboutS aboutScene(window, settings, sceneManager);
    sceneManager.addScene(&aboutScene);//3

    OnlineGame onlineGameScene(window, settings, sceneManager);
    sceneManager.addScene(&onlineGameScene);//4

    sceneManager.switchToScene(0);

    sf::Clock clock;

    //Головний цикл гри
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::Resized) {
                if (!settings.getBool("fulls", false)) {
                    sf::Vector2u newSize = window.getSize();
                    //Забороняємо змінювати розмір вікна на менше 1280x720
                    if (newSize.x < 1280 || newSize.y < 720) {
                        window.setSize(sf::Vector2u(std::max(newSize.x, 1280u), std::max(newSize.y, 720u)));
                        continue;
                    }
                    //Забороняємо змінювати відношення сторін менше 15:10
                    if (newSize.x < newSize.y * 1.5) {
                        newSize.x = newSize.y * 1.5;
                        window.setSize(newSize);
                    }
                }
            }
            sceneManager.handleEvent(event);
        }

        int deltaTime = clock.restart().asMilliseconds();
        sceneManager.updateCurrentScene(deltaTime);


        window.clear(sf::Color(44, 47, 51));
        sceneManager.drawCurrentScene(window);
        window.display();
    }
    return 0;
}