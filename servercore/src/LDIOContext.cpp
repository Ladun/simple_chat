#include "LDIOContext.hpp"

namespace net_core
{

	CIOContext CIOContext::singleton_;

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

	boost::asio::io_context& CIOContext::get_io_context()
	{
		return io_context_;
	}

	CIOContext& CIOContext::instance()
	{
		return singleton_;
	}

	template<typename THandler>
	auto CIOContext::bind_executor(THandler&& pHandler)
	{
		return boost::asio::bind_executor(strand_, pHandler);
	}

	template<typename THandler>
	void CIOContext::post(THandler&& pHandler)
	{
		return io_context_.post(strand_, pHandler);
	}

}