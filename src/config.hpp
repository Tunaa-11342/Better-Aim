#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

struct CONFIG {
    std::string targetColor;
    int tolerance;
    int scanAreaX, scanAreaY;
    int gravity;
    std::string toggleKey;
    int refreshRate;
};

extern CONFIG config;

std::string xorEncryptDecrypt(const std::string& input) {
    std::string key = "to skibidi or not";
    std::string output = input;
    for (size_t i = 0; i < input.size(); ++i) {
        output[i] ^= key[i % key.size()];
    }
    return output;
}

bool saveConfig() {
    char exePath[MAX_PATH];
    GetModuleFileNameA(NULL, exePath, MAX_PATH);

    std::string configFilePath(exePath);
    configFilePath = configFilePath.substr(0, configFilePath.find_last_of("\\/")) + "\\config.dat";

    // yo mr. Reverser, I hope you like this :p
    std::string x86_var_1 = "to skibidi or not";
    try {
        std::ostringstream oss;
        oss << config.targetColor << '\n';
        oss << config.tolerance << '\n';
        oss << config.scanAreaX << ' ' << config.scanAreaY << '\n';
        oss << config.refreshRate << "\n";
        oss << config.gravity << '\n';
        oss << config.toggleKey << '\n';

        std::string encryptedData = xorEncryptDecrypt(oss.str());

        std::ofstream outFile(configFilePath, std::ios::binary);
        if (!outFile) {
            std::cerr << "Failed to open file for writing: " << configFilePath << std::endl;
            return false;
        }

        outFile.write(encryptedData.data(), encryptedData.size());
        outFile.close();

        return true;
    }
    catch (const std::exception& e) {
        std::cerr << "Error saving config: " << e.what() << std::endl;
        return false;
    }
}

bool loadConfig() {
    char exePath[MAX_PATH];
    GetModuleFileNameA(NULL, exePath, MAX_PATH);

    // Replace the executable's name with the configuration filename
    std::string configFilePath(exePath);
    configFilePath = configFilePath.substr(0, configFilePath.find_last_of("\\/")) + "\\config.dat";

    try {
        std::ifstream inFile(configFilePath, std::ios::binary);
        if (!inFile) {
            return false;
        }

        std::ostringstream oss;
        oss << inFile.rdbuf();
        std::string encryptedData = oss.str();
        std::string decryptedData = xorEncryptDecrypt(encryptedData);

        std::istringstream iss(decryptedData);
        std::getline(iss, config.targetColor);
        iss >> config.tolerance;
        iss >> config.scanAreaX >> config.scanAreaY;
        iss >> config.refreshRate;
        iss >> config.gravity;
        iss.ignore(); // Ignore newline after gravity
        std::getline(iss, config.toggleKey);

        inFile.close();

        return true;
    }
    catch (const std::exception& e) {
        std::cerr << "Error loading config: " << e.what() << std::endl;
        return false;
    }
}

void printConfig() {
    std::cout << "\t- Target color: " << config.targetColor << std::endl;
    std::cout << "\t- Tolerance (color sensitivity): " << config.tolerance << std::endl;
    std::cout << "\t- Scan area (FOV): (x: " << config.scanAreaX << ", y: " << config.scanAreaY << ")" << std::endl;
    std::cout << "\t- Gravity (mouse lock power): " << config.gravity << std::endl;
    std::cout << "\t- Toggle key: " << config.toggleKey << std::endl;
    std::cout << "\t- Screen refresh rate: " << config.refreshRate << "FPS" << std::endl;
}
