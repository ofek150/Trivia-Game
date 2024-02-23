#pragma once
#include "IRequestHandler.h"
#include <string>
#include "LoggedUser.h"
#include "Game.h"
#include "GameManager.h"
#include "RequestHandlerFactory.h"

class RequestHandlerFactory;

class GameRequestHandler : public IRequestHandler
{
public:
	GameRequestHandler(std::string username, Game& game) : m_user(username),
	                                                       m_handlerFactory(RequestHandlerFactory::getInstance()),
	                                                       m_game(game), m_gameManager(GameManager::getInstance())
	{
	};

	bool isRequestRelevant(const RequestInfo& requestInfo) const override;
	RequestResult handleRequest(const RequestInfo& requestInfo) const override;
	RequestResult getQuestion(const RequestInfo& requestInfo) const;
	RequestResult submitAnswer(const RequestInfo& requestInfo) const;
	RequestResult getGameResults(const RequestInfo& requestInfo) const;
	RequestResult leaveGame(const RequestInfo& requestInfo) const;

private:
	LoggedUser m_user;
	RequestHandlerFactory& m_handlerFactory;
	Game& m_game;
	GameManager& m_gameManager;
};
