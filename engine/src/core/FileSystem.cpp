#include "FileSystem.h"

#include "Locator.h"

#include <fstream>
#include <sstream>

namespace Engine
{
    void FileSystem::SetProjectPath(const std::filesystem::path& projectPath) { s_projectPath = projectPath; }

    std::filesystem::path FileSystem::GetProjectPath() { return s_projectPath; }

    std::filesystem::path FileSystem::GetAbsoluteEnginePath(std::string_view relativePath)
    {
        return s_enginePath / relativePath;
    }

    std::filesystem::path FileSystem::GetAbsoluteProjectPath(std::string_view relativePath)
    {
        return s_projectPath / relativePath;
    }

    bool FileSystem::IsDirectory(const std::filesystem::path& path)
    {
        return std::filesystem::is_directory(path);
    }

    bool FileSystem::IsFile(const std::filesystem::path& path)
    {
        return std::filesystem::is_regular_file(path);
    }

    std::string FileSystem::ReadStringFromFile(const std::filesystem::path& filePath)
    {
        std::ifstream fileStream{filePath};
        if (!fileStream.is_open()) {
            Locator::GetLogger()->Error("File {} not found", filePath.c_str());
            return {};
        }
        std::stringstream buffer{};
        buffer << fileStream.rdbuf();
        fileStream.close();
        return buffer.str();
    }
} // namespace Engine
