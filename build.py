import os
import json

DATA = []

for name in os.listdir('examples'):
    source = os.path.join('examples', name, 'main.cpp')
    input = os.path.join('examples', name, 'input.txt')
    DATA.append([name], {'source': source, 'input': input})

with open('docs/src/data.js', 'wt') as f:
    f.write('const DATA = ')
    json.dump(DATA, f)
    f.write(';\n')
    f.write('export default DATA;\n')
