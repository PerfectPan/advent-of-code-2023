import fs from 'node:fs';

const cards = fs.readFileSync('./input.txt', { encoding: 'utf-8' });

let ans = 0;

cards.split('\n').map((card) => {
  const [winList, numList] = card.split(':')[1].split('|').map(list => list.split(' ').map(_ => _.trim()).filter(_ => _ !== ""));
  const winSet = new Set(winList.map(num => parseInt(num)));
  const matchTime = numList.reduce((prev, num) => prev + (winSet.has(parseInt(num)) ? 1 : 0), 0);
  if (matchTime) {
    ans += 1 << (matchTime - 1);
  }
});

fs.writeFileSync('./output.txt', ans + "", { encoding: 'utf-8' });
