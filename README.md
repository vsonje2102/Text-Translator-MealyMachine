# English-Hindi / Hindi-English Translator v2.2.2

## Overview
The Translator v2.2.2 is a state-machine-based text translation system designed to translate text between English and Hindi (and vice versa). It uses a finite state machine to process input files character by character and generates the corresponding translated output. The project supports real-time monitoring of directories for file changes and automatically processes modified files.

## Features
- **Bidirectional Translation**: Supports translation from English to Hindi and Hindi to English.
- **State Machine Implementation**: Uses a finite state machine for efficient character-by-character translation.
- **Real-Time Monitoring**: Monitors specified directories for file modifications and processes them automatically.
- **Unicode Support**: Handles Unicode characters for accurate translation.
- **Configurable Transitions**: Transition rules are defined in CSV files for easy customization.

## Project Structure
- **Source Code**
  - `main.c`: Entry point for the program. Initializes the state machine, monitors directories, and handles file events.
  - `notify_main.c`: Alternate main file for directory monitoring and file processing.
  - `state_machine.c/h`: Implements the state machine logic, including state initialization, expansion, and sorting.
  - `transition.c/h`: Manages state transitions and their associated input/output mappings.
  - `process_file.c/h`: Parses CSV files to populate the state machine with transitions.
  - `process_input.c/h`: Processes input files and generates translated output using the state machine.

- **Configuration Files**
  - `english_hindi.csv`: Defines state transitions for English-to-Hindi and Hindi-to-English translations.
  - `hindi_english.csv`: Similar to `english_hindi.csv`, but with a different set of transitions.
  - `map_old.txt`: Contains mappings for vowels, consonants, and special characters.

- **Input/Output Files**
  - `input_files/`: Directory containing input text files for translation.
  - `english_dir/` and `marathi_dir/`: Monitored directories for real-time file processing.

- **Build Files**
  - `Makefile`: Automates the build process for compiling the project.

- **Miscellaneous**
  - `.gitignore`: Specifies files and directories to be ignored by Git.

## Cloning the Repository

To get started with the project, clone the repository from GitHub:

```bash
git clone https://github.com/vsonje2102/Text-Translator-MealyMachine.git
```

This will create a local copy of the project in your current directory. Navigate to the project folder to begin working:

```bash
cd Text-Translator-MealyMachine
```
## Usage

### Prerequisites
- GCC compiler
- Linux environment (for inotify-based directory monitoring)

### Build
To compile the project, run:
```bash
make
```

### Run
1. **Translation**:
   ```bash
   ./main <path_to_csv_file>
   ```
   Example:
   ```bash
   ./main new/english_hindi.csv
   ```

2. **Real-Time Monitoring**:
   ```bash
   ./notify <path_to_csv_file>
   ```
   Example:
   ```bash
   ./notify english_hindi.csv
   ```

### Input/Output
- Place input files in `english_dir` or `marathi_dir` for real-time processing.
- Translated files will be saved in corresponding `_trans` directories.

### Customization
- Modify `english_hindi.csv` or `hindi_english.csv` to add or update translation rules.
- Use `map_old.txt` as a reference for character mappings.

## Known Issues
- The system may fail if the input file contains unsupported characters or if the state machine lacks a transition for a specific input.
- Ensure that file paths do not exceed the maximum allowed length (`PATH_MAX`).


