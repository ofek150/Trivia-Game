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
        std::string buffer_str(reinterpret_cast<const char*>(requestInfo.buffer.data()), requestInfo.buffer.size());

        SignupRequest signupRequest = JsonRequestPacketDeserializer::getInstance().deserializeSignupRequest(buffer_str);
        SignupResponse signupResponse;
        signupResponse.status = ResponseCodes::SignupResponseCode;
        requestResult.responseBuffer = JsonRequestPacketSerializer::getInstance().serializeResponse(signupResponse);
    }
    else if(requestInfo.code == Login)
    {
        std::string buffer_str(reinterpret_cast<const char*>(requestInfo.buffer.data()), requestInfo.buffer.size());

        LoginRequest loginRequest = JsonRequestPacketDeserializer::getInstance().deserializeLoginRequest(buffer_str);
        LoginResponse loginResponse;
        loginResponse.status = ResponseCodes::LoginResponseCode;
        requestResult.responseBuffer = JsonRequestPacketSerializer::getInstance().serializeResponse(loginResponse);
    }



    return requestResult;
}

RequestResult LoginRequestHandler::login(RequestInfo requestInfo)
{
    return RequestResult();
}

RequestResult LoginRequestHandler::signup(RequestInfo requestInfo)
{
    return RequestResult();
}
