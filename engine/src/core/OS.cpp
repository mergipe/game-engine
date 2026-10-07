#include "OS.h"

namespace Engine::OS
{
    std::optional<std::string> GetEnv(std::string_view name)
    {
#ifdef _WIN32
        char* value{nullptr};
        std::size_t size{0};
        if (_dupenv_s(&value, &size, name.data()) != 0 || !value) {
            return {};
        }
        std::string result{value};
        std::free(value);
        return result;
#else
        const auto value{std::getenv(name.data())};
        if (!value) {
            return {};
        }
        return std::string{value};
#endif
    }
} // namespace Engine::OS
