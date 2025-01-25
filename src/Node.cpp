#include "Node.hpp"
#include "Option.hpp"

//-----
Node::Node() : mText(""), mOptions(), mNextNodeId(-1) {}

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
int Node::GetNextNodeId() const
{
    return mNextNodeId;
}

//-----
void Node::SetNextNode(int nextNodeId)
{
    mNextNodeId = nextNodeId;
}
