# KMP
original = input().rstrip()
word = input().rstrip() 

# KMP table
table = [0 for _ in range(len(word))]
i = 0
for j in range(1, len(word)):
    while i > 0 and word[i] != word[j]:
        i = table[i-1]
    if word[i] == word[j]:
        i += 1
        table[j] = i

# KMP
res = 0
i = 0
for j in range(len(original)):
    while i > 0 and word[i] != original[j]:
        i = table[i-1]
    if word[i] == original[j]:
        i += 1
        if i == len(word):
            res += 1
            # j - i + 1
            i = table[i-1]

print(res)
