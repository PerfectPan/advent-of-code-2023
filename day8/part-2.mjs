import fs from 'node:fs';

const lines = fs.readFileSync('./input.txt', { encoding: 'utf-8' }).split('\n');

const instruction = lines[0];

const graph = {};
const aList = [];

for (let i = 2; i < lines.length; ++i) {
  const [node, edge] = lines[i].split('=').map(_ => _.trim());
  const [left, right] = edge.substring(1, edge.length - 1).split(',').map(_ => _.trim());
  graph[node] = {
    left,
    right
  };
  if (node.endsWith('A')) {
    aList.push(node);
  }
}

const gcd = (x, y) => {
  return y === 0 ? x : gcd(y, x % y);
};

let ans = 0;
for (let i = 0; i < aList.length; ++i) {
  let st = aList[i], cnt = 0;
  for (; !st.endsWith('Z') ;) {
    for (const ins of instruction) {
      if (ins === 'L') {
        st = graph[st].left;
      } else {
        st = graph[st].right;
      }
      cnt++;
      if (st.endsWith('Z')) {
        break;
      }
    }
  }
  ans = ans === 0 ? cnt : ans * cnt / gcd(Math.max(ans, cnt), Math.min(ans, cnt));
}


fs.writeFileSync('./output.txt', ans + "", { encoding: 'utf-8' });
