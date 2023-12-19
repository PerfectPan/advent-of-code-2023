import fs from 'node:fs';

const lines = fs.readFileSync('./input.txt', { encoding: 'utf-8' }).split('\n').filter(line => line.length > 0);

const rules = lines.filter(line => !line.startsWith('{'));

const ruleMap = {};

for (let i = 0; i < rules.length; ++i) {
    const rule = rules[i];
    const parts = rule.split('{');
    const name = parts[0];
    const ruleList = parts[1].substring(0, parts[1].length - 1).split(',');
    ruleMap[name] = ruleList.map((r) => {
      if (r.includes(':')) {
        const [expr, nxt] = r.split(':');
        if (expr.includes('<')) {
          const [ch, number] = expr.split('<');
          return {
            type: '<',
            ch,
            number: parseInt(number),
            nxt
          }
        }
        const [ch, number] = expr.split('>');
        return {
          type: '>',
          ch,
          number: parseInt(number),
          nxt
        }
      }
      return r;
    });
}

const intersect = (x, y, a, b) => {
  const L = Math.max(x, a);
  const R = Math.min(y, b);
  
  if (L > R) {
    return [-1, -1];
  }
  return [L, R];
};

let ans = 0;

const getLen = (range) => range[1] - range[0] + 1;

const dfs = (workflow, rangeList) => {
  if (workflow === 'A' || workflow === 'R') {
    if (workflow == 'A') {
      ans += getLen(rangeList.x) * getLen(rangeList.m) * getLen(rangeList.a) * getLen(rangeList.s);
    }
    return;
  }

  for (let i = 0; i < ruleMap[workflow].length; ++i) {
    const rule = ruleMap[workflow][i];
    if (typeof rule == 'string') {
      dfs(rule, rangeList);
    } else if (rule.type === '<') {
      const range = rangeList[rule.ch];
      const newRange = intersect(range[0], range[1], 1, rule.number - 1);
      if (newRange[0] !== -1) {
        dfs(rule.nxt, { ...rangeList, [rule.ch]: newRange });
      }
      const elseRange = intersect(range[0], range[1], rule.number, 4000);
      rangeList[rule.ch] = elseRange;
      if (elseRange[0] === -1) {
        return;
      }
    } else {
      const range = rangeList[rule.ch];
      const newRange = intersect(range[0], range[1], rule.number + 1, 4000);
      if (newRange[0] !== -1) {
        dfs(rule.nxt, { ...rangeList, [rule.ch]: newRange });
      }
      const elseRange = intersect(range[0], range[1], 1, rule.number);
      rangeList[rule.ch] = elseRange;
      if (elseRange[0] === -1) {
        return;
      }
    }
  }
};

const startRange = {
  x: [1, 4000],
  s: [1, 4000],
  m: [1, 4000],
  a: [1, 4000]
};

dfs('in', startRange);

fs.writeFileSync('./output.txt', ans + "", { encoding: 'utf-8' });
