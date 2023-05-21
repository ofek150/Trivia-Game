#pragma once
#include "IRequestHandler.h"

class RequestHandlerFactory;

class LoginRequestHandler : public IRequestHandler
{
public:
    LoginRequestHandler();

    bool isRequestRelevant(const RequestInfo& requestInfo) const override;
    RequestResult handleRequest(const RequestInfo& requestInfo) const override;

private:
    RequestResult login(const RequestInfo& requestInfo) const;
    RequestResult signup(const RequestInfo& requestInfo) const;

    RequestHandlerFactory& m_handlerFactory;
};
