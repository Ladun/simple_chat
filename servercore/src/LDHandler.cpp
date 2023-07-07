#include "LDHandler.hpp"

namespace net_core
{

	ErrCode CMessageHandler::register_handler(MessageNo pNumber, HandlerType&& pHandler)
	{
		auto aResult = handler_list_.emplace(pNumber, pHandler);
		if (aResult.second == false)
			return eErrCodeAlreadyRegistered;

		return 0;
	}

	template<typename... TArgs>
	ErrCode CMessageHandler::process(MessageNo pNumber, TArgs... pArgs)
	{
		auto aIter = handler_list_.find(pNumber);
		if (aIter == handler_list_.end())
			return eErrCodeInvalidMessage;

		auto aResult = aIter->second(pArgs...);
		return aResult;
	}
}