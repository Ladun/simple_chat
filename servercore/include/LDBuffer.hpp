#pragma once

#include "LDCore.hpp"

namespace net_core
{

    #pragma pack(push, 1)
    class BufferHeader
    {
    public:
        BufferHeader() = default;
        ~BufferHeader() = default;
    public:
        Size data_size = 0;
    };
    #pragma pack(pop)

    class Buffer
    {
    public:
        Buffer(Size size);
        ~Buffer();

        Buffer(const Buffer&) = delete;
        Buffer& operator=(const Buffer&) = delete;
        Buffer& operator=(const Buffer&&) = delete;

    public:
        bool push(const char* pData, Size size);
        char* front(Size& size, ErrCode& pErr);
        void pop();
        void clear();
        bool on_push(Size size);
        char* get_write_ptr();
        char* get_read_ptr();

        Size get_using_size() const { return use_size_; }
        Size get_usable_size() const { return MAX_SIZE - use_size_; }
        Size get_buffer_size() { return MAX_SIZE; }

        // TODO: remove
        char* get_buffer() { return buffer_; }

    protected:
        const Size      MAX_SIZE;
        Size    use_size_;
        int     read_index_;
        int     write_index_;
        char*   buffer_;
    };
}