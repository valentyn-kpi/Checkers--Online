//
// Created by valen on 5/4/2023.
//

#ifndef CHECKERS_SETTINGS_H
#define CHECKERS_SETTINGS_H
#include <string>
#include <unordered_map>

/**
 * Клас Settings об'єктами якого є налаштування
 */
class Settings {
public:
    explicit Settings(const std::string &filename);
    ~Settings();

    void saveToFile() const;

    void setUInt(const std::string& key, unsigned int value);
    void setInt(const std::string& key, int value);
    void setFloat(const std::string& key, float value);
    void setBool(const std::string& key, bool value);
    void setString(const std::string& key, const std::string& value);

    unsigned int getUInt(const std::string& key, unsigned int defaultValue = 0) const;
    int getInt(const std::string& key, int defaultValue = -1) const;
    float getFloat(const std::string& key, float defaultValue = -1.0f) const;
    bool getBool(const std::string& key, bool defaultValue = false) const;
    const std::string& getString(const std::string& key, const std::string& defaultValue = "") const;

private:
    std::string m_filename;
    std::unordered_map<std::string, unsigned int> m_uintSettings;
    std::unordered_map<std::string, int> m_intSettings;
    std::unordered_map<std::string, float> m_floatSettings;
    std::unordered_map<std::string, bool> m_boolSettings;
    std::unordered_map<std::string, std::string> m_stringSettings;

    void reconstructMenu();
};


#endif //CHECKERS_SETTINGSS_H
