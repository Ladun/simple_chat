#pragma once

#include <vector>

namespace net_core
{   

    #pragma pack(push, 1)
    template <typename T>
    struct MessageHeader
    {
        T id{};
        uint32_t size = 0;
    };
    #pragma pack(pop)

    template <typename T>
    struct Message
    {
        // Header & Body vector
        MessageHeader<T> header{};
        std::vector<uint8_t> body;

        // returns size of entire Message packet in bytes
        size_t size() const
        {
            return body.size();
        }

        // Override for std::cout compatibility - produces friendly description of Message
        friend std::ostream& operator << (std::ostream& os, const Message<T>& msg)
        {
            os << "ID:" << int(msg.header.id) << " Size:" << msg.header.size;
            return os;
        }

        // Convenience Operator overloads - These allow us to add and remove stuff from
        // the body vector as if it were a stack, so First in, Last Out. These are a 
        // template in itself, because we dont know what data type the user is pushing or 
        // popping, so lets allow them all. NOTE: It assumes the data type is fundamentally
        // Plain Old Data (POD). TLDR: Serialise & Deserialise into/from a vector

        // Pushes any POD-like data into the Message buffer
        template<typename DataType>
        friend Message<T>& operator << (Message<T>& msg, const DataType& data)
        {
            // Check that the type of the data being pushed is trivially copyable
            static_assert(std::is_standard_layout<DataType>::value, "Data is too complex to be pushed into vector");

            // Cache current size of vector, as this will be the point we insert the data
            size_t i = msg.body.size();

            // Resize the vector by the size of the data being pushed
            msg.body.resize(msg.body.size() + sizeof(DataType));

            // Physically copy the data into the newly allocated vector space
            std::memcpy(msg.body.data() + i, &data, sizeof(DataType));

            // Recalculate the Message size
            msg.header.size = msg.size();

            // Return the target Message so it can be "chained"
            return msg;
        }

        // Pulls any POD-like data form the Message buffer
        template<typename DataType>
        friend Message<T>& operator >> (Message<T>& msg, DataType& data)
        {
            // Check that the type of the data being pushed is trivially copyable
            static_assert(std::is_standard_layout<DataType>::value, "Data is too complex to be pulled from vector");

            // Cache the location towards the end of the vector where the pulled data starts
            size_t i = msg.body.size() - sizeof(DataType);

            // Physically copy the data from the vector into the user variable
            std::memcpy(&data, msg.body.data() + i, sizeof(DataType));

            // Shrink the vector to remove read bytes, and reset end position
            msg.body.resize(i);

            // Recalculate the Message size
            msg.header.size = msg.size();

            // Return the target Message so it can be "chained"
            return msg;
        }			
    };


    // An "owned" Message is identical to a regular Message, but it is associated with
    // a connection. On a server, the owner would be the client that sent the Message, 
    // on a client the owner would be the server.

    // Forward declare the connection
    class Session;

    template <typename T>
    struct OwnedMessage
    {
        std::shared_ptr<Session> remote = nullptr;
        Message<T> msg;

        // Again, a friendly string maker
        friend std::ostream& operator<<(std::ostream& os, const OwnedMessage<T>& msg)
        {
            os << msg.msg;
            return os;
        }
    };		
}