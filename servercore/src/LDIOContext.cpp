#include "LDIOContext.hpp"

namespace net_core
{

	CIOContext::CIOContext() : io_context_(), strand_(io_context_), work_(io_context_)
	{
	}

	CIOContext::~CIOContext()
	{
	}

	ErrCode CIOContext::run()
	{
		return io_context_.run();
	}

	void CIOContext::stop()
	{
		io_context_.stop();
	}

	void CIOContext::restart()
	{
		io_context_.restart();
	}
}