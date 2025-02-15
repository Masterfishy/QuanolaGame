#include "CliRenderer.hpp"
#include "GameManager.hpp"
#include "Node.hpp"
#include "Option.hpp"
#include "Serializer.hpp"

#include <iostream>

#include <signal.h>

bool gShutdown = false;

/**
 * Handle the SIGINT signal to gracefully shutdown.
 */
extern "C" void signalHandler(int signum)
{
    gShutdown = true;
}

int main()
{
    // Set up signal control
    signal(SIGINT, signalHandler);

    // Deserialize node data.
    Serializer::NodeCollection nodes;
    Serializer::LoadNodesFromFile("./build/nodedata.json", nodes);

    // Create game objects
    std::unique_ptr<IRenderer>   renderer = std::make_unique<CliRenderer>();
    std::unique_ptr<GameManager> gm =
        std::make_unique<GameManager>(renderer, nodes, 200);

    // Run the game
    while (!gShutdown)
    {
        gm->Update();
    }

    return 0;
}