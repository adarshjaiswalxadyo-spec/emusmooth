#pragma once

#include <string>
#include <vector>
#include <filesystem>

struct APKInfo {
    std::string name;
    std::string packageName;
    std::string filepath;
    std::string version;
};

class APKManager {
public:
    APKManager();
    ~APKManager();
    
    // APK file operations
    bool LoadAPK(const std::string& filepath);
    std::vector<APKInfo> GetInstalledAPKs() const;
    bool LaunchAPK(const std::string& packageName);
    
    // APK info extraction (simplified - real implementation would parse AndroidManifest.xml)
    APKInfo ExtractAPKInfo(const std::string& filepath);
    
    // Installation directory
    void SetInstallDirectory(const std::string& dir);
    std::string GetInstallDirectory() const { return m_installDir; }
    
private:
    std::vector<APKInfo> m_installedAPKs;
    std::string m_installDir;
    
    void ScanInstalledAPKs();
    std::string GetPackageNameFromPath(const std::string& filepath);
};
