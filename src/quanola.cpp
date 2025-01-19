#include "CliRenderer.hpp"
#include "GameManager.hpp"
#include "Node.hpp"
#include "Option.hpp"

#include <iostream>

int main()
{
    std::unique_ptr<Node> startNode;
    std::unique_ptr<Node> rightNode;
    std::unique_ptr<Node> leftNode;
    std::unique_ptr<Node> nextNode;

    startNode = std::make_unique<Node>();
    rightNode = std::make_unique<Node>();
    leftNode = std::make_unique<Node>();
    nextNode = std::make_unique<Node>();

    startNode->SetText("You wake up so woke.");
    startNode->SetNextNode(nextNode.get());

    Option rightOption;
    rightOption.SetText("Go back to sleep.");
    rightOption.SetNode(rightNode.get());
    rightOption.SetQuanolaCost(1);

    Option leftOption;
    leftOption.SetText("Try to get out of bed.");
    leftOption.SetNode(leftNode.get());
    leftOption.SetQuanolaCost(3);

    startNode->AddOption(rightOption);
    startNode->AddOption(leftOption);

    rightNode->SetText("You lay back down.");
    rightNode->SetNextNode(nextNode.get());

    leftNode->SetText(
        "You try to get out of bed but you aren't fooling anyone.");
    leftNode->SetNextNode(nextNode.get());

    nextNode->SetText("You fall deeply asleep");
    nextNode->SetNextNode(startNode.get());

    std::unique_ptr<IRenderer> renderer = std::make_unique<CliRenderer>();
    std::unique_ptr<GameManager> gm =
        std::make_unique<GameManager>(renderer, startNode, 200);

    while (true)
    {
        gm->Update();
    }

    return 0;
}