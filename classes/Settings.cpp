//
// Created by valen on 5/4/2023.
//

#include "Settings.h"

#include <fstream>
#include <sstream>
#include <iostream>

/**
 * Завантажує налаштування з файлу
 * @param filename ім'я файлу
 */
Settings::Settings(const std::string &filename) {
    this->m_filename = filename;

    std::ifstream file(filename);

    if (!file.is_open()) {

    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        std::stringstream ss(line);
        std::string key, value;
        std::getline(ss, key, '=');
        std::getline(ss, value);

        if (key.empty() || value.empty()) {
            continue;
        }

        if (isdigit(value[0]) || (value[0] == '-' && isdigit(value[1]))) {
            if (value.find('.') != std::string::npos) {
                setFloat(key, std::stof(value));
            } else if(value[0] == '-') {
                setInt(key, std::stoi(value));
            }
            else
            {
                setUInt(key, std::stoul(value));
            }
        } else if (value == "true" || value == "false") {
            setBool(key, value == "true");
        } else {
            setString(key, value);
        }
    }
}

/**
 * Зберігає налаштування в файл
 */
Settings::~Settings() {
    saveToFile();
}

/**
 * Зберігає налаштування в файл
 */
void Settings::saveToFile() const {
    std::ofstream file(m_filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open settings file for writing: " << m_filename << std::endl;
        return;
    }

    for (auto const &[key, value]: m_intSettings) {
        file << key << "=" << value << std::endl;
    }
    for (auto const &[key, value]: m_uintSettings) {
        file << key << "=" << value << std::endl;
    }
    for (auto const &[key, value]: m_floatSettings) {
        file << key << "=" << value << std::endl;
    }
    for (auto const &[key, value]: m_boolSettings) {
        file << key << "=" << (value?"true":"false") << std::endl;
    }
    for (auto const &[key, value]: m_stringSettings) {
        file << key << "=" << value << std::endl;
    }

    file.close();
}

/**
 * Встановлює значення налаштування
 * @param key ключ
 * @param value значення
 */
void Settings::setUInt(const std::string &key, unsigned int value) {
    m_uintSettings[key] = value;
}

/**
 * Встановлює значення налаштування
 * @param key ключ
 * @param value значення
 */
void Settings::setInt(const std::string &key, int value) {
    m_intSettings[key] = value;
}

/**
 * Встановлює значення налаштування
 * @param key ключ
 * @param value значення
 */
void Settings::setFloat(const std::string &key, float value) {
    m_floatSettings[key] = value;
}

/**
 * Встановлює значення налаштування
 * @param key ключ
 * @param value значення
 */
void Settings::setBool(const std::string &key, bool value) {
    m_boolSettings[key] = value;
}

/**
 * Встановлює значення налаштування
 * @param key ключ
 * @param value значення
 */
void Settings::setString(const std::string &key, const std::string &value) {
    m_stringSettings[key] = value;
}

/**
 * Повертає значення налаштування
 * @param key ключ
 * @param defaultValue значення за замовчуванням
 * @return значення налаштування
 */
unsigned int Settings::getUInt(const std::string &key, unsigned int defaultValue) const {
    auto it = m_uintSettings.find(key);
    if (it != m_uintSettings.end()) {
        return it->second;
    } else {
        return defaultValue;
    }
}

/**
 * Повертає значення налаштування
 * @param key ключ
 * @param defaultValue значення за замовчуванням
 * @return значення налаштування
 */
int Settings::getInt(const std::string &key, int defaultValue) const {
    auto it = m_intSettings.find(key);
    if (it != m_intSettings.end()) {
        return it->second;
    } else {
        return defaultValue;
    }
}

/**
 * Повертає значення налаштування
 * @param key ключ
 * @param defaultValue значення за замовчуванням
 * @return значення налаштування
 */
float Settings::getFloat(const std::string &key, float defaultValue) const {
    auto it = m_floatSettings.find(key);
    if (it != m_floatSettings.end()) {
        return it->second;
    } else {
        return defaultValue;
    }
}

/**
 * Повертає значення налаштування
 * @param key ключ
 * @param defaultValue значення за замовчуванням
 * @return значення налаштування
 */
bool Settings::getBool(const std::string &key, bool defaultValue) const {
    auto it = m_boolSettings.find(key);
    if (it != m_boolSettings.end()) {
        return it->second;
    } else {
        return defaultValue;
    }
}

/**
 * Повертає значення налаштування
 * @param key ключ
 * @param defaultValue значення за замовчуванням
 * @return значення налаштування
 */
const std::string &Settings::getString(const std::string &key, const std::string &defaultValue) const {
    auto it = m_stringSettings.find(key);
    if (it != m_stringSettings.end()) {
        return it->second;
    } else {
        return defaultValue;
    }
}