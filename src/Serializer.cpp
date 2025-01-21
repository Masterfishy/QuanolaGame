#include "Serializer.hpp"
#include "Node.hpp"
#include "Option.hpp"

#include <fstream>
#include <json/json.h>

//-----
bool Serializer::LoadNodesFromFile(const std::string& fileName,
                                   std::vector<Node*>& nodes)
{
    std::ifstream file(fileName);
    if (!file.is_open())
    {
        return false;
    }

    Json::Value root;
    Json::CharReaderBuilder reader;
    std::string errors;

    if (!Json::parseFromStream(reader, file, &root, &errors))
    {
        return false;
    }

    // Deserialize the root

    return true;
}

//-----
bool Serializer::WiteNodesToFile(const std::vector<Node*>& nodes,
                                 const std::string& fileName)
{
    std::ofstream file(fileName);
    if (!file.is_open())
    {
        return false;
    }

    Json::Value root;
    Json::StreamWriterBuilder writer;

    // Fill root with serialized nodes
    if (!SerializeToJson(nodes, root))
    {
        return false;
    }

    std::string nodesJson = Json::writeString(writer, root);
    file << nodesJson;

    return true;
}

//-----
bool Serializer::DeserializeFromJson(const Json::Value& jsonData,
                                     std::vector<Node*>& nodes)
{
}

//-----
bool Serializer::SerializeToJson(const std::vector<Node*>& nodes,
                                 Json::Value& jsonData)
{
    for (const auto& node : nodes)
    {
        // Serialize the node
        Json::Value jsonNode;
        jsonNode["text"] = node->GetText();
        jsonNode["nodeId"] = "";  // TODO how to identify nodes

        // Serialize the options
        Json::Value optionsArray(Json::arrayValue);
        for (const auto& option : node->GetOptions())
        {
            Json::Value jsonOption;
            jsonOption["cost"] = option.GetQuanolaCost();
            jsonOption["text"] = option.GetText();
            jsonOption["nodeId"] = "";  // TODO how to identify nodes

            optionsArray.append(jsonOption);
        }

        jsonNode["options"] = optionsArray;

        // Add the node to the root
        jsonData.append(jsonNode);
    }

    return true;
}
