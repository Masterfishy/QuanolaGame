#include "Option.hpp"

//-----
Option::Option()
    : mCost(0), mText(""), mDefaultNodeIds(), mRandomNodeIds(),
      mConditionalNodeIds()
{
}

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
int Option::GetNode() const
{
    // TODO handle results
    // 1. Check conditional nodes
    // 2. Draw from random weighted bag

    if (!mDefaultNodeIds.empty())
    {
        return mDefaultNodeIds.front();
    }

    if (!mRandomNodeIds.empty())
    {
        return mRandomNodeIds.front();
    }

    if (!mConditionalNodeIds.empty())
    {
        return mConditionalNodeIds.front();
    }

    return -1;
}

//-----
void Option::AddDefaultNode(int nodeId)
{
    mDefaultNodeIds.push_back(nodeId);
}

//-----
void Option::AddRandomNode(int nodeId)
{
    mRandomNodeIds.push_back(nodeId);
}

//-----
void Option::AddConditionalNode(int nodeId)
{
    mConditionalNodeIds.push_back(nodeId);
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
