import fs from 'node:fs';

const cards = fs.readFileSync('./input.txt', { encoding: 'utf-8' });

const cardList = cards.split('\n');
const cnt = new Array(cardList.length + 1).fill(1);

cardList.map((card, index) => {
  const [winList, numList] = card.split(':')[1].split('|').map(list => list.split(' ').map(_ => _.trim()).filter(_ => _ !== ""));
  const winSet = new Set(winList.map(num => parseInt(num)));
  const matchTime = numList.reduce((prev, num) => prev + (winSet.has(parseInt(num)) ? 1 : 0), 0);
  for (let i = 1; i <= matchTime; i++) {
    cnt[index + 1 + i] += cnt[index + 1];
  }
});

let ans = 0;

for (let i = 1; i <= cardList.length; ++i) {
  ans += cnt[i];
}

fs.writeFileSync('./output.txt', ans + "", { encoding: 'utf-8' });
