// work for both mark
import fs from 'node:fs';

const lines = fs.readFileSync('./input.txt', { encoding: 'utf-8' }).split('\n');

const [time, distance] = lines;
const timeList = time.split(':')[1].split(' ').map(_ => _.trim()).filter(_ => _ !== "").map(num => parseInt(num));
const distanceList = distance.split(':')[1].split(' ').map(_ => _.trim()).filter(_ => _ !== "").map(num => parseInt(num));

let ans = 0;
for (let i = 0; i < timeList.length; ++i) {
  let cnt = 0;
  for (let speed = 1; speed <= timeList[i]; ++speed) {
    if ((timeList[i] - speed) * speed > distanceList[i]) {
      cnt++;
    }
  }
  ans = ans == 0 ? cnt : ans * cnt;
}

fs.writeFileSync('./output.txt', ans + "", { encoding: 'utf-8' });
