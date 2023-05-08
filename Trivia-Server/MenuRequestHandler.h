#pragma once
#include "IRequestHandler.h"
#include "RequestCodes.h"

class RequestHandlerFactory;

class MenuRequestHandler : public IRequestHandler
{
public:
    MenuRequestHandler();

    bool isRequestRelevant(const RequestInfo& requestInfo) override;
    RequestResult handleRequest(const RequestInfo& requestInfo) override;

private:
    RequestHandlerFactory& m_handlerFactory;
};
