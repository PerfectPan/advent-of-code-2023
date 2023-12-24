import fs from 'node:fs';

const lines = fs.readFileSync('./input.txt', { encoding: 'utf-8' }).split('\n');

const poker = lines.map(line => line.split(' '));

const getType = (card) => {
  const mp = {};
  for (let i = 0; i < card.length; ++i) {
    mp[card[i]] = (mp[card[i]] || 0) + 1;
  }
  const keyLen = Object.keys(mp).length;
  if (keyLen === 5) {
    return 1;
  }
  if (keyLen === 1) {
    return 7;
  }
  if (keyLen === 2) {
    const val = Object.keys(mp).map(v => mp[v]);
    if (val[0] === 1 || val[0] === 4) {
      return 6;      
    }
    return 5;    
  }
  if (keyLen === 3) {
    const val = Object.keys(mp).map(v => mp[v]).filter(v => v === 2);
    if (val.length > 0) {
      return 3; 
    }
    return 4;
  }
  return 2;
};

const list = ['A', 'K', 'Q', 'J', 'T', '9', '8', '7', '6', '5', '4', '3', '2'];

poker.sort(([pa], [pb]) => {
  const ta = getType(pa);
  const tb = getType(pb);
  if (ta === tb) {
    for (let i = 0; i < 5; ++i) {
      if (pa[i] != pb[i]) {
        return list.indexOf(pb[i]) - list.indexOf(pa[i]);        
      }
    }
  }
  return ta - tb;
});

let ans = 0;
for (let i = 0; i < poker.length; ++i) {
  ans += parseInt(poker[i][1]) * (i + 1);
}

fs.writeFileSync('./output.txt', ans + "", { encoding: 'utf-8' });
