from english_to_Hindi_transition_table import transition_table_eh

def mealy_machine(input_string, start_state="s0"):
    state = start_state
    output = []

    for symbol in input_string:
        while symbol not in transition_table_eh.get(state, {}):  # If no transition found
            print(f"Error: No transition found for ({state}, {symbol})")
            symbol_temp = "others"

            if symbol_temp in transition_table_eh.get(state, {}):  # Check 'others'
                state, output_symbol = transition_table_eh[state][symbol_temp]
                output.append(output_symbol)
                print(f"Resetting state to {state}")
            else:
                print(f"Error: No transition found for ({state}, {symbol_temp}). Stopping.")
                return "".join(output)  # Stop processing if no valid transition

        next_state, output_symbol = transition_table_eh[state][symbol]
        output.append(output_symbol)
        print(f"After processing '{symbol}': State = {next_state}, Output = {output_symbol}")
        state = next_state

    return "".join(output)

# Example Usage
input_string = "chaTakaaa*e,"
output_string = mealy_machine(input_string)
print(f"Output: {output_string}")
