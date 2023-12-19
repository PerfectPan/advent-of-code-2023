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

const test = lines.filter(line => line.startsWith('{')).map(v => v.substring(1, v.length - 1)).map(v => {
  const [x,m,a,s] = v.split(',');
  const x_num = parseInt(x.split('=')[1]);
  const m_num = parseInt(m.split('=')[1]);
  const a_num = parseInt(a.split('=')[1]);
  const s_num = parseInt(s.split('=')[1]);
  return {
    x: x_num,
    m: m_num,
    a: a_num,
    s: s_num
  }
});

let ans = 0;

for (let i = 0; i < test.length; ++i) {
  let idx = 'in';
  while (idx != 'A' && idx != 'R') {
    for (let j = 0; j < ruleMap[idx].length; ++j) {
      if (typeof ruleMap[idx][j] == 'string') {
        idx = ruleMap[idx][j];
        break;
      } else {
        if (ruleMap[idx][j].type == '<') {
          if (test[i][ruleMap[idx][j].ch] < ruleMap[idx][j].number) {
            idx = ruleMap[idx][j].nxt;
            break;
          }
        } else {
          if (test[i][ruleMap[idx][j].ch] > ruleMap[idx][j].number) {
            idx = ruleMap[idx][j].nxt;
            break;
          }
        }
      }
    }
  }
  if (idx == 'A') {
    ans += test[i].s + test[i].a + test[i].x + test[i].m;
  }
}

fs.writeFileSync('./output.txt', ans + "", { encoding: 'utf-8' });
