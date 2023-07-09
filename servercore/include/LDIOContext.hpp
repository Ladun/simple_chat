#pragma once

#include <boost/asio.hpp>

#include "LDCore.hpp"


namespace net_core
{
    class CIOContext : public Singleton<CIOContext>
    {
	public:
		CIOContext();
		~CIOContext();

		ErrCode run();
		void	stop();
		void	restart();

		template<typename THandler>
		auto bind_executor(THandler&& pHandler);
		template<typename THandler>
		void post(THandler&& pHandler);

		boost::asio::io_context& get_io_context() { return io_context_; }
		boost::asio::io_context::strand& get_strand() { return strand_; }

	private:
		boost::asio::io_context			    io_context_;
		boost::asio::io_context::strand	    strand_;
		boost::asio::io_context::work	    work_;
    };
}