#include "LoginRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "MenuRequestHandler.h"

LoginRequestHandler::LoginRequestHandler() : m_handlerFactory(RequestHandlerFactory::getInstance()),
                                             m_loginManager(LoginManager::getInstance())
{
}

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
	if (requestInfo.code == LoginRequestCode)
	{
		return login(requestInfo);
	}
}

RequestResult LoginRequestHandler::login(const RequestInfo& requestInfo) const
{
	RequestResult requestResult;
	LoginResponse loginResponse;
	try
	{
		LoginRequest loginRequest = JsonRequestPacketDeserializer::getInstance().deserializeLoginRequest(
			requestInfo.buffer);
		m_loginManager.login(loginRequest.username, loginRequest.password);
		loginResponse.status = SUCCESSFUL;
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
	try
	{
		SignupRequest signupRequest = JsonRequestPacketDeserializer::getInstance().deserializeSignupRequest(
			requestInfo.buffer);
		m_loginManager.signup(signupRequest.username, signupRequest.password, signupRequest.email);

		requestResult.newHandler = m_handlerFactory.createMenuRequestHandler(signupRequest.username);

		signupResponse.status = SUCCESSFUL;
		requestResult.responseBuffer = JsonRequestPacketSerializer::getInstance().serializeResponse(signupResponse);
	}
	catch (const std::exception& e)
	{
		requestResult = ErrorResult(e);
	}

	return requestResult;
}
