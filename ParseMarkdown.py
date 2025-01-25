# Convert markdown to mermaid diagram

import re
import sys
import json

def parse_markdown(markdown: str) -> list:
    nodes = []

    node_id_lookup_table = {}    # title -> id
    node_lookup_table = {}       # id -> node

    node_id_counter = 0

    sections = re.split(r"^## ([^{]+?)(?: \{.*\}|\n)$", markdown.strip(), flags=re.MULTILINE)
    if len(sections) < 3:
        return
    
    for i, title in enumerate(sections[1::2]):
        node = {}
        node["id"] = i
        node["title"] = title.lower()

        node_id_lookup_table[node["title"]] = node["id"]
        node_lookup_table[node["id"]] = node

        node_id_counter += 1

    print(node_id_lookup_table)
    print(node_id_counter)

    for i, section in enumerate(sections[2::2]):

        print(f"Node: {i}")

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

            card_title = re.search(r"(?<=#### )(.*)", card.strip())
            if card_title is None:
                continue

            # print(card_title)
            print(f"Card Title: {card_title.group()}")

            result_shared_text = ""
            result_shared_text_search = re.findall(r"- Shared Text\n((?:  -.*\n)+)", card.strip(), flags=re.MULTILINE)
            if len(result_shared_text_search) > 0:
                result_shared_text = result_shared_text_search[0]
                print(f"Shared Text: {result_shared_text}")

            # DEFAULT RESULTS

            default_results = []
            default_result_text = re.findall(r"- Event - Default [^\n]+\n((?:  -.*\n?)*)", card.strip(), flags=re.MULTILINE)
            default_result_next = re.findall(r"- Event - Default .*\(#(.+[^)])\)", card.strip(), flags=re.MULTILINE)
            # print(f"Default Text: {default_result_text}")
            # print(f"Default Next: {default_result_next}")

            for text, next_node in zip(default_result_text, default_result_next):
            
                print(f"Default Text: {text}")
                print(f"Default Next: {next_node}")

                node_id = node_id_lookup_table.get(next_node.replace("-", " "))

                default_node = {}
                default_node["id"] = node_id_counter
                default_node["text"] = result_shared_text + text
                default_node["next"] = node_id

                node_id_counter += 1

                default_results.append(default_node)

            # RANDOM RESULTS

            random_results = []
            random_result_text = re.findall(r"- Event - Random [^\n]+\n((?:  -.*\n?)*)", card.strip(), flags=re.MULTILINE)
            random_result_next = re.findall(r"- Event - Random .*\(#(.+[^)])\)", card.strip(), flags=re.MULTILINE)
            # print(f"Random Text: {random_result_text}")
            # print(f"Random Next: {random_result_next}")

            for text, next_node in zip(random_result_text, random_result_next):

                print(f"Random Text: {text}")
                print(f"Random Next: {next_node}")

                node_id = node_id_lookup_table.get(next_node.replace("-", " "))

                random_node = {}
                random_node["id"] = node_id_counter
                random_node["text"] = result_shared_text + text
                random_node["next"] = node_id

                node_id_counter += 1

                random_results.append(random_node)

            # CONDITIONAL RESULTS

            # Add the results to the option

            option = {}
            option["title"] = card_title.group()
            option["default_results"] = default_results
            option["random_results"] = random_results
            # option["conditional_results"] = [node_id_lookup_table.get(title) for title in conditional_results]

            # print(option)

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
