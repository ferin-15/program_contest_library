import cson

with open('programContestLibrary/library.cson', 'r') as f:
    obj = cson.load(f)

print(obj)

title = obj['.source.cpp'].keys()
val = obj['.source.cpp'].values()

print(title)
print(val)

with open('programContestLibrary/library.md', 'w') as f:
    for i,j in zip(title, val):
        f.write("## " + i + '\n')
        f.write('```cpp' + '\n')
        f.write(j['body'] + '\n')
        f.write('```' + '\n')
