#include "LoginRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"

LoginRequestHandler::LoginRequestHandler() : m_handlerFactory(RequestHandlerFactory::getInstance()) {}

bool LoginRequestHandler::isRequestRelevant(const RequestInfo& requestInfo)
{
    return (requestInfo.code == Signup || requestInfo.code == Login);
}

RequestResult LoginRequestHandler::handleRequest(const RequestInfo& requestInfo)
{
    if (requestInfo.code == Signup)
    {
        return signup(requestInfo);
    }
    else if(requestInfo.code == Login)
    {
        return login(requestInfo);
    }
}

RequestResult LoginRequestHandler::login(const RequestInfo& requestInfo)
{
    RequestResult requestResult;
    LoginResponse loginResponse;
    requestResult.newHandler = m_handlerFactory.createLoginRequestHandler();
    try {
        LoginManager& loginManager = m_handlerFactory.getLoginManager();

        LoginRequest loginRequest = JsonRequestPacketDeserializer::getInstance().deserializeLoginRequest(requestInfo.buffer);
        loginManager.login(loginRequest.username, loginRequest.password);

        loginResponse.status = StatusCodes::SUCCESSFUL;
        requestResult.responseBuffer = JsonRequestPacketSerializer::getInstance().serializeResponse(loginResponse);
    }
    catch (std::exception e)
    {
        ErrorResponse errorResponse;
        errorResponse.errorMessage = e.what();
        std::cerr << e.what() << std::endl;
        requestResult.responseBuffer = JsonRequestPacketSerializer::getInstance().serializeResponse(errorResponse);
    }
    catch (...)
    {
        loginResponse.status = StatusCodes::FAILED;
    }

    return requestResult;
    
}

RequestResult LoginRequestHandler::signup(const RequestInfo& requestInfo)
{
    RequestResult requestResult;
    LoginResponse signupResponse;
    requestResult.newHandler = m_handlerFactory.createLoginRequestHandler();
    try {
        LoginManager& loginManager = m_handlerFactory.getLoginManager();

        SignupRequest signupRequest = JsonRequestPacketDeserializer::getInstance().deserializeSignupRequest(requestInfo.buffer);
        loginManager.signup(signupRequest.username, signupRequest.password, signupRequest.email);

        signupResponse.status = StatusCodes::SUCCESSFUL;
        requestResult.responseBuffer = JsonRequestPacketSerializer::getInstance().serializeResponse(signupResponse);
    }
    catch (std::exception e)
    {
        ErrorResponse errorResponse;
        errorResponse.errorMessage = e.what();
        std::cerr << e.what() << std::endl;
        requestResult.responseBuffer = JsonRequestPacketSerializer::getInstance().serializeResponse(errorResponse);
    }
    catch (...)
    {
        signupResponse.status = StatusCodes::FAILED;
    }

    return requestResult;
}
