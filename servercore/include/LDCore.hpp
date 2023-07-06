
namespace net_core
{
    using Size = unsigned short;

	/**
		@brief 에러코드 타입
	*/
    using ErrCode = std::size_t;
}

#define LD_ERRCODE(pErr) const net_core::ErrCode pErr = std::hash<std::string>{}(#pErr)   

#include "LDError.hpp"