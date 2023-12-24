import fs from 'node:fs';

const lines = fs.readFileSync('./input.txt', { encoding: 'utf-8' }).split('\n');

const seeds = lines[0].split(':')[1].split(' ').map(_ => _.trim()).filter(_ => _ !== "").map(num => parseInt(num));
let seedsLine = [];
for (let i = 0; i < seeds.length; i += 2) {
  const [seed, num] = [seeds[i], seeds[i + 1]];
  seedsLine.push([seed, seed + num - 1]);
}

for (let i = 2; i < lines.length;) {
  if (lines[i].endsWith('map:')) {
    let r = i + 1;
    const seg = [];
    while (r < lines.length && lines[r] !== '') {
      const [source, des, interval] = lines[r].split(' ').map(_ => _.trim()).map(num => parseInt(num));
      seg.push([source, des, interval]);
      r++;
    }
    const processSeedLine = [];
    for (let j = 0; j < seedsLine.length; ++j) {
      const [s, e] = seedsLine[j];
      let flag = false;
      for (let k = 0; k < seg.length; ++k) {
        if (seg[k][1] <= s && e < seg[k][1] + seg[k][2]) {
          processSeedLine.push([seg[k][0] + s - seg[k][1], seg[k][0] + e - seg[k][1]]);
          flag = true;
          break;
        }
        if (seg[k][1] <= s && s < seg[k][1] + seg[k][2] && e >= seg[k][1] + seg[k][2]) {
          processSeedLine.push([seg[k][0] + s - seg[k][1], seg[k][0] + seg[k][2] - 1]);
          seedsLine.push([seg[k][1] + seg[k][2], e]);
          flag = true;
          break;
        }
        if (seg[k][1] > s && e < seg[k][1] + seg[k][2] && e >= seg[k][1]) {
          processSeedLine.push([seg[k][0], seg[k][0] + e - seg[k][1]]);
          seedsLine.push([s, seg[k][1] - 1]);
          flag = true;
          break;
        }
        if (seg[k][1] > s && e >= seg[k][1] + seg[k][2]) {
          processSeedLine.push([seg[k][0], seg[k][0] + seg[k][2] - 1]);
          seedsLine.push([s, seg[k][1] - 1]);
          seedsLine.push([seg[k][1] + seg[k][2], e]);
          flag = true;
          break;
        }
      }
      if (!flag) {
        processSeedLine.push([s, e]);
      }
    }
    seedsLine = processSeedLine;
    i = r;
  } else {
    i++;
  }
}

let ans = seedsLine[0][0];
for (let i = 1; i < seedsLine.length; ++i) {
  ans = Math.min(ans, seedsLine[i][0]);
}

fs.writeFileSync('./output.txt', ans + "", { encoding: 'utf-8' });
