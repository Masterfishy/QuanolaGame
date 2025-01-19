#include "CliRenderer.hpp"
#include "GameState.hpp"
#include "Node.hpp"
#include "Option.hpp"

#include <algorithm>
#include <iostream>

//-----
CliRenderer::CliRenderer() {}

//-----
CliRenderer::~CliRenderer() {}

//-----
void CliRenderer::Render(const GameState& state)
{
    if (state.node == nullptr)
    {
        return;
    }

    // Render the node's text
    std::cout << "Quanola: " << state.quanola << std::endl;
    std::cout << state.node->GetText() << std::endl;

    // Render the options
    const std::vector<Option>& options = state.node->GetOptions();
    if (options.empty())
    {
        std::cout << " >> Continue" << std::endl;
    }
    else
    {
        std::cout << " > What will you do?" << std::endl;
    }

    for (int i = 0; i < options.size(); i++)
    {
        std::cout << " [" << i + 1 << "] > " << options[i].GetText()
                  << std::endl;
    }

    // Get the response
    std::string response;
    std::cout << "> ";
    std::getline(std::cin, response);

    // Handle next
    if (options.empty())
    {
        // Go to next node
        OnNextEvent.Invoke();
        return;
    }

    // Invalid option selection
    if (!IsPositiveInt(response))
    {
        std::cout << "Sorry, that is not an option." << std::endl;
        return;
    }

    // Handle option selection
    int responseInt = std::stoi(response);
    if (0 >= responseInt || responseInt - 1 >= options.size())
    {
        std::cout << "Sorry, that is not an option." << std::endl;
        return;
    }

    // Invoke OnOption
    OnOptionEvent.Invoke(options[responseInt - 1]);
}

//-----
bool CliRenderer::IsPositiveInt(const std::string& numberStr)
{
    if (numberStr.empty())
    {
        return false;
    }

    return std::find_if(numberStr.begin(), numberStr.end(),
                        [](const auto& c)
                        { return !std::isdigit(c); }) == numberStr.end();
}
