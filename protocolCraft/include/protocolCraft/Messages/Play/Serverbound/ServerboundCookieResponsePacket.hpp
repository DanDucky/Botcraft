#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Identifier.hpp"

#include <optional>
#include <vector>

namespace ProtocolCraft
{
    class ServerboundCookieResponsePacket : public BaseMessage<ServerboundCookieResponsePacket>
    {
    public:
#if   PROTOCOL_VERSION == 766 /* 1.20.5/6 */ || PROTOCOL_VERSION == 767 /* 1.21 */
        static constexpr int packet_id = 0x11;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Cookie Response";

        DECLARE_FIELDS_TYPES(Identifier, std::optional<std::vector<unsigned char>>);
        DECLARE_FIELDS_NAMES(Key,        Payload);
        DECLARE_SERIALIZE;

        GETTER_SETTER(Key);
        GETTER_SETTER(Payload);

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            SetKey(ReadData<Identifier>(iter, length));
            // special case, read all remaining bytes
            SetPayload(ReadOptional<std::vector<unsigned char>>(iter, length,
                [](ReadIterator& i, size_t& l)
                {
                    return ReadByteArray(i, l, l);
                }
            ));
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<Identifier>(GetKey(), container);
            // special case, write all bytes without size prefix
            WriteOptional<std::vector<unsigned char>>(GetPayload(), container,
                [](const std::vector<unsigned char>& v, WriteContainer& c)
                {
                    WriteByteArray(v, c);
                });
        }
    };
} // ProtocolCraft
#endif
