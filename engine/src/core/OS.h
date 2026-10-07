#pragma once

#include <optional>
#include <string>
#include <string_view>

namespace Engine::OS
{
    std::optional<std::string> GetEnv(std::string_view name);
}
