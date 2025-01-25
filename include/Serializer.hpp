#pragma once

#include <map>
#include <memory>
#include <string>

// Forward declarations
class Node;
namespace Json
{
class Value;
}
// end forward declarations

class Serializer
{
  public:
    typedef std::map<int, std::unique_ptr<Node>> NodeCollection;

    /**
     * Create a list of nodes from a given file.
     *
     * @param fileName  The name of the serialized node data.
     * @param nodes     The collection of nodes to fill with the serialized
     *                  data.
     * @return true     If the load is successful.
     * @return false    If the load fails.
     */
    static bool LoadNodesFromFile(const std::string& fileName,
                                  NodeCollection& nodes);

    /**
     * Write the given nodes to a file.
     *
     * @param nodes     The nodes to serialize.
     * @param fileName  The name of the file to write the node data to.
     * @return true     If the node data is successfully serialized.
     * @return false    If the data could not be written.
     */
    static bool WiteNodesToFile(const NodeCollection& nodes,
                                const std::string& fileName);

  private:
    /**
     * Deserialize nodes from the given json data, filling the given collection.
     *
     * @param jsonData  The json node data.
     * @param nodes     The node collection to fill.
     * @return true     If successful.
     * @return false    otherwise.
     */
    static bool DeserializeFromJson(const Json::Value& jsonData,
                                    NodeCollection& nodes);

    /**
     * Serialize nodes to json, filling the given root.
     *
     * @param nodes     The nodes to serialize.
     * @param jsonData  The json data to fill.
     * @return true     If successful.
     * @return false    otherwise.
     */
    static bool SerializeToJson(const NodeCollection& nodes,
                                Json::Value& jsonData);
};
