#include "Engine.h"
#include "core/FileSystem.h"

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " project_path\n";
        return 1;
    }
    const auto projectPath(std::filesystem::canonical(argv[1]));
    if (!Engine::FileSystem::IsDirectory(projectPath)) {
        std::cerr << "Please, provide a valid project path.\n";
        return 1;
    }
    Engine::FileSystem::SetProjectPath(projectPath);
    Engine::Engine& engine{Engine::Engine::Instance()};
    engine.Start();
    return 0;
}
