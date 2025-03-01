###  English-Hindi/Hindi-English Translator

## Overview
This script performs translation between English and Hindi using a **finite state transition table**. The transition tables are stored in separate Python modules:
- `hindi_to_English_transition_table.py`
- `english_to_Hindi_transition_table.py`

## Transition Table Format
Each transition table follows this structure:
```python
{
    "current_state": {
        "input_symbol": ("next_state", "output_symbol"),
        "others": ("next_state", "output_symbol")  # Default transition
    }
}
```
Example:
```python
{
    "s0": {
        "a": ("s1", "अ"),
        "b": ("s2", "ब"),
        "others": ("s0", "")
    },
    "s1": {
        "c": ("s2", "क"),
        "others": ("s0", "")
    }
}
```

## Usage
Run the main from the command line:
```bash
python main.py <input_file> <output_file> <-eh/-he>
```
Where:
- `<input_file>`: Path to the input text file
- `<output_file>`: Path to save the translated output
- `<-eh>`: English to Hindi translation
- `<-he>`: Hindi to English translation

### Example:
```bash
python main.py input.txt output.txt -eh
```
This will translate English text from `input.txt` to Hindi and save it in `output.txt`.

## Functions
### `english_to_hindi(input_string, start_state="s0")`
- Converts English text to Hindi using the **English-to-Hindi transition table**.

### `hindi_to_english(input_string, start_state="s0")`
- Converts Hindi text to English using the **Hindi-to-English transition table**.

### `process_file(input_filename, output_filename, function_name)`
- Reads input text file line by line.
- Translates each line using the selected function.
- Saves the translated output in the specified output file.

## Error Handling
- If a character is not found in the transition table, it defaults to `"others"`, if available.
- If no valid transition is found, the script stops processing that input.
- The script validates user input and prints an error message if incorrect flags are used.

## Dependencies
- Python 3.x
- Transition table files (`hindi_to_English_transition_table.py`, `english_to_Hindi_transition_table.py`)

## Notes
- The script preserves **digits and punctuation** as they are.
- Ensure the transition table files are properly structured before running the script.


