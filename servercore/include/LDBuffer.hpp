#pragma once

#include "LDCore.hpp"

namespace net_core
{

    class CBufferHeader
    {
    public:
        CBufferHeader() = default;
        ~CBufferHeader() = default;
    public:
        Size data_size = 0;
    };

    class CBuffer
    {
    public:
        CBuffer(Size size);
        ~CBuffer();

        CBuffer(const CBuffer&) = delete;
        CBuffer& operator=(const CBuffer&) = delete;
        CBuffer& operator=(const CBuffer&&) = delete;

    public:
        bool push(const char* pData, Size size);
        char* front(Size& size, ErrCode& pErr);
        void pop();
        void clear();
        bool on_push(Size size);
        char* get_write_ptr();

        Size get_using_size() const { return use_size_; }
        Size get_usable_size() const { return MAX_SIZE - use_size_; }
        Size get_buffer_size() { return MAX_SIZE; }

    protected:
        const Size      MAX_SIZE;
        Size    use_size_;
        int     read_index_;
        int     write_index_;
        char*   buffer_;
    };
}