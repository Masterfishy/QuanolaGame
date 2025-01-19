#pragma once

#include <string>

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
     * Get the Node of this Option.
     * @return The Node of this Option.
     */
    const Node* const GetNode() const;

    /**
     * Set the Node object
     *
     * @param node The node of the Option.
     */
    void SetNode(Node* node);

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
     * The Node this Option leads to.
     */
    Node* mNode;
};
