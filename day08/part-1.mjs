import fs from 'node:fs';

const lines = fs.readFileSync('./input.txt', { encoding: 'utf-8' }).split('\n');

const instruction = lines[0];

const graph = {};

for (let i = 2; i < lines.length; ++i) {
  const [node, edge] = lines[i].split('=').map(_ => _.trim());
  const [left, right] = edge.substring(1, edge.length - 1).split(',').map(_ => _.trim());
  graph[node] = {
    left,
    right
  };
}

let st = "AAA", ans = 0;
for (; st !== 'ZZZ' ;) {
  for (const ins of instruction) {
    if (ins === 'L') {
      st = graph[st].left;
    } else {
      st = graph[st].right;
    }
    ans++;
    if (st === 'ZZZ') break;
  }
}

fs.writeFileSync('./output.txt', ans + "", { encoding: 'utf-8' });
