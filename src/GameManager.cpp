#include "GameManager.hpp"
#include "IRenderer.hpp"
#include "Node.hpp"
#include "Option.hpp"

#include <iostream>

//-----
GameManager::GameManager(std::unique_ptr<IRenderer>& renderer,
                         std::unique_ptr<Node>& startNode, int startQuanola)
    : mRenderer(std::move(renderer)), mStartNode(std::move(startNode))
{
    mGameState.node = mStartNode.get();
    mGameState.quanola = startQuanola;

    mRenderer->OnNextEvent.AddListener(this, &GameManager::OnNext);
    mRenderer->OnOptionEvent.AddListener(this, &GameManager::OnOption);
}

//-----
GameManager::~GameManager()
{
    // TODO Clean up the nodes?
}

//-----
void GameManager::Update()
{
    if (mRenderer != nullptr)
    {
        mRenderer->Render(mGameState);
    }
}

//-----
void GameManager::OnNext()
{
    if (mGameState.node != nullptr)
    {
        mGameState.node = mGameState.node->GetNextNode();
    }
}

//-----
void GameManager::OnOption(const Option& option)
{
    mGameState.quanola -= option.GetQuanolaCost();
    mGameState.node = option.GetNode();
}
