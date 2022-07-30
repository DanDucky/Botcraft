#if PROTOCOL_VERSION > 758
#include "botcraft/Game/Entities/entities/animal/frog/FrogEntity.hpp"

namespace Botcraft
{
    const std::array<std::string, FrogEntity::metadata_count> FrogEntity::metadata_names{ {
        "data_variant_id",
        "data_tongue_target_id",
    } };

    FrogEntity::FrogEntity()
    {
        // Initialize all metadata with default values
        SetDataVariantId(0);
        SetDataTongueTargetId(std::optional<int>());
    }

    FrogEntity::~FrogEntity()
    {

    }


    std::string FrogEntity::GetName() const
    {
        return "Frog";
    }

    EntityType FrogEntity::GetType() const
    {
        return EntityType::Frog;
    }

    double FrogEntity::GetWidth() const
    {
        return 0.5;
    }

    double FrogEntity::GetHeight() const
    {
        return 0.5;
    }


    std::string FrogEntity::GetClassName()
    {
        return "Frog";
    }

    EntityType FrogEntity::GetClassType()
    {
        return EntityType::Frog;
    }


    nlohmann::json FrogEntity::Serialize() const
    {
        nlohmann::json output = AnimalEntity::Serialize();

        output["metadata"]["data_variant_id"] = GetDataVariantId();
        output["metadata"]["data_tongue_target_id"] = GetDataTongueTargetId() ? nlohmann::json(GetDataTongueTargetId().value()) : nlohmann::json();

        return output;
    }


    void FrogEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            AnimalEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    const int FrogEntity::GetDataVariantId() const
    {
        return std::any_cast<int>(metadata.at("data_variant_id"));
    }

    const std::optional<int>& FrogEntity::GetDataTongueTargetId() const
    {
        return std::any_cast<const std::optional<int>&>(metadata.at("data_tongue_target_id"));
    }


    void FrogEntity::SetDataVariantId(const int data_variant_id)
    {
        metadata["data_variant_id"] = data_variant_id;
    }

    void FrogEntity::SetDataTongueTargetId(const std::optional<int>& data_tongue_target_id)
    {
        metadata["data_tongue_target_id"] = data_tongue_target_id;
    }

}
#endif