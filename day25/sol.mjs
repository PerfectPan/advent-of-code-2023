// Unofficial solution
// Use neato gen the graph to find the edges need to be cut
import fs from 'node:fs';

const edges = 
  fs.readFileSync('./input.txt', { encoding: 'utf-8' })
    .split('\n')
    .filter(line => line.length > 0)
    .map(v => v.split(': '))
    .map(([from, to]) => [from, to.split(' ').map(_ => _.trim())]);


let cnt = 0;
const nameToId = {};

edges.map(([from, to]) => {
  if (!nameToId[from]) {
    cnt++;
    nameToId[from] = cnt;
  }
  to.map(v => {
    if (!nameToId[v]) {
      cnt++;
      nameToId[v] = cnt;
    }
  });
});

const fa = new Array(cnt + 1).fill(0).map((_, index) => index);

const Find = (x) => x === fa[x] ? x : fa[x] = Find(fa[x]);

// bbp dvr
// gtj tzj
// qvq jzv
edges.map(([from, to]) => {
  const fromId = nameToId[from];
  to.map(v => {
    const toId = nameToId[v];
    if ((from === 'bbp' && v === "dvr") || (from === 'dvr' && v === "bbp")
    || (from === 'gtj' && v === "tzj") || (from === 'tzj' && v === "gtj")
    || (from === 'qvq' && v === "jzv") || (from === 'jzv' && v === "qvq")) {
      return;
    }
    const fromFa = Find(fromId);
    const toFa = Find(toId);
    fa[toFa] = fromFa;
  });
});

const group = {};

for (let i = 1; i <= cnt; ++i) {
  fa[i] = Find(i);
  if (group[fa[i]] === void 0) {
    group[fa[i]] = 1;
  } else {
    group[fa[i]] += 1;
  }
}

const ans = Object.keys(group).reduce((prev, u) => prev * group[u], 1);

fs.writeFileSync('./output.txt', ans + "", { encoding: 'utf-8' });
