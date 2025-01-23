# Convert markdown to mermaid diagram

import re
import sys
import json

def parse_markdown(markdown: str) -> list:
    nodes = []

    sections = re.split(r"(?=^## .*$)", markdown.strip(), flags=re.MULTILINE)

    node_id_counter = 0

    for section in sections:

        node = {}

        header_split = re.split(r"^## ([^{]+?)(?: \{.*\}|\n)$", section.strip(), flags=re.MULTILINE)
        if len(header_split) != 3:
            continue

        # Grab the header
        header = header_split[1]

        content = header_split[2]

        # print(f"{i} {header}")

        content_split = re.split(r"### Cards", content.strip(), flags=re.MULTILINE)
        if len(content_split) != 2:
            print(f"Dropped: {header}, no cards found")
            continue

        # Grab the header text
        header_text = content_split[0]

        cards = content_split[1]

        # print(header_text)
        
        cards_split = re.split(r"(?=^#### )", cards.strip(), flags=re.MULTILINE)
        if len(cards_split) <= 1:
            print(f"Dropped: {header}, no options found")
            continue

        options = []

        for card in cards_split:
            card_split = re.split(r"^#### (.*)", card.strip())
            if len(card_split) < 2:
                continue

            # Grab the card title
            card_title = card_split[1]

            # Grab the card text
            card_text = card_split[2]
            # print(f"{card_title} {card_text}")

            default_results = []
            random_results = []
            conditional_results = []

            result_split = re.split(r"- Event - (\w+) ", card_text.strip(), flags=re.MULTILINE)
            if len(result_split) < 2:
                print(f"Dropped option: {card_title}, no results")
                continue
            
            shared_text = result_split[0]
            result_type = result_split[1]
            print(f"Result: {result_type} > {result_split[2]}")
            if result_type == "Random":
                pass

            if result_type == "Default":
                pass

            if result_type == "Conditional":
                pass

            option = {}
            option["title"] = card_title
            option["text"] = card_text

            options.append(option)
            # print("^^^^^^^")

        node["id"] = node_id_counter
        node["title"] = header
        node["text"] = header_text
        node["options"] = options

        node_id_counter += 1

        nodes.append(node)

    return nodes


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

    # with open(outputFileName, "w") as file:
    #     json.dump(parsed_nodes, file, indent=2)
