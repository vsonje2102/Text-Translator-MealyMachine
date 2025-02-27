import sys
import random
import string
import hindi_to_English_transition_table as transition_table_he
import english_to_Hindi_transition_table as transition_table_eh

def english_to_hindi(input_string, start_state="s0"):
    print("Converting English to Hindi")
    state = start_state
    output = []

    for symbol in input_string:
        print(f"Processing symbol: {symbol}")
        if symbol.isdigit() or (symbol in string.punctuation and symbol not in [".", "*"]):
            output.append(symbol)
        else:
            while symbol not in transition_table_eh.transition_table_eh.get(state, {}):  # If no transition found
                symbol_temp = "others"
                print(f"No transition found for ({state}, {symbol}). Trying 'others' transition.")

                if symbol_temp in transition_table_eh.transition_table_eh.get(state, {}):  # Check 'others'
                    state, output_symbol = transition_table_eh.transition_table_eh[state][symbol_temp]
                    print(f"Transition found for 'others': ({state}, {output_symbol})")
                    output.append(output_symbol)
                else:
                    print(f"No valid transition found for ({state}, {symbol_temp}). Stopping.")
                    return "".join(output)  # Stop processing if no valid transition

            # Process the symbol after valid transition is found
            next_state, output_symbol = transition_table_eh.transition_table_eh[state][symbol]
            print(f"Transition found: ({state}, {symbol}) -> ({next_state}, {output_symbol})")
            output.append(output_symbol)
            state = next_state
        print("--------------------------")
        print(output)
    if state != "s0":
        # translating last symbol completly
        #print("exited For loop")
        symbol = "others"
        print(state)
        next_state, output_symbol = transition_table_eh.transition_table_eh[state][symbol]
        print(f"Transition found: ({state}, {symbol}) -> ({next_state}, {output_symbol})")
        output.append(output_symbol)        

    return "".join(output)

def hindi_to_english(input_string, start_state="s0"):
    print("Converting Hindi to English")
    state = start_state
    output = []

    for symbol in input_string:
        print(f"Processing symbol: {symbol}")
        if symbol.isdigit() or symbol in string.punctuation:
            output.append(symbol)
        else:
            if symbol in transition_table_he.transition_table_he.get(state, {}):
                next_state, output_symbol = transition_table_he.transition_table_he[state][symbol]
                print(f"Transition found: ({state}, {symbol}) -> ({next_state}, {output_symbol})")
                output.append(output_symbol)
                state = next_state
            else:
                print(f"No transition found for ({state}, {symbol}). Stopping.")
                return "".join(output)
  
    return "".join(output)

def process_file(input_filename, output_filename, function_name):
    with open(input_filename, 'r', encoding='utf-8') as infile, open(output_filename, 'w', encoding='utf-8') as outfile:
        for line in infile:
            translated_text = function_name(line.strip())
            outfile.write(translated_text + "\n")
    print(f"Translation completed. Output saved in {output_filename}")

if len(sys.argv) != 4:
    print("Usage: python script.py <input_file> <output_file> <-eh/-he>")
    sys.exit(1)

input_file = sys.argv[1]
output_file = sys.argv[2]
flag = sys.argv[3]

if flag == '-eh':
    translation_function = english_to_hindi
elif flag == '-he':
    translation_function = hindi_to_english
else:
    print("Invalid flag! Use -eh for English to Hindi or -he for Hindi to English.")
    sys.exit(1)

process_file(input_file, output_file, translation_function)
