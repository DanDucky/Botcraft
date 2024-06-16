#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Item/Slot.hpp"
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#include <map>
#endif

namespace ProtocolCraft
{
    class ServerboundContainerClickPacket : public BaseMessage<ServerboundContainerClickPacket>
    {
    public:
#if   PROTOCOL_VERSION == 340 /* 1.12.2 */
        static constexpr int packet_id = 0x07;
#elif PROTOCOL_VERSION == 393 /* 1.13 */ || PROTOCOL_VERSION == 401 /* 1.13.1 */ ||  \
      PROTOCOL_VERSION == 404 /* 1.13.2 */
        static constexpr int packet_id = 0x08;
#elif PROTOCOL_VERSION == 477 /* 1.14 */ || PROTOCOL_VERSION == 480 /* 1.14.1 */ ||  \
      PROTOCOL_VERSION == 485 /* 1.14.2 */ || PROTOCOL_VERSION == 490 /* 1.14.3 */ ||  \
      PROTOCOL_VERSION == 498 /* 1.14.4 */ || PROTOCOL_VERSION == 573 /* 1.15 */ ||  \
      PROTOCOL_VERSION == 575 /* 1.15.1 */ || PROTOCOL_VERSION == 578 /* 1.15.2 */ ||  \
      PROTOCOL_VERSION == 735 /* 1.16 */ || PROTOCOL_VERSION == 736 /* 1.16.1 */ ||  \
      PROTOCOL_VERSION == 751 /* 1.16.2 */ || PROTOCOL_VERSION == 753 /* 1.16.3 */ ||  \
      PROTOCOL_VERSION == 754 /* 1.16.4/5 */
        static constexpr int packet_id = 0x09;
#elif PROTOCOL_VERSION == 755 /* 1.17 */ || PROTOCOL_VERSION == 756 /* 1.17.1 */ ||  \
      PROTOCOL_VERSION == 757 /* 1.18/.1 */ || PROTOCOL_VERSION == 758 /* 1.18.2 */
        static constexpr int packet_id = 0x08;
#elif PROTOCOL_VERSION == 759 /* 1.19 */
        static constexpr int packet_id = 0x0A;
#elif PROTOCOL_VERSION == 760 /* 1.19.1/2 */
        static constexpr int packet_id = 0x0B;
#elif PROTOCOL_VERSION == 761 /* 1.19.3 */
        static constexpr int packet_id = 0x0A;
#elif PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */
        static constexpr int packet_id = 0x0B;
#elif PROTOCOL_VERSION == 764 /* 1.20.2 */ || PROTOCOL_VERSION == 765 /* 1.20.3/4 */
        static constexpr int packet_id = 0x0D;
#elif PROTOCOL_VERSION == 766 /* 1.20.5/6 */ || PROTOCOL_VERSION == 767 /* 1.21 */
        static constexpr int packet_id = 0x0E;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Container Click";

#if PROTOCOL_VERSION < 755 /* < 1.17 */
        DECLARE_FIELDS_TYPES(unsigned char, short,   char,      short, VarInt,    Slot);
        DECLARE_FIELDS_NAMES(ContainerId,   SlotNum, ButtonNum, Uid,   ClickType, CarriedItem);
#elif PROTOCOL_VERSION < 756 /* < 1.17.1 */
        DECLARE_FIELDS_TYPES(unsigned char, short,   char,      VarInt,    std::map<short, Slot>, Slot);
        DECLARE_FIELDS_NAMES(ContainerId,   SlotNum, ButtonNum, ClickType, ChangedSlots,          CarriedItem);
#else
        DECLARE_FIELDS_TYPES(unsigned char, VarInt,  short,   char,      VarInt,    std::map<short, Slot>, Slot);
        DECLARE_FIELDS_NAMES(ContainerId,   StateId, SlotNum, ButtonNum, ClickType, ChangedSlots,          CarriedItem);
#endif
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(ContainerId);
        GETTER_SETTER(SlotNum);
        GETTER_SETTER(ButtonNum);
#if PROTOCOL_VERSION < 755 /* < 1.17 */
        GETTER_SETTER(Uid);
#endif
        GETTER_SETTER(ClickType);
        GETTER_SETTER(CarriedItem);
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
        GETTER_SETTER(ChangedSlots);
#endif
#if PROTOCOL_VERSION > 755 /* > 1.17 */
        GETTER_SETTER(StateId);
#endif
    };
} //ProtocolCraft
