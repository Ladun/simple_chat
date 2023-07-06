#pragma once

#include "LDCore.hpp"

#include <boost/asio.hpp>

namespace net_core
{
    class CIOContext
    {
	private:
		CIOContext();

	public:
		~CIOContext();

		ErrCode run();
		void	stop();
		void	restart();

		template<typename THandler>
		auto bind_executor(THandler&& pHandler);
		template<typename THandler>
		void post(THandler&& pHandler);

		boost::asio::io_context&	get_io_context();
		static CIOContext&	instance();

	private:
		static CIOContext			        singleton_;

		boost::asio::io_context			    io_context_;
		boost::asio::io_context::strand	    strand_;
		boost::asio::io_context::work	    work_;
    };
}