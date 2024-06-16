#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Identifier.hpp"

namespace ProtocolCraft
{
    class ClientboundCookieRequestLoginPacket : public BaseMessage<ClientboundCookieRequestLoginPacket>
    {
    public:
        static constexpr int packet_id = 0x05;
        static constexpr std::string_view packet_name = "Cookie Request (Login)";

        DECLARE_FIELDS(
            (Identifier),
            (Key)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Key);
    };
}
#endif
