#include "protocolCraft/Types/NBT/TagLongArray.hpp"

namespace ProtocolCraft
{
    TagLongArray::TagLongArray()
    {

    }

    TagLongArray::~TagLongArray()
    {

    }

    const std::vector<long long int>& TagLongArray::GetValues() const
    {
        return values;
    }

    void TagLongArray::SetValues(const std::vector<long long int> &v)
    {
        values = v;
    }

    const TagType TagLongArray::GetType() const
    {
        return TagType::LongArray;
    }

    void TagLongArray::ReadImpl(ReadIterator &iterator, size_t &length)
    {
        values = ReadVector<long long int, int>(iterator, length);
    }

    void TagLongArray::WriteImpl(WriteContainer &container) const
    {
        WriteVector<long long int, int>(values, container);
    }

    const nlohmann::json TagLongArray::SerializeImpl() const
    {
        return nlohmann::json(values);
    }
}
