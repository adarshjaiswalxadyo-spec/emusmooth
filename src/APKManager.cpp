#include "APKManager.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <algorithm>
#include <cctype>

namespace fs = std::filesystem;

APKManager::APKManager() {
    m_installDir = "apks";
    
    // Create install directory if it doesn't exist
    if (!fs::exists(m_installDir)) {
        fs::create_directories(m_installDir);
    }
    
    ScanInstalledAPKs();
}

APKManager::~APKManager() {
}

bool APKManager::LoadAPK(const std::string& filepath) {
    if (!fs::exists(filepath)) {
        std::cerr << "APK file not found: " << filepath << std::endl;
        return false;
    }
    
    // Check if it's a valid APK (basic check - should end with .apk)
    if (filepath.substr(filepath.length() - 4) != ".apk") {
        std::cerr << "Invalid APK file: " << filepath << std::endl;
        return false;
    }
    
    // Extract APK info
    APKInfo info = ExtractAPKInfo(filepath);
    
    // Copy to install directory
    std::string destPath = m_installDir + "/" + fs::path(filepath).filename().string();
    try {
        fs::copy_file(filepath, destPath, fs::copy_options::overwrite_existing);
        std::cout << "APK installed: " << info.name << std::endl;
        
        // Add to installed list
        info.filepath = destPath;
        m_installedAPKs.push_back(info);
        
        return true;
    }
    catch (const std::exception& e) {
        std::cerr << "Error installing APK: " << e.what() << std::endl;
        return false;
    }
}

std::vector<APKInfo> APKManager::GetInstalledAPKs() const {
    return m_installedAPKs;
}

bool APKManager::LaunchAPK(const std::string& packageName) {
    // NOTE: This is a simulated launcher
    // In a real implementation, you would need:
    // - Android runtime (like Android-x86, Anbox, or similar)
    // - APK parsing and extraction
    // - Container/VM execution
    
    std::cout << "Launching APK: " << packageName << std::endl;
    std::cout << "NOTE: This is a simulated launcher. Full APK execution requires Android runtime." << std::endl;
    
    // Find APK
    for (const auto& apk : m_installedAPKs) {
        if (apk.packageName == packageName) {
            std::cout << "APK found: " << apk.name << std::endl;
            std::cout << "File: " << apk.filepath << std::endl;
            
            // In a real implementation, you would:
            // 1. Extract APK contents
            // 2. Parse AndroidManifest.xml
            // 3. Launch in Android container/VM
            // 4. Render in emulator window
            
            return true;
        }
    }
    
    std::cerr << "APK not found: " << packageName << std::endl;
    return false;
}

APKInfo APKManager::ExtractAPKInfo(const std::string& filepath) {
    APKInfo info;
    info.filepath = filepath;
    info.name = fs::path(filepath).stem().string();
    info.packageName = GetPackageNameFromPath(filepath);
    info.version = "1.0.0"; // Default version
    
    // NOTE: Real implementation would:
    // 1. Extract APK (it's a ZIP file)
    // 2. Parse AndroidManifest.xml
    // 3. Extract package name, version, app name, etc.
    
    return info;
}

void APKManager::SetInstallDirectory(const std::string& dir) {
    m_installDir = dir;
    if (!fs::exists(m_installDir)) {
        fs::create_directories(m_installDir);
    }
    ScanInstalledAPKs();
}

void APKManager::ScanInstalledAPKs() {
    m_installedAPKs.clear();
    
    if (!fs::exists(m_installDir)) {
        return;
    }
    
    for (const auto& entry : fs::directory_iterator(m_installDir)) {
        if (entry.is_regular_file() && entry.path().extension() == ".apk") {
            APKInfo info = ExtractAPKInfo(entry.path().string());
            m_installedAPKs.push_back(info);
        }
    }
}

std::string APKManager::GetPackageNameFromPath(const std::string& filepath) {
    // Extract a simple package name from filename
    // In real implementation, parse from AndroidManifest.xml
    std::string filename = fs::path(filepath).stem().string();
    
    // Convert to package-like format (lowercase, dots)
    std::string package = filename;
    std::transform(package.begin(), package.end(), package.begin(), ::tolower);
    std::replace(package.begin(), package.end(), ' ', '.');
    
    return "com.emulator." + package;
}
