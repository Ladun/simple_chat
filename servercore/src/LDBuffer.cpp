
#include "pch.hpp"
#include "LDBuffer.hpp"

namespace net_core
{
    Buffer::Buffer(Size size)
        : MAX_SIZE(size), use_size_(0), 
          read_index_(0), write_index_(0), buffer_(nullptr)
    {
        buffer_ = new char[MAX_SIZE];
        ::memset(buffer_, 0, MAX_SIZE);
    }

    Buffer::~Buffer()
    {
        delete[] buffer_;
    }

    bool Buffer::push(const char* data, Size size)
    {
        Size data_size = static_cast<Size>(sizeof(BufferHeader)) + size;
        if(data_size > get_usable_size())
            return false;

        reinterpret_cast<BufferHeader*>(buffer_ + write_index_)->data_size = size;
        //::memcpy_s(buffer_ + write_index_ + sizeof(BufferHeader), get_usable_size() - sizeof(BufferHeader), data, size);
        ::memcpy(buffer_ + write_index_ + sizeof(BufferHeader), data, size);
        use_size_ += size + sizeof(BufferHeader);
        write_index_ += static_cast<int>(size) + sizeof(BufferHeader);
        
        return true;
    }

    char* Buffer::front(Size& size, ErrCode& pErr)
    {
        if(static_cast<int>(use_size_) - read_index_ < static_cast<int>(sizeof(BufferHeader)))
            return nullptr;

        pErr = 0;
        char* data = buffer_ + read_index_;
        size = reinterpret_cast<BufferHeader*>(data)->data_size;
        data += sizeof(BufferHeader);

        // 읽을 데이터의 크기가 Buffer에서 보관할 수 있는 최대 크기보다
        // 크다면 Error
        if(size > MAX_SIZE - sizeof(BufferHeader))
        {
            pErr = eErrCodeSessionBufferFull;
            return nullptr;
        }

        // 읽을 데이터의 크기가 실제 데이터 크기와 다르다면
        if(size > use_size_ - static_cast<Size>(read_index_) - sizeof(BufferHeader))
        {
            pErr = eErrCodeInvalidSize;
            return nullptr;
        }
        
        read_index_ += (static_cast<int>(size) + static_cast<int>(sizeof(BufferHeader)));
        return data;
    }

    void Buffer::pop()
    {
        // memmove_s(void *dest, rsize_t destsz, const void *src, rsize_t count);
        // ::memmove_s(buffer_, MAX_SIZE, buffer_ + read_index_, MAX_SIZE - read_index_);
        ::memmove(buffer_, buffer_ + read_index_, MAX_SIZE - read_index_);

        write_index_    -= read_index_;
        use_size_       -= static_cast<int>(read_index_);
        read_index_     = 0;

    }

    void Buffer::clear()
    {
        read_index_     = 0;
        use_size_       = 0;
        write_index_    = 0;
    }

    bool Buffer::on_push(Size size)
    {
        if(write_index_ + size > MAX_SIZE)
            return false;

        write_index_ += static_cast<int>(size);
        use_size_    += size;

        return true;
    }

    char* Buffer::get_read_ptr()
    {
        if(static_cast<int>(use_size_) - read_index_ < static_cast<int>(sizeof(BufferHeader)))
            return nullptr;
        return  buffer_ + read_index_;
    }

    char* Buffer::get_write_ptr()
    {
        return &(buffer_[write_index_]);
    }
}