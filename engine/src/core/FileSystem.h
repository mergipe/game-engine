#pragma once

#include <filesystem>

namespace Engine
{
    class FileSystem
    {
    public:
        FileSystem() = delete;
        static void SetProjectPath(const std::filesystem::path& projectPath);
        static std::filesystem::path GetProjectPath();
        static std::filesystem::path GetAbsoluteEnginePath(std::string_view relativePath);
        static std::filesystem::path GetAbsoluteProjectPath(std::string_view relativePath);
        static bool IsDirectory(const std::filesystem::path& path);
        static bool IsFile(const std::filesystem::path& path);
        static std::string ReadStringFromFile(const std::filesystem::path& filePath);

    private:
        static inline std::filesystem::path s_enginePath{std::filesystem::canonical(ENGINE_BASE_DIR)};
        static inline std::filesystem::path s_projectPath{};
    };
} // namespace Engine
