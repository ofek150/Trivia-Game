#include "LoginRequestHandler.h"

bool LoginRequestHandler::isRequestRelevant(RequestInfo requestInfo)
{
    return (requestInfo.code == Signup || requestInfo.code == Login);
}

RequestResult LoginRequestHandler::handleRequest(RequestInfo requestInfo)
{
    RequestResult requestResult;
    IRequestHandler* newHandler;

    if (requestInfo.code == Signup)
    {
        //Call Signup handler
    }
    else if(requestInfo.code == Login)
    {
        //Call Login handler
    }
    return requestResult;
}
