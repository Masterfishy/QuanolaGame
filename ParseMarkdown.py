# Convert markdown to mermaid diagram

import re
import sys
import json

def parse_markdown(markdown: str) -> list:
    nodes = []

    node_id_lookup_table = {}    # title -> id
    node_lookup_table = {}       # id -> node

    sections = re.split(r"^## ([^{]+?)(?: \{.*\}|\n)$", markdown.strip(), flags=re.MULTILINE)
    if len(sections) < 3:
        return
    
    for i, title in enumerate(sections[1::2]):
        node = {}
        node["id"] = i
        node["title"] = title.lower()

        node_id_lookup_table[node["title"]] = node["id"]
        node_lookup_table[node["id"]] = node

    print(node_id_lookup_table)

    for i, section in enumerate(sections[2::2]):

        content_split = re.split(r"### Cards", section.strip(), flags=re.MULTILINE)
        if len(content_split) < 1:
            print(f"Dropped {node_lookup_table.get(i).get('title')}")
            continue

        # print(content_split)

        node = node_lookup_table.get(i)
        if node is None:
            print(f"Dropping content {i}, no node")
            continue

        # Grab the node text
        node["text"] = content_split[0]

        if len(content_split) < 2:
            continue

        options = []

        # print(content_split[1])

        cards_split = re.split(r"(?=^#### .*)", content_split[1].strip(), flags=re.MULTILINE)
        for card in cards_split[1::]:
            print(card)

            card_title = re.search(r"^#### (.*)", card.strip())
            if card_title is None:
                continue

            print(card_title)
            print(card_title.groups()[0])

            default_results = [result.replace("-"," ") for result in re.findall(r"- Event - Default .*\(#(.+[^)])\)", card.strip(), flags=re.MULTILINE)]
            random_results = [result.replace("-"," ") for result in re.findall(r"- Event - Random .*\(#(.+[^)])\)", card.strip(), flags=re.MULTILINE)]
            conditional_results = [result.replace("-"," ") for result in re.findall(r"- Event - Conditional .*\(#(.+[^)])\)", card.strip(), flags=re.MULTILINE)]

            print(default_results)
            print(random_results)
            print(conditional_results)

            # Make a node for each result

            # result_node["id"] = node_counter ++
            # result_node["title"] = title
            # result_node["text"] = text
            # result_node["next"] = node_id_lookup_table.get(title)

            # Add the results to the option

            option = {}
            option["title"] = card_title.groups()[0]
            option["default_results"] = [node_id_lookup_table.get(title) for title in default_results]
            option["random_results"] = [node_id_lookup_table.get(title) for title in random_results]
            option["conditional_results"] = [node_id_lookup_table.get(title) for title in conditional_results]

            print(option)

            options.append(option)

            print("-" * 20)

        node["options"] = options

        print("=" * 20)

    return list(node_lookup_table.values())

if __name__ == "__main__":

    if len(sys.argv) < 3:
        print("Invalid usage! Usage: ParseMarkdown.py <markdown-file> <output-file>")
        sys.exit(1)

    markdownFileName = sys.argv[1]
    outputFileName = sys.argv[2]

    markdown = ""
    
    with open(markdownFileName, "r") as file:
        markdown = file.read()

    parsed_nodes = parse_markdown(markdown)

    with open(outputFileName, "w") as file:
        json.dump(parsed_nodes, file, indent=2)
