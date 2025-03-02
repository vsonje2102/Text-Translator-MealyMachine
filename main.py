import sys
import string
import hindi_to_English_transition_table as transition_table_he
import english_to_Hindi_transition_table as transition_table_eh

def translate(input_string, transition_table, start_state="1"):
    state = start_state
    output = []
    store = False

    for symbol in input_string:
        #print(f"Processing symbol: {symbol}, Current state: {state}")
        if symbol.isdigit() or (symbol in string.punctuation and symbol not in [".", "*"]):
            if state == "1":
                output.append(symbol)
                #print("Appending symboL")
            else:
                store = True
                sym = symbol
                #print("Storing symbol for later")
        else:
            while symbol not in transition_table.get(state, {}):  # If no transition found
                symbol_temp = "others"
                #print(f"No transition found for symbol: {symbol}")
                if symbol_temp in transition_table.get(state, {}):  # Check 'others'
                    state, output_symbol = transition_table[state][symbol_temp]
                    output.append(output_symbol)
                    #print(f"New state: {state}, Output symbol: {output_symbol}")
                else:
                    #print("Stopping.")
                    return "".join(output)  # Stop processing if no valid transition

            # Process the symbol after valid transition is found
            next_state, output_symbol = transition_table[state][symbol]
            output.append(output_symbol)
            #print(f"Transition found. New state: {next_state}, Output symbol: {output_symbol}")
            state = next_state
            if store:
                output.append(sym)
                #print(f"Appending stored symbol")
                store = False

    if state != "1":
        # translating last symbol completely
        symbol = "others"
        next_state, output_symbol = transition_table[state][symbol]
        output.append(output_symbol)
        #print(f"Translating last symbol. New state: {next_state}, Output symbol: {output_symbol}")

    translated_output = "".join(output)
    #print(f"Translation completed")
    return translated_output

def process_file(input_filename, output_filename, transition_table):
    with open(input_filename, 'r', encoding='utf-8') as infile, open(output_filename, 'w', encoding='utf-8') as outfile:
        for line in infile:
            translated_text = translate(line.strip(), transition_table)
            outfile.write(translated_text + "\n")
    print(f"Translation completed. Output saved in {output_filename}")

if len(sys.argv) != 4:
    print("Usage: python script.py <input_file> <output_file> <-eh/-he>")
    sys.exit(1)

input_file = sys.argv[1]
output_file = sys.argv[2]
flag = sys.argv[3]

print(f"Input file: {input_file}, Output file: {output_file}, Flag: {flag}")

if flag == '-eh':
    transition_table = transition_table_eh.transition_table_eh
    print("Using English to Hindi transition table.")
elif flag == '-he':
    transition_table = transition_table_he.transition_table_he
    print("Using Hindi to English transition table.")
else:
    print("Invalid flag! Use -eh for English to Hindi or -he for Hindi to English.")
    sys.exit(1)

process_file(input_file, output_file, transition_table)
