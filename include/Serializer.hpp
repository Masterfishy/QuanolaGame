#pragma once

#include <string>
#include <vector>

// Forward declarations
class Node;
// end forward declarations

class Serializer
{
  public:
    /**
     * Create a list of nodes from a given file.
     *
     * @param fileName              The name of the serialized node data.
     * @return std::vector<Node*>   A list of the deserialized nodes.
     */
    static std::vector<Node*> loadNodesFromFile(const std::string& fileName);

    /**
     * Write the given nodes to a file.
     *
     * @param nodes     The nodes to serialize.
     * @param fileName  The name of the file to write the node data to.
     * @return true     If the node data is successfully serialized.
     * @return false    If the data could not be written.
     */
    bool writeNodesToFile(const std::vector<Node*> nodes,
                          const std::string& fileName);
};
