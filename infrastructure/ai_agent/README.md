# README Writer

This script provides a simple way to generate a `README.md` file based on the files in a given directory tree. The script uses Ollama (a popular open-source code generation tool) to analyze the structure of the project and extract relevant information.

## Usage

1. **Prepare the Directory Tree:**
   - Ensure that all necessary files are present in the specified `ROOT_DIR`.
   - Create a `README.md` file with the desired content.

2. **Run the Script:**
   - Save the script to a file, e.g., `readme_writer.py`.
   - Execute the script using Python:
     ```sh
     python readme_writer.py
     ```

3. **Generate README Files:**
   - The script will generate two types of `README.md` files:
     - A single `README.md` file containing only the raw Markdown content.
     - Multiple `README.md` files, each representing a specific module in the project.

## Example Usage

- If you have a directory tree like this:

  ```
  /project
    ├── README.md
    └── module1
      ├── README.md
      └── module2
        ├── README.md
        └── module3
          ├── README.md
          └── ...
  ```

- The script will generate two `README.md` files:
  - A single file named `module1/README.md`.
  - Multiple files, each representing a specific module in the project.

## Requirements

- Python 3.x
- Ollama (a popular open-source code generation tool)

## Installation

You can install the script using pip:

```sh
pip install --user readme_writer
```

## How It Works

1. **Reading Files:**
   - The script reads files in the specified directory tree and extracts relevant information.
   - It uses `requests` to post data to Ollama, which generates a Markdown file based on the provided prompt.

2. **Generating README Files:**
   - Based on the extracted information from Ollama, the script generates two types of `README.md` files:
     - A single `README.md` file containing only the raw Markdown content.
     - Multiple `README.md` files, each representing a specific module in the project.

## Customization

- You can customize the script by modifying the `OLLAMA_URL`, `MODEL`, and other parameters to fit your specific needs.
- The script also supports reading from local files if needed.

## Limitations

- This script assumes that the Ollama server is running locally. If you need to use a different server, you may need to modify the script accordingly.
- The script does not handle cases where the project structure changes or new files are added after the initial analysis.

Feel free to ask if you have any questions or need further assistance!