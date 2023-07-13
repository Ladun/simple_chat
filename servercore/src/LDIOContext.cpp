#include "LDIOContext.hpp"

namespace net_core
{

	IOContext::IOContext() : io_context_(), strand_(io_context_), work_(io_context_)
	{
	}

	IOContext::~IOContext()
	{
	}

	ErrCode IOContext::run()
	{
		return io_context_.run();
	}

	void IOContext::stop()
	{
		io_context_.stop();
	}

	void IOContext::restart()
	{
		io_context_.restart();
	}
}