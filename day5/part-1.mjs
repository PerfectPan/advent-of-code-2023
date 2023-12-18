import fs from 'node:fs';

const lines = fs.readFileSync('./input.txt', { encoding: 'utf-8' }).split('\n');

const seeds = lines[0].split(':')[1].split(' ').map(_ => _.trim()).filter(_ => _ !== "").map(num => parseInt(num));

for (let i = 2; i < lines.length;) {
  if (lines[i].endsWith('map:')) {
    let r = i + 1;
    const seg = [];
    while (r < lines.length && lines[r] !== '') {
      const [source, des, interval] = lines[r].split(' ').map(_ => _.trim()).map(num => parseInt(num));
      seg.push([source, des, interval]);
      r++;
    }
    for (let j = 0; j < seeds.length; ++j) {
      for (let k = 0; k < seg.length; ++k) {
        if (seg[k][1] <= seeds[j] && seeds[j] < seg[k][1] + seg[k][2]) {
          seeds[j] = seg[k][0] + seeds[j] - seg[k][1];
          break;
        }
      }
    }
    i = r;
  } else {
    i++;
  }
}

let ans = seeds[0];
for (let i = 1; i < seeds.length; ++i) {
  ans = Math.min(ans, seeds[i]);
}

fs.writeFileSync('./output.txt', ans + "", { encoding: 'utf-8' });
