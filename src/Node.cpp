#include "Node.hpp"
#include "Option.hpp"

//-----
Node::Node() : mText(""), mOptions(), mNextNode(nullptr) {}

//-----
Node::~Node() {}

//-----
const std::string& Node::GetText() const
{
    return mText;
}

//-----
void Node::SetText(const std::string& text)
{
    mText = text;
}

//-----
const std::vector<Option>& Node::GetOptions() const
{
    return mOptions;
}

//-----
void Node::AddOption(Option& option)
{
    mOptions.emplace_back(option);
}

//-----
const Node* const Node::GetNextNode() const
{
    return mNextNode;
}

//-----
void Node::SetNextNode(Node* nextNode)
{
    mNextNode = nextNode;
}
