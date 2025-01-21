# Convert markdown to mermaid diagram

import re
import sys

def parse_markdown(markdown: str) -> str:
    nodes = {}

    sections = re.split(r"(?=^## .*$)", markdown.strip(), flags=re.MULTILINE)

    for i, section in enumerate(sections):

        node = {}

        header_split = re.split(r"^## ([^{]+?)(?: \{.*\}|\n)$", section.strip(), flags=re.MULTILINE)
        if len(header_split) != 3:
            continue

        # Grab the header
        header = header_split[1]
        node["title"] = header

        content = header_split[2]

        # print(f"{i} {header}")

        content_split = re.split(r"### Cards", content.strip(), flags=re.MULTILINE)
        if len(content_split) != 2:
            continue

        # Grab the header text
        header_text = content_split[0]
        node["text"] = header_text

        cards = content_split[1]

        # print(header_text)
        
        cards_split = re.split(r"(?=^#### )", cards.strip(), flags=re.MULTILINE)
        if len(cards_split) <= 1:
            continue

        node["options"] = []

        for card in cards_split:
            card_split = re.split(r"^#### (.*)", card.strip())
            if len(card_split) < 2:
                continue

            # Grab the card title
            card_title = card_split[1]

            # Grab the card text
            card_text = card_split[2]
            # print(f"{card_title} {card_text}")

            # print("^^^^^^^")

            option = {}
            option["title"] = card_title
            option["text"] = card_text

            node["options"].append(option)

        nodes[i] = node

        print("----------------------------------------")

    print(nodes[1])

if __name__ == "__main__":

    if len(sys.argv) < 1:
        print("Please provide a file.")
        sys.exit(1)

    markdownFileName = sys.argv[1]
    markdown = ""
    
    with open(markdownFileName, "r") as file:
        markdown = file.read()

    parse_markdown(markdown)
