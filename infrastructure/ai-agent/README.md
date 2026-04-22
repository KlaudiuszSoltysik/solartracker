# Infrastructure AI Agent

## Main.py

This script is responsible for orchestrating the development process of an AI agent using a specific model and environment setup.

### Dependencies

- `logging`: For logging purposes.
- `os`: For file operations.
- `subprocess`: For subprocess calls.
- `pathlib`: For path manipulation.
- `dotenv`: For loading environment variables from `.env` files.
- `requests`: For making HTTP requests to the Ollama server.

### Environment Variables

- `OLLAMA_URL`: The URL of the Ollama server.
- `MODEL`: The model name used for inference.
- `ROOT_DIR`: The root directory containing all necessary files and directories.
- `IGNORE_EXTENSIONS`: A list of file extensions that should not be ignored during processing.
- `IGNORE_FILES`: A list of files to ignore.

### File Operations

1. **get_valid_files**: Retrieves a list of valid files in the specified scope path.
2. **has_changes**: Checks if there are any changes in the current directory tree.
3. **read_file_content**: Reads the content of a file and returns it as a string.
4. **call_ollama**: Calls Ollama to generate code based on the prompt provided.

### Main Function

- **get_valid_files**: Retrieves valid files from the specified scope path.
- **has_changes**: Checks if there are any changes in the current directory tree.
- **read_file_content**: Reads the content of a file and returns it as a string.
- **call_ollama**: Calls Ollama to generate code based on the prompt provided.

### Main Function

1. **Start Work**: Initializes the logger, loads environment variables, and calls `get_valid_files` to get valid files in the root directory.
2. **Generate Root README**: Reads the content of a file named "README.md" from the root directory and generates a short, professional README.md based on it.
3. **Generate Module Readme**: Calls Ollama to generate code for a specific module within the specified scope path.

### Example Usage

1. Ensure you have the necessary environment variables set up:
   ```sh
   export OLLAMA_URL=http://localhost:11434
   export MODEL=qwen2.5:0.5b
   export ROOT_DIR="../.."
   ```

2. Run the script:

```sh
python infrastructure/ai_agent/main.py
```

This will generate a `README.md` file in the current directory based on the provided model and scope, ensuring that only valid files are processed.

### Notes

- The script assumes you have already set up Ollama to run locally.
- You can modify the `ROOT_DIR` variable to point to your project's root directory if needed.
- The script uses a simple setup for demonstration purposes. In production, consider using more robust error handling and logging mechanisms.