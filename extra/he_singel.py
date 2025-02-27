import hindi_to_English_transition_table as transition_table
import random
def mealy_machine(input_string, start_state="s0"):
    state = start_state
    output = []
    for symbol in input_string:
        if symbol in transition_table.transition_table_he.get(state, {}):
            next_state, output_symbol_1 , output_symbol_2 = transition_table.transition_table_he[state][symbol]
            output.append(random.choice([output_symbol_1, output_symbol_2]))
            state = next_state
        else:
            print(f" No transition found for ({state}, {symbol}). Stopping.")
    return "".join(output)

def process_file(input_filename, output_filename):
    with open(input_filename, 'r', encoding='utf-8') as infile, open(output_filename, 'w', encoding='utf-8') as outfile:
        for line in infile:
            translated_text = mealy_machine(line.strip())
            outfile.write(translated_text + "\n")
    print(f"Translation completed. Output saved in {output_filename}")

# Example Usage
#input_filename = "output.txt"
#output_filename = "output_2.txt"
#process_file(input_filename, output_filename)
ip = "aaeesisai chaai.mpiiya.ms T.hr.Ophai 2025 meM 23 phravrai kao daubaI a.mtarraASha.hTa.hraiy k.hraIkaET s.hTEDiiyma meM bhaarta aura     paAkiis.htaana kaE bich eka romaa.mchka mukaAblaA hauA, jaIsamae.m bhaArta ne paAkiis.htaana kaO 6 vIkeTa sE praajIt kIyaA. isa jait     maE.m bhArataiya kp.htaAn vIraATa kaohlai kai naabaaada 100 rano.m kai shatakaiy paaarai ne mahat.hvpUra.hN bhuumaIkaa naiibhaAee."
teext = mealy_machine(ip)
print(teext)
