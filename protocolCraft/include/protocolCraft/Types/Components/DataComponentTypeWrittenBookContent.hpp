#pragma once
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Types/Components/DataComponentType.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

#include <string>
#include <vector>

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeWrittenBookContent : public DataComponentType
        {
        public:
            virtual ~DataComponentTypeWrittenBookContent()
            {

            }

            const std::string& GetTitle() const
            {
                return title;
            }

            const std::string& GetAuthor() const
            {
                return author;
            }

            int GetGeneration() const
            {
                return generation;
            }

            const std::vector<Chat>& GetPages() const
            {
                return pages;
            }

            bool GetResolved() const
            {
                return resolved;
            }


            void SetTitle(const std::string& title_)
            {
                title = title_;
            }

            void SetAuthor(const std::string& author_)
            {
                author = author_;
            }

            void SetGeneration(const int generation_)
            {
                generation = generation_;
            }

            void SetPages(const std::vector<Chat>& pages_)
            {
                pages = pages_;
            }

            void SetResolved(const bool resolved_)
            {
                resolved = resolved_;
            }

        protected:
            virtual void ReadImpl(ReadIterator& iter, size_t& length) override
            {
                title = ReadData<std::string>(iter, length);
                author = ReadData<std::string>(iter, length);
                generation = ReadData<VarInt>(iter, length);
                pages = ReadVector<Chat>(iter, length);
                resolved = ReadData<bool>(iter, length);
            }

            virtual void WriteImpl(WriteContainer& container) const override
            {
                WriteData<std::string>(title, container);
                WriteData<std::string>(author, container);
                WriteData<VarInt>(generation, container);
                WriteVector<Chat>(pages, container);
                WriteData<bool>(resolved, container);
            }

            virtual Json::Value SerializeImpl() const override
            {
                Json::Value output;

                output["title"] = title;
                output["author"] = author;
                output["generation"] = generation;
                output["pages"] = pages;
                output["resolved"] = resolved;

                return output;
            }

        private:
            //TODO: check title and pages, weird codec stuff with filterable
            std::string title;
            std::string author;
            int generation = 0;
            std::vector<Chat> pages;
            bool resolved = false;

        };
    }
}
#endif