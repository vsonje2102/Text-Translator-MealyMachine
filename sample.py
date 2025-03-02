outputs = [
    "a", "aa", "ī", "ii", "ū", "uu", "RRi", "RRI", "LLi", "LLI", "E", "aī", "^e", "ae", "^o", "o", "aū", "AU", ".a", "OM",
    "A", "I", "i", "U", "u", "R^i", "L^i", "E", "ai", "O", "au", ".m", ".N", "H", ".h", ".c", ".O", ""
]
print(set(outputs))
if len(outputs) == len(set(outputs)):
    print("All outputs are unique.")
else:
    print("There are duplicate outputs.")