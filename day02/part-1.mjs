import fs from 'node:fs';

const games = fs.readFileSync('./input.txt', { encoding: 'utf-8' });

let ans = 0;

const limit = {
  red: 12,
  green: 13,
  blue: 14,
};

games.split('\n').map((game, index) => {
  const rounds = game.split(':')[1].split(';').map(round => round.trim());
  let flag = true;
  for (let i = 0; i < rounds.length; ++i) {
    const cubes = rounds[i].split(',').map(_ => _.trim().split(' '));
    for (const [number, color] of cubes) {
      if (limit[color] < +number) {
        flag = false;
        i = rounds.length;
        break;
      }
    }
  }
  if (flag) {
    ans += index + 1;
  }
});

fs.writeFileSync('./output.txt', ans + "", { encoding: 'utf-8' });
