import logging
import os
import subprocess
from pathlib import Path
from dotenv import load_dotenv

import requests

load_dotenv()

OLLAMA_URL = os.environ.get("OLLAMA_URL", "http://localhost:11434")
GENERATE_URL = f"{OLLAMA_URL.rstrip('/')}/api/generate"
MODEL = os.environ.get("MODEL", "qwen2.5:0.5b")
ROOT_DIR = os.environ.get("ROOT_DIR", "../..")

ignore_ext_str = os.environ.get("IGNORE_EXTENSIONS", ".png,.jpg,.jpeg,.lock,.pyc,.exe,.toml,.json,.txt")
IGNORE_EXTENSIONS = set(ext.strip() for ext in ignore_ext_str.split(","))

ignore_files_str = os.environ.get("IGNORE_FILES", "Dockerfile,.gitignore,secret.yml,install.yaml,ghcr-secret.yml,TODO.md")
IGNORE_FILES = set(file.strip() for file in ignore_files_str.split(","))

logging.basicConfig(
    level=logging.INFO,
    format="%(asctime)s [%(levelname)s] %(message)s",
    datefmt="%Y-%m-%d %H:%M:%S"
)

logger = logging.getLogger("readme-writer")


def get_valid_files(scope_path):
    cmd = ["git", "ls-files", "--cached", "--others", "--exclude-standard", scope_path]
    result = subprocess.run(cmd, capture_output=True, text=True)
    files = result.stdout.strip().split("\n")
    return [f for f in files if f and Path(f).suffix not in IGNORE_EXTENSIONS and Path(f).name not in IGNORE_FILES]


def has_changes(scope_path):
    diff = subprocess.run(["git", "diff", "HEAD", scope_path], capture_output=True, text=True).stdout.strip()
    untracked = subprocess.run(["git", "ls-files", "--others", "--exclude-standard", scope_path], capture_output=True,
                               text=True).stdout.strip()
    return bool(diff or untracked)


def read_file_content(file_path):
    try:
        with open(file_path, "r", encoding="utf-8") as f:
            return f.read()
    except Exception:
        return ""


def call_ollama(prompt):
    logger.info("Thinking...")
    try:
        response = requests.post(GENERATE_URL, json={
            "model": MODEL,
            "prompt": prompt,
            "stream": False,
            "options": {
                "temperature": 0.0,
                "num_ctx": 2048
            }
        })
        logger.info("Done!")
        return response.json().get("response", "")
    except requests.exceptions.ConnectionError:
        logger.error("Ollama server is not running.")
        return ""


def clean_markdown(text):
    text = text.strip()
    if text.startswith("```markdown"):
        text = text[11:]
    elif text.startswith("```"):
        text = text[3:]
    if text.endswith("```"):
        text = text[:-3]
    return text.strip()


def generate_root_readme(scope_path):
    logger.info("Generating ROOT README (using eza tree)")
    tree_output = subprocess.run(["eza", "--tree", "--git-ignore", scope_path], capture_output=True,
                                 text=True).stdout.strip()

    prompt = f"""
    You are an expert Software Architect. 
    Analyze the following directory tree of a project.
    
    Directory Tree:
    {tree_output}
    
    Write a short, professional README.md explaining the high-level architecture of this project based ONLY on the folder names. 
    Write ONLY the raw Markdown content. Do not write any introductory text, pleasantries, or explanations. Do not include code snippets in final README.md.
    """
    return call_ollama(prompt)


def generate_module_readme(scope_path, files):
    logger.info(f"Generating MODULE README (reading {len(files)} files)")
    code_context = ""
    for file_path in files:
        content = read_file_content(file_path)
        if content:
            code_context += f"\n--- File: {file_path} ---\n{content}\n"

    prompt = f"""
    You are an expert Software Engineer.
    Write a short README.md for this specific module.
    
    Files content:
    {code_context}
    
    Focus on technical architecture and purpose of this module, don't include setup paragraph. It's for internal developers.
    Write ONLY the raw Markdown content. Do not write any introductory text, pleasantries, or explanations. Do not include code snippets in final README.md.
    """
    return call_ollama(prompt)


def main():
    logger.info("Starting work!")

    all_files = get_valid_files(ROOT_DIR)
    readme_files = [f for f in all_files if Path(f).name == "README.md"]

    for readme_str in readme_files:
        readme_path = Path(readme_str)
        scope_path = readme_path.parent

        logger.info(f"Evaluating scope: {scope_path}")

        is_empty = os.path.getsize(readme_path) == 0 or not readme_path.read_text(encoding="utf-8").strip()
        needs_update = is_empty or has_changes(str(scope_path))

        if not needs_update:
            logger.info("No changes in context and file is not empty. Skipping.")
            continue

        if str(scope_path) == ROOT_DIR:
            new_content = generate_root_readme(str(scope_path))
        else:
            files_in_scope = get_valid_files(str(scope_path))
            files_in_scope = [f for f in files_in_scope if Path(f).name != "README.md"]

            if not files_in_scope:
                logger.info("No valid source files found. Skipping.")
                continue

            new_content = generate_module_readme(str(scope_path), files_in_scope)

        if new_content:
            cleaned_content = clean_markdown(new_content)
            with open(readme_path, "w", encoding="utf-8") as f:
                f.write(cleaned_content)
            logger.info("Saved!")

    logger.info("Work is done!")


if __name__ == "__main__":
    main()
