import fs from 'node:fs';

const bricks = fs.readFileSync('./input.txt', { encoding: 'utf-8' }).split('\n').filter(line => line.length > 0);

const getDir = (start, end) => {
  if (start[0] != end[0]) {
    return 'x';
  }
  if (start[1] != end[1]) {
    return 'y';
  }
  return 'z';
};

const brickList = bricks.map((v) => {
  const [start, end] = v.split('~');
  const start_pos = start.split(',').map(_ => parseInt(_));
  const end_pos = end.split(',').map(_ => parseInt(_));

  return {
    start: start_pos,
    end: end_pos,
    dir: getDir(start_pos, end_pos)
  };
});

let m_x = 0, m_y = 0, m_z = 0;

brickList.forEach((brick) => {
  const { start, end } = brick;
  m_x = Math.max(m_x, Math.max(start[0], end[0]));
  m_y = Math.max(m_y, Math.max(start[1], end[1]));
  m_z = Math.max(m_z, Math.max(start[2], end[2]));
});

brickList.sort((a, b) => {
  return Math.min(a.start[2], a.end[2]) - Math.min(b.start[2], b.end[2]);
});

const mp = new Array((m_x + 1)).fill(0).map(() => new Array(m_y + 1).fill(0).map(() => new Array(m_z + 1).fill(0)));

brickList.forEach((brick, index) => {
  const { start, end } = brick;
  for (let x = Math.min(start[0], end[0]); x <= Math.max(start[0], end[0]); x++) {
    for (let y = Math.min(start[1], end[1]); y <= Math.max(start[1], end[1]); ++y) {
      for (let z = Math.min(start[2], end[2]); z <= Math.max(start[2], end[2]); ++z) {
        mp[x][y][z] = index + 1;
      }
    }
  }
});

brickList.forEach((brick, index) => {
  if (brick.dir == 'x' || brick.dir == 'y') {
    let temp_z = brick.start[2] - 1;
    const z = brick.start[2];
    while (temp_z >= 1) {
      let flag = false;
      for (let x = Math.min(brick.start[0], brick.end[0]); x <= Math.max(brick.start[0], brick.end[0]); x++) {
        for (let y = Math.min(brick.start[1], brick.end[1]); y <= Math.max(brick.start[1], brick.end[1]); ++y) {
          if (mp[x][y][temp_z] != 0) {
            flag = true;
          }
        }
      }

      if (flag) {
        break;
      }
      temp_z -= 1;
    }
    temp_z += 1;

    for (let x = Math.min(brick.start[0], brick.end[0]); x <= Math.max(brick.start[0], brick.end[0]); x++) {
      for (let y = Math.min(brick.start[1], brick.end[1]); y <= Math.max(brick.start[1], brick.end[1]); ++y) {
        mp[x][y][z] = 0;
        mp[x][y][temp_z] = index + 1;
      }
    }
    brick.start[2] = brick.end[2] = temp_z;
  } else {
    let temp_z = Math.min(brick.start[2], brick.end[2]) - 1;
    let z = Math.min(brick.start[2], brick.end[2]);
    const x = brick.start[0], y = brick.start[1];
    while (temp_z >= 1) {
      if (mp[x][y][temp_z] != 0) {
        break;
      }
      temp_z -= 1;
    }
    temp_z += 1;
    for (let z = Math.min(brick.start[2], brick.end[2]); z <= Math.max(brick.start[2], brick.end[2]); ++z) {
      mp[x][y][z] = 0;
    }
    brick.start[2] -= (z - temp_z), brick.end[2] -= (z - temp_z);
    for (let z = Math.min(brick.start[2], brick.end[2]); z <= Math.max(brick.start[2], brick.end[2]); ++z) {
      mp[x][y][z] = index + 1;
    }
  }
});

for (let z = m_z; z >= 1; --z) {
  let str = '';
  for (let x = 0; x <= m_x; ++x) {
    let char = '.';
    for (let y = 0; y <= m_y; ++y) {
      if (mp[x][y][z] !== 0) {
        char = mp[x][y][z];
        break;
      }
    }
    str += char;
  }
}

const test = () => {
  for (let index = 0; index < brickList.length; ++index) {
    const brick = brickList[index];
    if (brick.dir == 'x' || brick.dir == 'y') {
      let temp_z = brick.start[2] - 1;
      const z = brick.start[2];
      while (temp_z >= 1) {
        let flag = false;
        for (let x = Math.min(brick.start[0], brick.end[0]); x <= Math.max(brick.start[0], brick.end[0]); x++) {
          for (let y = Math.min(brick.start[1], brick.end[1]); y <= Math.max(brick.start[1], brick.end[1]); ++y) {
            if (mp[x][y][temp_z] != 0) {
              flag = true;
            }
          }
        }
  
        if (flag) {
          break;
        }
        temp_z -= 1;
      }
      temp_z += 1;
      
      if (temp_z !== z) {
        return false;
      }
    } else {
      let temp_z = Math.min(brick.start[2], brick.end[2]) - 1;
      let z = Math.min(brick.start[2], brick.end[2]);
      const x = brick.start[0], y = brick.start[1];
      while (temp_z >= 1) {
        if (mp[x][y][temp_z] != 0) {
          break;
        }
        temp_z -= 1;
      }
      temp_z += 1;
      if (temp_z !== z) {
        return false;
      }
    }
  }
  return true;
};

let ans = 0;

brickList.forEach((brick, index) => {
  const { start, end } = brick;
  for (let x = Math.min(start[0], end[0]); x <= Math.max(start[0], end[0]); x++) {
    for (let y = Math.min(start[1], end[1]); y <= Math.max(start[1], end[1]); ++y) {
      for (let z = Math.min(start[2], end[2]); z <= Math.max(start[2], end[2]); ++z) {
        mp[x][y][z] = 0;
      }
    }
  }
  ans += test();
  for (let x = Math.min(start[0], end[0]); x <= Math.max(start[0], end[0]); x++) {
    for (let y = Math.min(start[1], end[1]); y <= Math.max(start[1], end[1]); ++y) {
      for (let z = Math.min(start[2], end[2]); z <= Math.max(start[2], end[2]); ++z) {
        mp[x][y][z] = index + 1;
      }
    }
  }
});

fs.writeFileSync('./output.txt', ans + "", { encoding: 'utf-8' });
