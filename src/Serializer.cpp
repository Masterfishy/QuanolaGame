#include "Serializer.hpp"
#include "Node.hpp"
#include "Option.hpp"

#include <fstream>
#include <iostream>
#include <json/json.h>

//-----
bool Serializer::LoadNodesFromFile(const std::string& fileName,
                                   NodeCollection& nodes)
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
    return DeserializeFromJson(root, nodes);
}

//-----
bool Serializer::WiteNodesToFile(const NodeCollection& nodes,
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
                                     NodeCollection& nodes)
{
    for (const auto& jsonNode : jsonData)
    {
        // std::cout << "===NODE===" << std::endl;
        // std::cout << jsonNode << std::endl << std::endl;

        // Deserialize the node id
        const Json::Value& jsonId = jsonNode["id"];
        if (jsonId == Json::Value::null)
        {
            continue;
        }

        // Deserialize the node title
        const Json::Value& jsonTitle = jsonNode["title"];
        if (jsonTitle == Json::Value::null)
        {
            continue;
        }

        // Deserialize the node text
        const Json::Value& jsonText = jsonNode["text"];
        if (jsonText == Json::Value::null)
        {
            continue;
        }

        // Create a node from the deserialized data
        std::unique_ptr<Node> node = std::make_unique<Node>();
        node->SetText(jsonText.asString());

        // Deserialize the node options
        const Json::Value& jsonOptions = jsonNode["options"];
        for (const auto& jsonOption : jsonOptions)
        {
            // Deserialize the option text
            const Json::Value& jsonOptionTitle = jsonOption["title"];
            if (jsonOptionTitle == Json::Value::null)
            {
                continue;
            }

            Option option;
            option.SetText(jsonOptionTitle.asString());

            // Deserialize the default results
            const Json::Value& jsonDefaultResults =
                jsonOption["default_results"];
            for (const auto& jsonDefaultResult : jsonDefaultResults)
            {
                const Json::Value& jsonResultId = jsonDefaultResult["id"];
                if (jsonResultId == Json::Value::null)
                {
                    continue;
                }

                const Json::Value& jsonResultText = jsonDefaultResult["text"];
                if (jsonResultText == Json::Value::null)
                {
                    continue;
                }

                const Json::Value& jsonNextId = jsonDefaultResult["next"];
                if (jsonNextId == Json::Value::null)
                {
                    continue;
                }

                // Create the result node
                std::unique_ptr<Node> resultNode = std::make_unique<Node>();
                resultNode->SetText(jsonResultText.asString());
                resultNode->SetNextNode(jsonNextId.asInt());

                // Add the result node's id to the option
                option.AddDefaultNode(jsonResultId.asInt());

                // Add the result node to the node collection
                nodes.emplace(jsonResultId.asInt(), std::move(resultNode));
            }

            // Deserialize the random results
            const Json::Value& jsonRandomResults = jsonOption["random_results"];
            for (const auto& jsonRandomResult : jsonRandomResults)
            {
                const Json::Value& jsonResultId = jsonRandomResult["id"];
                if (jsonResultId == Json::Value::null)
                {
                    continue;
                }

                const Json::Value& jsonResultText = jsonRandomResult["text"];
                if (jsonResultText == Json::Value::null)
                {
                    continue;
                }

                const Json::Value& jsonNextId = jsonRandomResult["next"];
                if (jsonNextId == Json::Value::null)
                {
                    continue;
                }

                // Create the result node
                std::unique_ptr<Node> resultNode = std::make_unique<Node>();
                resultNode->SetText(jsonResultText.asString());
                resultNode->SetNextNode(jsonNextId.asInt());

                // Add the result node's id to the option
                option.AddRandomNode(jsonResultId.asInt());

                // Add the result node to the node collection
                nodes.emplace(jsonResultId.asInt(), std::move(resultNode));
            }

            // Deserialize the conditional results
            const Json::Value& jsonConditionalResults =
                jsonOption["conditional_results"];
            for (const auto& jsonConditionalResult : jsonConditionalResults)
            {
                const Json::Value& jsonResultId = jsonConditionalResult["id"];
                if (jsonResultId == Json::Value::null)
                {
                    continue;
                }

                const Json::Value& jsonResultText =
                    jsonConditionalResult["text"];
                if (jsonResultText == Json::Value::null)
                {
                    continue;
                }

                const Json::Value& jsonNextId = jsonConditionalResult["next"];
                if (jsonNextId == Json::Value::null)
                {
                    continue;
                }

                // Create the result node
                std::unique_ptr<Node> resultNode = std::make_unique<Node>();
                resultNode->SetText(jsonResultText.asString());
                resultNode->SetNextNode(jsonNextId.asInt());

                // Add the result node's id to the option
                option.AddConditionalNode(jsonResultId.asInt());

                // Add the result node to the node collection
                nodes.emplace(jsonResultId.asInt(), std::move(resultNode));
            }

            node->AddOption(option);
        }

        // Add the node to the collection
        nodes.emplace(jsonId.asInt(), std::move(node));
    }

    return true;
}

//-----
bool Serializer::SerializeToJson(const NodeCollection& nodes,
                                 Json::Value& jsonData)
{
    // for (const auto& node : nodes)
    // {
    //     // Serialize the node
    //     Json::Value jsonNode;
    //     jsonNode["text"] = node->GetText();
    //     jsonNode["nodeId"] = "";  // TODO how to identify nodes

    //     // Serialize the options
    //     Json::Value optionsArray(Json::arrayValue);
    //     for (const auto& option : node->GetOptions())
    //     {
    //         Json::Value jsonOption;
    //         jsonOption["cost"] = option.GetQuanolaCost();
    //         jsonOption["text"] = option.GetText();
    //         jsonOption["nodeId"] = "";  // TODO how to identify nodes

    //         optionsArray.append(jsonOption);
    //     }

    //     jsonNode["options"] = optionsArray;

    //     // Add the node to the root
    //     jsonData.append(jsonNode);
    // }

    return true;
}
