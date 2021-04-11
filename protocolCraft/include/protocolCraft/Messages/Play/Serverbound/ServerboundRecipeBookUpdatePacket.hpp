#pragma once

#if PROTOCOL_VERSION < 737
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundRecipeBookUpdatePacket : public BaseMessage<ServerboundRecipeBookUpdatePacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x17;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x1B;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x1D;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x1D;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.X
            return 0x1E;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Recipe Book Update";
        }

        void SetPurpose(const int purpose_)
        {
            purpose = purpose_;
        }

#if PROTOCOL_VERSION > 375
        void SetRecipe(const Identifier& recipe_)
#else
        void SetRecipe(const int recipe_)
#endif
        {
            recipe = recipe_;
        }

        void SetGuiOpen(const bool gui_open_)
        {
            gui_open = gui_open_;
        }

        void SetFilteringCraftable(const bool filtering_craftable_)
        {
            filtering_craftable = filtering_craftable_;
        }

#if PROTOCOL_VERSION > 358
        void SetFurnaceGuiOpen(const bool furnace_gui_open_)
        {
            furnace_gui_open = furnace_gui_open_;
        }

        void SetFurnaceFilteringCraftable(const bool furnace_filtering_craftable_)
        {
            furnace_filtering_craftable = furnace_filtering_craftable_;
        }
#endif

#if PROTOCOL_VERSION > 450
        void SetBlastFurnaceGuiOpen(const bool blast_furnace_gui_open_)
        {
            blast_furnace_gui_open = blast_furnace_gui_open_;
        }

        void SetBlastFurnaceFilteringCraftable(const bool blast_furnace_filtering_craftable_)
        {
            blast_furnace_filtering_craftable = blast_furnace_filtering_craftable_;
        }

        void SetSmokerGuiOpen(const bool smoker_gui_open_)
        {
            smoker_gui_open = smoker_gui_open_;
        }

        void SetSmokerFilteringCraftable(const bool smoker_filtering_craftable_)
        {
            smoker_filtering_craftable = smoker_filtering_craftable_;
        }
#endif

        const int GetPurpose() const
        {
            return purpose;
        }

#if PROTOCOL_VERSION > 375
        const Identifier& GetRecipe() const
#else
        const int GetRecipe() const
#endif
        {
            return recipe;
        }

        const bool GetGuiOpen() const
        {
            return gui_open;
        }

        const bool GetFilteringCraftable() const
        {
            return filtering_craftable;
        }

#if PROTOCOL_VERSION > 358
        const bool GetFurnaceGuiOpen() const
        {
            return furnace_gui_open;
        }

        const bool GetFurnaceFilteringCraftable() const
        {
            return furnace_filtering_craftable;
        }
#endif

#if PROTOCOL_VERSION > 450
        const bool GetBlastFurnaceGuiOpen() const
        {
            return blast_furnace_gui_open;
        }

        const bool GetBlastFurnaceFilteringCraftable() const
        {
            return blast_furnace_filtering_craftable;
        }

        const bool GetSmokerGuiOpen() const
        {
            return smoker_gui_open;
        }

        const bool GetSmokerFilteringCraftable() const
        {
            return smoker_filtering_craftable;
        }
#endif

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            purpose = ReadVarInt(iter, length);
            switch (purpose)
            {
            case 0:
#if PROTOCOL_VERSION > 375
                recipe = ReadString(iter, length);
#else
                recipe = ReadVarInt(iter, length);
#endif
                break;
            case 1:
                gui_open = ReadData<bool>(iter, length);
                filtering_craftable = ReadData<bool>(iter, length);
#if PROTOCOL_VERSION > 358
                furnace_gui_open = ReadData<bool>(iter, length);
                furnace_filtering_craftable = ReadData<bool>(iter, length);
#endif
#if PROTOCOL_VERSION > 450
                blast_furnace_gui_open = ReadData<bool>(iter, length);
                blast_furnace_filtering_craftable = ReadData<bool>(iter, length);
                smoker_gui_open = ReadData<bool>(iter, length);
                smoker_filtering_craftable = ReadData<bool>(iter, length);
#endif
                break;
            default:
                break;
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteVarInt(purpose, container);
            switch (purpose)
            {
            case 0:
#if PROTOCOL_VERSION > 375
                WriteString(recipe, container);
#else
                WriteVarInt(recipe, container);
#endif
                break;
            case 1:
                WriteData<bool>(gui_open, container);
                WriteData<bool>(filtering_craftable, container);
#if PROTOCOL_VERSION > 358
                WriteData<bool>(furnace_gui_open, container);
                WriteData<bool>(furnace_filtering_craftable, container);
#endif
#if PROTOCOL_VERSION > 450
                WriteData<bool>(blast_furnace_gui_open, container);
                WriteData<bool>(blast_furnace_filtering_craftable, container);
                WriteData<bool>(smoker_gui_open, container);
                WriteData<bool>(smoker_filtering_craftable, container);
#endif
                break;
            default:
                break;
            }
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["purpose"] = picojson::value((double)purpose);
            switch (purpose)
            {
            case 0:
#if PROTOCOL_VERSION > 375
                object["recipe"] = picojson::value(recipe);
#else
                object["recipe"] = picojson::value((double)recipe);
#endif
                break;
            case 1:
                object["gui_open"] = picojson::value(gui_open);
                object["filtering_craftable"] = picojson::value(filtering_craftable);
#if PROTOCOL_VERSION > 358
                object["furnace_gui_open"] = picojson::value(furnace_gui_open);
                object["furnace_filtering_craftable"] = picojson::value(furnace_filtering_craftable);
#endif
#if PROTOCOL_VERSION > 450
                object["blast_furnace_gui_open"] = picojson::value(blast_furnace_gui_open);
                object["blast_furnace_filtering_craftable"] = picojson::value(blast_furnace_filtering_craftable);
                object["smoker_gui_open"] = picojson::value(smoker_gui_open);
                object["smoker_filtering_craftable"] = picojson::value(smoker_filtering_craftable);
#endif
                break;
            default:
                break;
            }

            return value;
        }

    private:
        int purpose;
#if PROTOCOL_VERSION > 375
        Identifier recipe;
#else
        int recipe;
#endif
        bool gui_open;
        bool filtering_craftable;
#if PROTOCOL_VERSION > 358
        bool furnace_gui_open;
        bool furnace_filtering_craftable;
#endif
#if PROTOCOL_VERSION > 450
        bool blast_furnace_gui_open;
        bool blast_furnace_filtering_craftable;
        bool smoker_gui_open;
        bool smoker_filtering_craftable;
#endif

    };
} //ProtocolCraft
#endif