#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundStartConfigurationPacket : public BaseMessage<ClientboundStartConfigurationPacket>
    {
    public:
#if   PROTOCOL_VERSION == 764 /* 1.20.2 */
        static constexpr int packet_id = 0x65;
#elif PROTOCOL_VERSION == 765 /* 1.20.3/4 */
        static constexpr int packet_id = 0x67;
#elif PROTOCOL_VERSION == 766 /* 1.20.5/6 */ || PROTOCOL_VERSION == 767 /* 1.21 */
        static constexpr int packet_id = 0x69;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Start Configuration";

        DECLARE_EMPTY;
    };
} //ProtocolCraft
#endif
