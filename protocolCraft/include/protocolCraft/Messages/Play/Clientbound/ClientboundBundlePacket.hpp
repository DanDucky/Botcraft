#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundBundlePacket : public BaseMessage<ClientboundBundlePacket>
    {
    public:
#if   PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */ ||  \
      PROTOCOL_VERSION == 764 /* 1.20.2 */ || PROTOCOL_VERSION == 765 /* 1.20.3/4 */ ||  \
      PROTOCOL_VERSION == 766 /* 1.20.5/6 */ || PROTOCOL_VERSION == 767 /* 1.21 */
        static constexpr int packet_id = 0x00;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Bundle";

        DECLARE_EMPTY;
    };
} //ProtocolCraft
#endif
