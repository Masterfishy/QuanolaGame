#pragma once

#include <string>
#include <vector>

// Forward declarations
class Node;
// end

class Option
{
  public:
    /**
     * Create an Option.
     */
    Option();

    /**
     * Destructor.
     */
    ~Option();

    /**
     * Get the text of this Option.
     * @return The text of this Option.
     */
    const std::string& GetText() const;

    /**
     * Set the text of the Option.
     *
     * @param text The new text of the Option.
     */
    void SetText(const std::string& text);

    /**
     * Get the id of the node of this Option.
     * @return The id of the node of this option.
     */
    int GetNode() const;

    /**
     * Add an id for a default node.
     *
     * @param nodeId  The id of the node.
     */
    void AddDefaultNode(int nodeId);

    /**
     * Add an id for a random node.
     *
     * @param nodeId  The id of the node.
     */
    void AddRandomNode(int nodeId);

    /**
     * Add an id for a conditional node.
     *
     * @param nodeId  The id of the node.
     */
    void AddConditionalNode(int nodeId);

    /**
     * Get the cost of this Option.
     * @return The quanola cost of selecting this Option.
     */
    int GetQuanolaCost() const;

    /**
     * Set the Quanola cost
     *
     * @param cost The cost of the option.
     */
    void SetQuanolaCost(int cost);

  private:
    /**
     * The quanola cost of this Option.
     */
    int mCost;

    /**
     * The text of this Option.
     */
    std::string mText;

    /**
     * The collection of ids for the default results
     */
    std::vector<int> mDefaultNodeIds;

    /**
     * The collection of ids for the random results.
     */
    std::vector<int> mRandomNodeIds;

    /**
     * The collection of ids for the conditional results.
     */
    std::vector<int> mConditionalNodeIds;
};
