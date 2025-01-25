#pragma once

#include <string>
#include <vector>

// Forward declarations

class Option;

// end

/**
 * A dialog moment with text, a next node, and possibly options to select from.
 */
class Node
{
  public:
    /**
     * Create a new node.
     */
    Node();

    /**
     * Destructor.
     */
    ~Node();

    /**
     * Get the Nodes text.
     * @return The text as a string.
     */
    const std::string& GetText() const;

    /**
     * Set the text of the Node.
     *
     * @param text The new text of the node.
     */
    void SetText(const std::string& text);

    /**
     * Get the \c Node s \c Option s.
     * @return A list of Options.
     */
    const std::vector<Option>& GetOptions() const;

    /**
     * Add an option to the Node.
     *
     * @param option The option to add.
     */
    void AddOption(Option& option);

    /**
     * Get the Node that follows this Node.
     * @return The next node.
     */
    int GetNextNodeId() const;

    /**
     * Set the Next Node object
     *
     * @param nextNode The next node
     */
    void SetNextNode(int nextNodeId);

  private:
    /**
     * The text of this Node.
     */
    std::string mText;

    /**
     * The Options of this Node.
     */
    std::vector<Option> mOptions;

    /**
     * The Node that follows this Node.
     */
    int mNextNodeId;
};
