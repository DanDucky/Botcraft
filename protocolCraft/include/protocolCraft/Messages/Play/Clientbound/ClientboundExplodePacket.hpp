#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class ClientboundExplodePacket : public BaseMessage<ClientboundExplodePacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x1C;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x1E;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x1C;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x1D;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x1C;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x1B;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Explode";
        }

        void SetX(const float x_)
        {
            x = x_;
        }

        void SetY(const float y_)
        {
            y = y_;
        }

        void SetZ(const float z_)
        {
            z = z_;
        }

        void SetPower(const float power_)
        {
            power = power_;
        }

        void SetToBlow(const std::vector<NetworkPosition>& to_blow_)
        {
            to_blow = to_blow_;
        }

        void SetKnockbackX(const float knockback_x_)
        {
            knockback_x = knockback_x_;
        }

        void SetKnockbackY(const float knockback_y_)
        {
            knockback_y = knockback_y_;
        }

        void SetKnockbackZ(const float knockback_z_)
        {
            knockback_z = knockback_z_;
        }


        const float GetX() const
        {
            return x;
        }

        const float GetY() const
        {
            return y;
        }

        const float GetZ() const
        {
            return z;
        }

        const float GetPower() const
        {
            return power;
        }

        const std::vector<NetworkPosition>& GetToBlow() const
        {
            return to_blow;
        }

        const float GetKnockbackX() const
        {
            return knockback_x;
        }

        const float GetKnockbackY() const
        {
            return knockback_y;
        }

        const float GetKnockbackZ() const
        {
            return knockback_z;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            x = ReadData<float>(iter, length);
            y = ReadData<float>(iter, length);
            z = ReadData<float>(iter, length);
            power = ReadData<float>(iter, length);
            const int to_blow_size = ReadData<int>(iter, length);
            to_blow = std::vector<NetworkPosition>(to_blow_size);
            for (int i = 0; i < to_blow_size; ++i)
            {
                to_blow[i].SetX((int)ReadData<char>(iter, length));
                to_blow[i].SetY((int)ReadData<char>(iter, length));
                to_blow[i].SetZ((int)ReadData<char>(iter, length));
            }
            knockback_x = ReadData<float>(iter, length);
            knockback_y = ReadData<float>(iter, length);
            knockback_z = ReadData<float>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<float>(x, container);
            WriteData<float>(y, container);
            WriteData<float>(z, container);
            WriteData<float>(power, container);
            WriteData<int>(to_blow.size(), container);
            for (int i = 0; i < to_blow.size(); ++i)
            {
                WriteData<char>(to_blow[i].GetX(), container);
                WriteData<char>(to_blow[i].GetY(), container);
                WriteData<char>(to_blow[i].GetZ(), container);
            }
            WriteData<float>(knockback_x, container);
            WriteData<float>(knockback_y, container);
            WriteData<float>(knockback_z, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["x"] = picojson::value((double)x);
            object["y"] = picojson::value((double)y);
            object["z"] = picojson::value((double)z);
            object["power"] = picojson::value((double)power);
            picojson::value value2(picojson::array_type, false);
            picojson::array& object2 = value2.get<picojson::array>();
            for (int i = 0; i < to_blow.size(); ++i)
            {
                object2.push_back(to_blow[i].Serialize());
            }
            object["to_blow"] = value2;
            object["knockback_x"] = picojson::value((double)knockback_x);
            object["knockback_y"] = picojson::value((double)knockback_y);
            object["knockback_z"] = picojson::value((double)knockback_z);

            return value;
        }

    private:
        float x;
        float y;
        float z;
        float power;
        std::vector<NetworkPosition> to_blow;
        float knockback_x;
        float knockback_y;
        float knockback_z;

    };
} //ProtocolCraft