#pragma once

#include "GameState.hpp"

#include <memory>

// Forward declarations
class IRenderer;
class Option;
// end

class GameManager
{
  public:
    GameManager(std::unique_ptr<IRenderer>& renderer,
                std::unique_ptr<Node>& startNode, int startQuanola);

    /**
     * Destructor.
     */
    ~GameManager();

    /**
     * The main loop of the game.
     */
    void Update();

    /**
     * Callback for the OnNext event.
     */
    void OnNext();

    /**
     * Callback for the OnOption event.
     */
    void OnOption(const Option& option);

  private:
    /**
     * The renderer for the game.
     */
    std::unique_ptr<IRenderer> mRenderer;

    /**
     * The starting node of the game.
     */
    std::unique_ptr<Node> mStartNode;

    /**
     * The current game state
     *
     */
    GameState mGameState;
};
