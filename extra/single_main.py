from transition_table import transition_table

def mealy_machine(input_string, start_state="s0"):
    state = start_state
    output = []

    for symbol in input_string:
        while symbol not in transition_table.get(state, {}):  # If no transition found
            print(f"Error: No transition found for ({state}, {symbol})")
            symbol_temp = "others"

            if symbol_temp in transition_table.get(state, {}):  # Check 'others'
                state, output_symbol = transition_table[state][symbol_temp]
                output.append(output_symbol)
                print(f"Resetting state to {state}")
            else:
                print(f"Error: No transition found for ({state}, {symbol_temp}). Stopping.")
                return "".join(output)  # Stop processing if no valid transition

        next_state, output_symbol = transition_table[state][symbol]
        output.append(output_symbol)
        print(f"After processing '{symbol}': State = {next_state}, Output = {output_symbol}")
        state = next_state

    return "".join(output)

# Example Usage
input_string = "aaeesisai chaai.mpiiya.ms T.hr.Ophai 2025 meM 23 phravrai kao daubaI a.mtarraASha.hTa.hraiy k.hraIkaET s.hTEDiiyma meM bhaarta aura     paAkiis.htaana kaE bich eka romaa.mchka mukaAblaA hauA, jaIsamae.m bhaArta ne paAkiis.htaana kaO 6 vIkeTa sE praajIt kIyaA. isa jait     maE.m bhArataiya kp.htaAn vIraATa kaohlai kai naabaaada 100 rano.m kai shatakaiy paaarai ne mahat.hvpUra.hN bhuumaIkaa naiibhaAee."
output_string = mealy_machine(input_string)
print(f"Output: {output_string}")
