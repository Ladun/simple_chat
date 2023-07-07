
namespace net_core
{
    using Size = unsigned short;

	#pragma region Constant
	constexpr Size eSzPacketMax		= 0x3FFF;	// 한 패킷당 최대 사이즈
	#pragma endregion

	/**
		@brief 에러코드 타입
	*/
    using ErrCode = std::size_t;
}

#define LD_ERRCODE(pErr) const net_core::ErrCode pErr = std::hash<std::string>{}(#pErr)   

#include "LDError.hpp"