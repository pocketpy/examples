import os
import json

DATA = []

def read_file(path):
    with open(path, 'rt') as f:
        return f.read()

for name in os.listdir('examples'):
    source = os.path.join('examples', name, 'main.cpp')
    input = os.path.join('examples', name, 'input.txt')
    DATA.append([name, {'source': read_file(source), 'input': read_file(input)}])

with open('docs/src/data.js', 'wt') as f:
    f.write('const DATA = ')
    json.dump(DATA, f, indent=4)
    f.write(';\n')
    f.write('export default DATA;\n')
