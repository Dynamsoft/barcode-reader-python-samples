# DBR Python Sample Creator - AI Coding Skill

An AI coding skill that helps developers quickly build working Python applications with the [Dynamsoft Barcode Reader](https://www.dynamsoft.com/barcode-reader/overview/) SDK. Feed this skill to your AI agent (GitHub Copilot, Claude, Cursor, Windsurf, etc.) and describe what you need - the agent will generate correct, production-ready code.

## Who Is This For?

Developers evaluating or integrating the `dynamsoft_barcode_reader_bundle` Python SDK who want to **accelerate POC development** using AI coding assistants. Instead of reading through documentation and samples manually, let your AI agent do the heavy lifting with full SDK knowledge built in.

## Quick Setup

**Recommended:** Use the [`skills` CLI](https://github.com/vercel-labs/skills) to install to all your AI agents at once.

If you have already cloned this repository, run from the repo root:

```bash
npx skills add .
```

Or install directly from GitHub without cloning:

```bash
npx skills add Dynamsoft/barcode-reader-python-samples
```

You can also target a specific agent:

```bash
npx skills add . -a claude-code
npx skills add . -a cursor -a windsurf
```

Or copy the `skills/dbr-python-sample-creator/` folder into your project and configure your agent manually:

| AI Agent | Manual Setup |
|----------|-------|
| **GitHub Copilot** | Just open the workspace - auto-discovered |
| **Claude Code** | Reference `SKILL.md` in your `CLAUDE.md` |
| **Cursor** | Add a rule in `.cursor/rules/dbr.mdc` pointing to `SKILL.md` |
| **Windsurf** | Reference in `.windsurfrules` |
| **Others (40+ agents)** | Use `npx skills add` or point the agent to `SKILL.md` as context |

### Manual Setup Details

<details>
<summary><b>GitHub Copilot</b> - auto-discovered, no configuration needed</summary>

1. Clone the repository (or copy the `skills/dbr-python-sample-creator/` folder into your project).
2. Open the workspace in VS Code with GitHub Copilot enabled.
3. In Copilot Chat (Agent mode), describe the barcode sample you need.

</details>

<details>
<summary><b>Claude Code</b> - add a reference in CLAUDE.md</summary>

1. Copy the `skills/dbr-python-sample-creator/` folder into your project root.
2. Add the following to your project's `CLAUDE.md` (create one if it doesn't exist):

   ```markdown
   ## Coding Skills
   
   When writing Python code that uses the Dynamsoft Barcode Reader SDK, 
   read and follow the skill defined in `skills/dbr-python-sample-creator/SKILL.md` 
   and its `references/` directory.
   ```

</details>

<details>
<summary><b>Cursor</b> - add a project rule</summary>

1. Copy the `skills/dbr-python-sample-creator/` folder into your project.
2. Create or edit `.cursor/rules/dbr.mdc` in your project root:

   ```markdown
   ---
   description: Use when writing Python code with Dynamsoft Barcode Reader SDK
   globs: **/*.py
   ---
   
   When generating code that uses dynamsoft_barcode_reader_bundle, 
   follow the skill definition in `skills/dbr-python-sample-creator/SKILL.md`.
   Read the relevant reference files from `skills/dbr-python-sample-creator/references/` 
   for API details.
   ```

</details>

<details>
<summary><b>Windsurf</b> - add a project rule</summary>

1. Copy the `skills/dbr-python-sample-creator/` folder into your project.
2. Create or edit `.windsurfrules` in your project root:

   ```
   When writing Python code that uses dynamsoft_barcode_reader_bundle or 
   Dynamsoft Barcode Reader SDK, follow the skill defined in 
   skills/dbr-python-sample-creator/SKILL.md and read API references from 
   skills/dbr-python-sample-creator/references/ as needed.
   ```

</details>

<details>
<summary><b>Other AI Agents</b> - generic setup</summary>

1. Copy the `skills/dbr-python-sample-creator/` folder into your project.
2. Point the agent to `skills/dbr-python-sample-creator/SKILL.md` as a reference document.
3. The `SKILL.md` file tells the agent which additional reference files to read based on the task.

</details>

## What's Inside

```
dbr-python-sample-creator/
+-- SKILL.md                  # Entry point - SDK architecture, coding guide, conventions
+-- README.md                 # This file
+-- references/
|   +-- api-core.md           # Core types, enums, geometry, error codes
|   +-- api-cvr.md            # CaptureVisionRouter API
|   +-- api-dbr.md            # Barcode reading API, formats, result items
|   +-- api-license.md        # License initialization API
|   +-- api-utility.md        # DirectoryFetcher, ImageIO, ImageDrawer, filters
|   +-- sample-patterns.md    # Complete working code for every sample pattern
+-- evals/
    +-- evals.json            # Test prompts & expectations for validation
```

The AI agent reads `SKILL.md` first, which tells it which reference files to load based on your specific task. You do not need to understand these files yourself - they are written for the AI.

## Example Prompts

Once the skill is set up, try prompts like:

| Prompt | What the AI Generates |
|--------|----------------------|
| *"Read barcodes from a single image"* | Script using `capture_multi_pages()` with full error handling |
| *"Scan barcodes from a webcam with dedup"* | OpenCV + `ImageSourceAdapter` + `MultiFrameResultCrossFilter` |
| *"Batch decode all images in a folder"* | `DirectoryFetcher` + `CapturedResultReceiver` async pattern |
| *"Flask API that accepts image uploads and returns barcode JSON"* | Server-side sample with proper request handling |
| *"Read only QR codes from a specific region of a PDF"* | Custom settings with format filter + ROI configuration |

## Validating the Setup

Test with this prompt:

> *"Write a Python script that reads barcodes from a single image file and prints the format and text."*

The AI should produce code that:
- Imports from `dynamsoft_barcode_reader_bundle`
- Initializes the license with `LicenseManager.init_license()`
- Creates a `CaptureVisionRouter` instance
- Processes the image and extracts results correctly

More test prompts are available in [`evals/evals.json`](evals/evals.json).
