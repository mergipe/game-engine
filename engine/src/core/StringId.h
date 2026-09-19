#pragma once

#include "Hash.h"
#include "Types.h"

#include <iostream>
#include <string>
#include <string_view>
#include <unordered_map>

namespace Engine
{
    using StringIdHashType = U32;

    constexpr U32 operator""_sid(const char* str, std::size_t) { return Hash::Hash32(str); }

    /**
     * Wraps a view to an interned string and its hashed value.
     */
    class StringId
    {
    public:
        static StringId Intern(std::string_view str);
        static std::string_view GetString(StringIdHashType hash);

        StringId() = default;
        constexpr explicit StringId(const char* str);

        bool operator==(const StringId& other) const { return m_hash == other.m_hash; }
        [[nodiscard]] std::string_view GetString() const { return m_str; }
        [[nodiscard]] StringIdHashType GetHash() const { return m_hash; }

    private:
        static inline std::unordered_map<StringIdHashType, std::string> s_stringIdTable{};

        explicit StringId(std::string_view str, StringIdHashType hash);

        std::string_view m_str{};
        StringIdHashType m_hash{};
    };

    constexpr StringId::StringId(const char* str)
        : m_str{str}, m_hash{Hash::Hash32(str)}
    {
    }

#define SID(str)                                                                                             \
    StringId { str }
} // namespace Engine

template <>
struct std::hash<Engine::StringId> {
    std::size_t operator()(const Engine::StringId& sid) const noexcept { return sid.GetHash(); }
};
