import fs from 'node:fs';

const games = fs.readFileSync('./input.txt', { encoding: 'utf-8' });

let ans = 0;

games.split('\n').map((game, index) => {
  const rounds = game.split(':')[1].split(';').map(round => round.trim());
  const limit = {
    red: 0,
    green: 0,
    blue: 0
  };
  for (let i = 0; i < rounds.length; ++i) {
    const cubes = rounds[i].split(',').map(_ => _.trim().split(' '));
    for (const [number, color] of cubes) {
      limit[color] = Math.max(limit[color], +number);
    }
  }
  ans += Object.keys(limit).reduce((prev, color) => prev * limit[color], 1);
});

fs.writeFileSync('./output.txt', ans + "", { encoding: 'utf-8' });
