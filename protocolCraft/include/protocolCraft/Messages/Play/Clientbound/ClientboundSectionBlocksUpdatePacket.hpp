#pragma once

#include "protocolCraft/BaseMessage.hpp"

#if PROTOCOL_VERSION < 739 /* < 1.16.2 */
#include "protocolCraft/Types/Record.hpp"
#endif

namespace ProtocolCraft
{
    class ClientboundSectionBlocksUpdatePacket : public BaseMessage<ClientboundSectionBlocksUpdatePacket>
    {
    public:
#if   PROTOCOL_VERSION == 340 /* 1.12.2 */
        static constexpr int packet_id = 0x10;
#elif PROTOCOL_VERSION == 393 /* 1.13 */ || PROTOCOL_VERSION == 401 /* 1.13.1 */ ||  \
      PROTOCOL_VERSION == 404 /* 1.13.2 */ || PROTOCOL_VERSION == 477 /* 1.14 */ ||  \
      PROTOCOL_VERSION == 480 /* 1.14.1 */ || PROTOCOL_VERSION == 485 /* 1.14.2 */ ||  \
      PROTOCOL_VERSION == 490 /* 1.14.3 */ || PROTOCOL_VERSION == 498 /* 1.14.4 */
        static constexpr int packet_id = 0x0F;
#elif PROTOCOL_VERSION == 573 /* 1.15 */ || PROTOCOL_VERSION == 575 /* 1.15.1 */ ||  \
      PROTOCOL_VERSION == 578 /* 1.15.2 */
        static constexpr int packet_id = 0x10;
#elif PROTOCOL_VERSION == 735 /* 1.16 */ || PROTOCOL_VERSION == 736 /* 1.16.1 */
        static constexpr int packet_id = 0x0F;
#elif PROTOCOL_VERSION == 751 /* 1.16.2 */ || PROTOCOL_VERSION == 753 /* 1.16.3 */ ||  \
      PROTOCOL_VERSION == 754 /* 1.16.4/5 */
        static constexpr int packet_id = 0x3B;
#elif PROTOCOL_VERSION == 755 /* 1.17 */ || PROTOCOL_VERSION == 756 /* 1.17.1 */ ||  \
      PROTOCOL_VERSION == 757 /* 1.18/.1 */ || PROTOCOL_VERSION == 758 /* 1.18.2 */
        static constexpr int packet_id = 0x3F;
#elif PROTOCOL_VERSION == 759 /* 1.19 */
        static constexpr int packet_id = 0x3D;
#elif PROTOCOL_VERSION == 760 /* 1.19.1/2 */
        static constexpr int packet_id = 0x40;
#elif PROTOCOL_VERSION == 761 /* 1.19.3 */
        static constexpr int packet_id = 0x3F;
#elif PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */
        static constexpr int packet_id = 0x43;
#elif PROTOCOL_VERSION == 764 /* 1.20.2 */
        static constexpr int packet_id = 0x45;
#elif PROTOCOL_VERSION == 765 /* 1.20.3/4 */
        static constexpr int packet_id = 0x47;
#elif PROTOCOL_VERSION == 766 /* 1.20.5/6 */ || PROTOCOL_VERSION == 767 /* 1.21 */
        static constexpr int packet_id = 0x49;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Section Blocks Update";

#if PROTOCOL_VERSION < 751 /* < 1.16.2 */
        DECLARE_FIELDS(
            (int,    int,    std::vector<Record>),
            (ChunkX, ChunkZ, Records)
        );
#elif PROTOCOL_VERSION < 763 /* < 1.20 */
        DECLARE_FIELDS(
            (long long int, bool,                 std::vector<short>, std::vector<int>),
            (SectionPos,    SuppressLightUpdates, Positions,          States)
        );
#else
        DECLARE_FIELDS(
            (long long int, std::vector<short>, std::vector<int>),
            (SectionPos,    Positions,          States)
        );
#endif
        DECLARE_SERIALIZE;

#if PROTOCOL_VERSION < 751 /* < 1.16.2 */
        GETTER_SETTER(ChunkX);
        GETTER_SETTER(ChunkZ);
        GETTER_SETTER(Records);
#endif
#if PROTOCOL_VERSION > 736 /* > 1.16.1 */
        GETTER_SETTER(SectionPos);
        GETTER_SETTER(Positions);
        GETTER_SETTER(States);
#endif
#if PROTOCOL_VERSION > 736 /* > 1.16.1 */ && PROTOCOL_VERSION < 763 /* < 1.20 */
        GETTER_SETTER(SuppressLightUpdates);
#endif

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
#if PROTOCOL_VERSION < 739 /* < 1.16.2 */
            SetChunkX(ReadData<int>(iter, length));
            SetChunkZ(ReadData<int>(iter, length));
            SetRecords(ReadData<std::vector<Record>>(iter, length));
#else
            SetSectionPos(ReadData<long long int>(iter, length));
#if PROTOCOL_VERSION < 763 /* < 1.20 */
            SetSuppressLightUpdates(ReadData<bool>(iter, length));
#endif
            const std::vector<long long int> data = ReadData<std::vector<VarLong>>(iter, length);
            std::vector<short> positions(data.size());
            std::vector<int> states(data.size());
            for (size_t i = 0; i < data.size(); ++i)
            {
                positions[i] = static_cast<short>(data[i] & 0xFFFl);
                states[i] = static_cast<int>(data[i] >> 12);
            }
            SetPositions(positions);
            SetStates(states);
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
#if PROTOCOL_VERSION < 739 /* < 1.16.2 */
            WriteData<int>(GetChunkX(), container);
            WriteData<int>(GetChunkZ(), container);
            WriteData<std::vector<Record>>(GetRecords(), container);
#else
            WriteData<long long int>(GetSectionPos(), container);
#if PROTOCOL_VERSION < 763 /* < 1.20 */
            WriteData<bool>(GetSuppressLightUpdates(), container);
#endif
            WriteData<VarInt>(static_cast<int>(GetPositions().size()), container);
            for (size_t i = 0; i < GetPositions().size(); ++i)
            {
                WriteData<VarLong>((static_cast<long long int>(GetStates()[i]) << 12) | static_cast<long long int>(GetPositions()[i]), container);
            }
#endif
        }
    };
}
