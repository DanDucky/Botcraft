#if PROTOCOL_VERSION > 766 /* > 1.20.6 */
#pragma once
#include "protocolCraft/Types/Components/DataComponentType.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeJukeboxPlayable : public DataComponentType
        {
            DECLARE_FIELDS_TYPES(VarInt,   VarInt,  bool);
            DECLARE_FIELDS_NAMES(Material, Pattern, ShowInTooltip);
            DECLARE_READ_WRITE_SERIALIZE;

            GETTER_SETTER(Material);
            GETTER_SETTER(Pattern);
            GETTER_SETTER(ShowInTooltip);
        };
    }
}
#endif
