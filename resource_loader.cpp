//
// Created by valen on 5/23/2023.
//

#include "resource_loader.h"
#include <SFML/Network.hpp>
#include <fstream>
#include <filesystem>
#include <iostream>

/**
 * Завантажує файл з сервера https://stdio.systems .
 * @param serverUrl - адреса сервера.
 * @param serverPort - порт сервера.
 * @param filePath - шлях до файлу.
 * @return - true, якщо файл був завантажений успішно.
 */
bool loadResources(const std::string& serverUrl, int serverPort, const std::string& filePath)
{
    sf::Http http(serverUrl, serverPort);

    sf::Http::Request request;
    request.setMethod(sf::Http::Request::Get);
    request.setUri(filePath);

    sf::Http::Response response = http.sendRequest(request);
    if (response.getStatus() == sf::Http::Response::Ok)
    {
        std::ofstream outputFile(filePath, std::ios::binary);
        if (!outputFile)
        {
            std::cout << "Failed to create output file: " << filePath << std::endl;
            return false;
        }

        outputFile.write(response.getBody().c_str(), response.getBody().size());
        outputFile.close();

        return true;
    }
    else
    {
        std::cout << "Failed to download file: " << filePath << std::endl;
        return false;
    }
}