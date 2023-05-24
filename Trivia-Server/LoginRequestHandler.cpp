#include "LoginRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "MenuRequestHandler.h"

LoginRequestHandler::LoginRequestHandler() : m_handlerFactory(RequestHandlerFactory::getInstance()), IRequestHandler("") {}

bool LoginRequestHandler::isRequestRelevant(const RequestInfo& requestInfo) const
{
    return (requestInfo.code == SignupRequestCode || requestInfo.code == LoginRequestCode);
}

RequestResult LoginRequestHandler::handleRequest(const RequestInfo& requestInfo) const
{
    if (requestInfo.code == SignupRequestCode)
    {
        return signup(requestInfo);
    }
    else if(requestInfo.code == LoginRequestCode)
    {
        return login(requestInfo);
    }
}

RequestResult LoginRequestHandler::login(const RequestInfo& requestInfo) const
{
    RequestResult requestResult;
    LoginResponse loginResponse;
    try {
        LoginManager& loginManager = m_handlerFactory.getLoginManager();
        LoginRequest loginRequest = JsonRequestPacketDeserializer::getInstance().deserializeLoginRequest(requestInfo.buffer);
        if (loginRequest.username == "") throw std::exception("Username can't be empty!");
        if (loginRequest.password == "") throw std::exception("Password can't be empty!");
        loginManager.login(loginRequest.username, loginRequest.password);
        loginResponse.status = StatusCodes::SUCCESSFUL;
        requestResult.responseBuffer = JsonRequestPacketSerializer::getInstance().serializeResponse(loginResponse);
        requestResult.newHandler = m_handlerFactory.createMenuRequestHandler(loginRequest.username);
    }
    catch (const std::exception& e)
    {
        requestResult = ErrorResult(e);
    }

    return requestResult;
    
}

RequestResult LoginRequestHandler::signup(const RequestInfo& requestInfo) const
{
    RequestResult requestResult;
    LoginResponse signupResponse;
    try {
        LoginManager& loginManager = m_handlerFactory.getLoginManager();

        SignupRequest signupRequest = JsonRequestPacketDeserializer::getInstance().deserializeSignupRequest(requestInfo.buffer);
        if (signupRequest.username == "") throw std::exception("Username can't be empty!");
        if (signupRequest.password == "") throw std::exception("Password can't be empty!");
        loginManager.signup(signupRequest.username, signupRequest.password, signupRequest.email);

        requestResult.newHandler = m_handlerFactory.createMenuRequestHandler(signupRequest.username);

        signupResponse.status = StatusCodes::SUCCESSFUL;
        requestResult.responseBuffer = JsonRequestPacketSerializer::getInstance().serializeResponse(signupResponse);
    }
    catch (const std::exception& e)
    {
        requestResult = ErrorResult(e);
    }

    return requestResult;
}