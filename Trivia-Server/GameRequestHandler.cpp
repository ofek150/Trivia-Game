#include "GameRequestHandler.h"
#include "RequestCodes.h"
#include "MenuRequestHandler.h"


bool GameRequestHandler::isRequestRelevant(const RequestInfo& requestInfo) const
{
	return requestInfo.code == GetGameResultsRequestCode || requestInfo.code == SubmitAnswerRequestCode ||
		requestInfo.code == GetQuestionRequestCode || requestInfo.code == LeaveGameRequestCode;
}

RequestResult GameRequestHandler::handleRequest(const RequestInfo& requestInfo) const
{
	switch (requestInfo.code)
	{
	case GetGameResultsRequestCode:
		return getGameResults(requestInfo);
	case SubmitAnswerRequestCode:
		return submitAnswer(requestInfo);
	case GetQuestionRequestCode:
		return getQuestion(requestInfo);
	case LeaveGameRequestCode:
		return leaveGame(requestInfo);
	}
}

RequestResult GameRequestHandler::getQuestion(const RequestInfo& requestInfo) const
{
	RequestResult requestResult;
	GetQuestionResponse getQuestionResponse;
	try
	{
		Question question = m_game.getCurrentQuestion();
		getQuestionResponse.question = question.getQuestion();
		getQuestionResponse.answers = question.getPossibleAnswers();
		getQuestionResponse.status = SUCCESSFUL;
		requestResult.responseBuffer = JsonRequestPacketSerializer::getInstance().
			serializeResponse(getQuestionResponse);
		requestResult.newHandler = m_handlerFactory.createGameRequestHandler(m_user.getUsername(), m_game);
	}
	catch (const std::exception& e)
	{
		requestResult = ErrorResult(e);
	}
	return requestResult;
}

RequestResult GameRequestHandler::submitAnswer(const RequestInfo& requestInfo) const
{
	RequestResult requestResult;
	SubmitAnswerResponse submitAnswerResponse;
	try
	{
		SubmitAnswerRequest submitAnswerRequest = JsonRequestPacketDeserializer::getInstance().
			deserializeSubmitAnswerRequest(requestInfo.buffer);
		m_game.submitAnswer(m_user, submitAnswerRequest.answerId);
		submitAnswerResponse.correctsAnswerId = m_game.getCurrentQuestion().getCorrectAnswerId();
		submitAnswerResponse.status = SUCCESSFUL;
		requestResult.responseBuffer = JsonRequestPacketSerializer::getInstance().serializeResponse(
			submitAnswerResponse);
		requestResult.newHandler = m_handlerFactory.createGameRequestHandler(m_user.getUsername(), m_game);
	}
	catch (const std::exception& e)
	{
		requestResult = ErrorResult(e);
	}
	return requestResult;
}

RequestResult GameRequestHandler::getGameResults(const RequestInfo& requestInfo) const
{
	RequestResult requestResult;
	GetGameResultsResponse getGameResultsResponse;
	try
	{
		getGameResultsResponse.results = m_game.getPlayersResults();
		getGameResultsResponse.status = SUCCESSFUL;
		requestResult.newHandler = m_handlerFactory.createGameRequestHandler(m_user.getUsername(), m_game);
	}
	catch (const std::exception& e)
	{
		requestResult = ErrorResult(e);
	}
	return requestResult;
}

RequestResult GameRequestHandler::leaveGame(const RequestInfo& requestInfo) const
{
	RequestResult requestResult;
	LeaveGameResponse leaveGameResponse;
	try
	{
		m_game.removePlayer(m_user);
		leaveGameResponse.status = SUCCESSFUL;
		requestResult.responseBuffer = JsonRequestPacketSerializer::getInstance().serializeResponse(leaveGameResponse);
		requestResult.newHandler = m_handlerFactory.createMenuRequestHandler(m_user.getUsername());
	}
	catch (const std::exception& e)
	{
		requestResult = ErrorResult(e);
	}
	return requestResult;
}
