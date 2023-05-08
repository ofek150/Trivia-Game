#include "MenuRequestHandler.h"
#include "RequestHandlerFactory.h"

MenuRequestHandler::MenuRequestHandler() : m_handlerFactory(RequestHandlerFactory::getInstance()) {}

bool MenuRequestHandler::isRequestRelevant(const RequestInfo& requestInfo)
{
	return false;
}

RequestResult MenuRequestHandler::handleRequest(const RequestInfo& requestInfo)
{
	return RequestResult();
}