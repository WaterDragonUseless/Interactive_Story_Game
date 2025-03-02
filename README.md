# Choose Your Own Adventure Game

This project is a C++ implementation of a "choose your own adventure" game—a dynamic story engine where your choices dictate the outcome. Originally developed as part of an evaluative assignment, the project guides you through an interactive narrative with multiple paths and endings.

## Features

- **Interactive Storytelling:** Navigate through story pages by making choices that influence the outcome.
- **Multiple Endings:** Reach winning or losing conclusions based on your decisions.
- **Cycle-Free Winning Paths:** An advanced mode computes all cycle-free winning paths through the narrative.
- **Conditional Choices & Variables:** In later stages, the game supports variable assignments and conditional choices, allowing the story to remember events and adjust available options.
- **Robust Error Handling:** Comprehensive validation of story file formatting and page references ensures a smooth gameplay experience.

## Project Structure

- **cyoa-step1:** Reads and sequentially displays all story pages.
- **cyoa-step2:** Offers interactive gameplay, letting users traverse the story via their choices.
- **cyoa-step3:** Analyzes the story graph to print all cycle-free paths leading to a win.
- **cyoa-step4:** Enhances the gameplay with variable tracking and conditional logic.
- **Source Files:** Organized C++ source (`.cpp`) and header (`.h`) files implementing classes for pages, choices, and story management.
- **Makefile:** Easily compile the project using GNU Make.

## Getting Started

### Prerequisites

- A C++ compiler supporting at least C++11.
- GNU Make (or any compatible build system).

### Compilation

Clone the repository and build the executables using the provided Makefile:

```bash
git clone https://github.com/yourusername/your-repo-name.git
cd your-repo-name
make
