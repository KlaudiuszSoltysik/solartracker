import os
import subprocess
from pathlib import Path

import requests

OLLAMA_URL = "http://localhost:11434/api/generate"
MODEL = "llama3.2"
IGNORE_EXTENSIONS = {'.png', '.jpg', '.jpeg', '.lock', '.pyc', '.exe', '.toml', '.json', '.txt'}
IGNORE_FILES = {'Dockerfile', '.gitignore', 'secret.yml', 'install.yaml', 'ghcr-secret.yml', 'TODO.md'}


def get_valid_files(scope_path="../.."):
    cmd = ['git', 'ls-files', '--cached', '--others', '--exclude-standard', scope_path]
    result = subprocess.run(cmd, capture_output=True, text=True)
    files = result.stdout.strip().split('\n')
    return [f for f in files if f and Path(f).suffix not in IGNORE_EXTENSIONS and Path(f).name not in IGNORE_FILES]


def get_git_diff(scope_path):
    result = subprocess.run(['git', 'diff', '--cached', scope_path], capture_output=True, text=True)
    if not result.stdout.strip():
        result = subprocess.run(['git', 'diff', 'HEAD', scope_path], capture_output=True, text=True)
    return result.stdout.strip()


def read_file_content(file_path):
    try:
        with open(file_path, 'r', encoding='utf-8') as f:
            return f.read(2000)
    except Exception:
        return ""


def call_ollama(prompt):
    print("Thinking...", end="", flush=True)
    try:
        response = requests.post(OLLAMA_URL, json={
            "model": MODEL,
            "prompt": prompt,
            "stream": False,
            "options": {
                "temperature": 0.1
            }
        })
        print("Done!")
        return response.json().get('response', '')
    except requests.exceptions.ConnectionError:
        print("Ollama server is not running.")
        return ""


def generate_initial_readme(scope_path, files):
    print(f"Writing README for: {scope_path}\nFiles: {files}")

    code_context = ""
    for file_path in files:
        content = read_file_content(file_path)
        if content:
            code_context += f"\n--- File: {file_path} ---\n{content}\n"

    prompt = f"""
    You are an expert DevOps and Software Engineer.
    Write a comprehensive, professional README.md in English for a specific module of a project.
    
    Directory: {scope_path}
    
    Here is the content of the files in this directory:
    {code_context}
    
    Write ONLY the raw Markdown content. Include Description and Architecture, skip Setup. Do not write any introductory text, pleasantries, or explanations. Just the final Markdown.
    """
    return call_ollama(prompt)


def update_existing_readme(scope_path, existing_content, diff):
    print(f"Rewriting README for: {scope_path}")

    prompt = f"""
    You are an expert DevOps and Software Engineer. 
    Below is the current content of the README.md file in the '{scope_path}' directory, followed by a git diff showing recent code changes.
    
    Current README:
    ---
    {existing_content}
    ---
    
    Git Diff:
    ---
    {diff}
    ---
    
    Rewrite the entire README file to seamlessly incorporate these new changes. 
    Maintain the existing structure, tone, and formatting, but update the technical details, architecture, or usage instructions as necessary based on the diff.
    
    Write ONLY the raw Markdown content. Include Description and Architecture, skip Setup. Do not write any introductory text, pleasantries, or explanations. Just the final Markdown.
    """
    return call_ollama(prompt)


def process_repo():
    print("Starting work!")

    all_files = get_valid_files()
    readme_files = [f for f in all_files if Path(f).name == 'README.md']

    for readme_str in readme_files:
        readme_path = Path(readme_str)
        scope_path = readme_path.parent
        print(f"Found scope {scope_path}.")

        is_empty = os.path.getsize(readme_path) == 0 or not readme_path.read_text(encoding='utf-8').strip()

        if is_empty:
            files_in_scope = get_valid_files(str(scope_path))
            files_in_scope = [f for f in files_in_scope if Path(f).name != 'README.md']

            if not files_in_scope:
                print(f"Skipping directory {scope_path}.")
                continue

            new_content = generate_initial_readme(str(scope_path), files_in_scope)
            if new_content:
                with open(readme_path, 'w', encoding='utf-8') as f:
                    f.write(new_content)
                subprocess.run(['git', 'add', str(readme_path)])

        else:
            diff = get_git_diff(str(scope_path))
            if not diff:
                print(f"Skipping directory {scope_path}.")
                continue

            existing_content = readme_path.read_text(encoding='utf-8')
            update_content = update_existing_readme(str(scope_path), existing_content, diff)

            if update_content:
                with open(readme_path, 'w', encoding='utf-8') as f:
                    f.write(update_content)
                subprocess.run(['git', 'add', str(readme_path)])


if __name__ == "__main__":
    process_repo()
    print("Work is done!")
