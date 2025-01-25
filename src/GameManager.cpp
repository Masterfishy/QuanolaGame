#include "GameManager.hpp"
#include "IRenderer.hpp"
#include "Node.hpp"
#include "Option.hpp"

#include <iostream>

//-----
GameManager::GameManager(std::unique_ptr<IRenderer>& renderer,
                         std::map<int, std::unique_ptr<Node>>& nodes,
                         int startQuanola)
    : mRenderer(std::move(renderer)), mGameNodes(std::move(nodes))
{
    const auto& startNode = mGameNodes.find(0);
    if (startNode == mGameNodes.end())
    {
        // If there is no start node we are done
        return;
    }

    mGameState.node = startNode->second.get();
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
        int nextId = mGameState.node->GetNextNodeId();

        const auto& nextNode = mGameNodes.find(nextId);
        if (nextNode == mGameNodes.end())
        {
            mGameState.node = nullptr;
        }
        else
        {
            mGameState.node = nextNode->second.get();
        }
    }
}

//-----
void GameManager::OnOption(const Option& option)
{
    mGameState.quanola -= option.GetQuanolaCost();

    int nodeId = option.GetNode();

    const auto& node = mGameNodes.find(nodeId);
    if (node == mGameNodes.end())
    {
        // TODO handle this case better
        mGameState.node = nullptr;
    }
    else
    {
        mGameState.node = node->second.get();
    }
}
