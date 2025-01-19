#include "Option.hpp"

//-----
Option::Option() : mCost(0), mText(""), mNode(nullptr) {}

//-----
Option::~Option() {}

//-----
const std::string& Option::GetText() const
{
    return mText;
}

//-----
void Option::SetText(const std::string& text)
{
    mText = text;
}

//-----
const Node* const Option::GetNode() const
{
    return mNode;
}

//-----
void Option::SetNode(Node* node)
{
    mNode = node;
}

//-----
int Option::GetQuanolaCost() const
{
    return mCost;
}

//-----
void Option::SetQuanolaCost(int cost)
{
    mCost = cost;
}
