# English-Hindi / Hindi-English Translator (v1.1.0)

## Overview
This project is a **finite-state machine-based** English-to-Hindi and Hindi-to-English translator. It processes input text character by character, following predefined transition rules to generate the translated output. The transition logic is stored in separate **transition tables**, ensuring accuracy and flexibility.

### How It Works
1. **Finite State Machine (FSM) Approach:**
   - The translation process follows a **state-based model**, where each character triggers a state transition.
   - Depending on the state and input character, the appropriate Hindi or English equivalent is produced.
   
2. **Transition Tables:**
   - The transition tables define how each character transitions to the next state and what output is generated.
   - Two separate tables are used for **English-to-Hindi** and **Hindi-to-English** translation.
   
3. **Command-Line Interface (CLI):**
   - Users can run the script via the command line, providing an **input file**, an **output file**, and a flag specifying the translation direction.
   
### Features
✅ **Bi-Directional Translation** (English ⬌ Hindi)  
✅ **Finite State Machine-based processing**  
✅ **Handles Digits and Punctuation**  
✅ **Efficient transition logic** for accurate translation  
✅ **Command-line execution for easy automation**  

## Usage
Run the script from the command line:
```bash
python main.py <input_file> <output_file> <-eh/-he>
```
Where:
- `<input_file>`: Path to the input text file.
- `<output_file>`: Path to save the translated output.
- `-eh`: Translates **English to Hindi**.
- `-he`: Translates **Hindi to English**.

### Example:
```bash
python main.py input.txt output.txt -eh
```
This translates the **English text** in `input.txt` to **Hindi** and saves it in `output.txt`.

## Transition Table Format
The transition table follows this structure:
```python
{
    "current_state": {
        "input_character": ("next_state", "output_character"),
        "others": ("next_state", "output_character")  # Default transition for unknown inputs
    }
}
```
### Example:
```python
{
    "1": {
        "a": ("2", "अ"),
        "b": ("3", "ब"),
        "others": ("1", "")
    },
    "2": {
        "c": ("3", "क"),
        "others": ("1", "")
    }
}
```

## Functions
### `translate(input_string, transition_table, start_state="1")`
- Takes an **input string**, processes it through the FSM, and returns the **translated output**.
- Preserves **punctuation and digits**.

### `process_file(input_filename, output_filename, transition_table)`
- Reads the input file, **translates** each line, and writes the result to the output file.

---

## Changes from v1.0.2 to v1.1.0
| Feature | v1.0.2 (Old) | v1.1.0 (New) |
|---------|-------------|-------------|
| **Translation Function** | Separate functions for each direction | **Unified translation function** for both directions |
| **Transition Table Format** | Used `*` to mark vowels | Differentiation **handled within the table** |
| **State Naming** | Alphanumeric states (e.g., `s0`, `s1`) | Uses **numeric states** starting from `1` |
| **Symbol Handling** | Required extra conditions for symbols | **Now seamlessly handled** in FSM |
| **Efficiency** | Extra logic to handle cases | Optimized FSM for **faster execution** |

---

