// NOTE: depend on https://graphviz.org/download/
import fs from 'node:fs';
import { execSync } from 'child_process';

const lines = 
  fs.readFileSync('./input.txt', { encoding: 'utf-8' })
    .split('\n')
    .filter(line => line.length > 0)
    .map(v => `${v.replace(': ', '-> { ')} }`);

let graph = `digraph {
${lines.join('\n')}
}
`

fs.writeFileSync('./input.dot', graph, { encoding: 'utf-8' });

execSync(`neato -Tsvg input.dot > input.svg`, { stdio: 'inherit' });
