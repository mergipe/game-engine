#include "StringId.h"

#include "Hash.h"
#include "Locator.h"
#include "Logger.h"

#include <unordered_map>

namespace Engine
{
    StringId StringId::Intern(std::string_view str)
    {
        const StringIdHashType hash{Hash::Hash32(str.data())};
        if (!s_stringIdTable.contains(hash)) {
            s_stringIdTable[hash] = std::string{str};
            Locator::GetLogger()->Trace("[StringId] Interned '{}' as '{}'", str, hash);
        }
        return StringId{s_stringIdTable[hash], hash};
    }

    std::string_view StringId::GetString(StringIdHashType hash)
    {
        if (s_stringIdTable.contains(hash)) {
            return s_stringIdTable[hash];
        }
        return {};
    }

    StringId::StringId(std::string_view str, StringIdHashType hash)
        : m_str{str}, m_hash{hash}
    {
    }
} // namespace Engine
