import fs from 'node:fs';

class BinaryHeap {
  data = [];

  constructor(comparator) {
    this.comparator = comparator;
  }

  push(element) {
    this.data.push(element);
    let index = this.data.length - 1;
    while (index > 0) {
      const fa = Math.floor(index / 2);
      if (this.comparator(this.data[fa], this.data[index]) > 0) {
        [this.data[fa], this.data[index]] = [this.data[index], this.data[fa]];
        index = fa;
      } else {
        break;
      }
    }
  }

  top() {
    return this.data[0];
  }

  isEmpty() {
    return this.data.length === 0;
  }

  pop() {
    if (this.data.length === 0) {
      return;
    }
    const item = this.data.shift();
    if (this.data.length > 0) {
      const lastItem = this.data.pop();
      this.data.unshift(lastItem);
      let index = 0;
      while (index * 2 < this.data.length) {
        let child = index * 2;
        if (
          child + 1 < this.data.length &&
          this.comparator(this.data[child + 1], this.data[child]) < 0
        ) {
          child++;
        }
        if (this.comparator(this.data[child], lastItem) < 0) {
          this.data[index] = this.data[child];
          index = child;
        } else {
          break;
        }
      }
      this.data[index] = lastItem;
    }

    return item;
  }
}

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

let brickList = bricks.map((v) => {
  const [start, end] = v.split('~');
  const start_pos = start.split(',').map(_ => parseInt(_));
  const end_pos = end.split(',').map(_ => parseInt(_));

  return {
    start: start_pos,
    end: end_pos,
    dir: getDir(start_pos, end_pos),
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

brickList = brickList.map((v, index) => {
  return {
    ...v,
    index: index + 1
  };
});

const mp = new Array((m_x + 1)).fill(0).map(() => new Array(m_y + 1).fill(0).map(() => new Array(m_z + 1).fill(0)));

brickList.forEach((brick) => {
  const { start, end, index } = brick;
  for (let x = Math.min(start[0], end[0]); x <= Math.max(start[0], end[0]); x++) {
    for (let y = Math.min(start[1], end[1]); y <= Math.max(start[1], end[1]); ++y) {
      for (let z = Math.min(start[2], end[2]); z <= Math.max(start[2], end[2]); ++z) {
        mp[x][y][z] = index;
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

const effect = (idx) => {
  const heap = new BinaryHeap((a, b) => {
    return Math.min(a.start[2], a.end[2]) - Math.min(b.start[2], b.end[2]);
  });

  for (let i = 0; i < brickList.length; ++i) if (brickList[i].index !== idx) {
    heap.push(JSON.parse(JSON.stringify(brickList[i])));
  }

  const s = new Set();
  while (!heap.isEmpty()) {
    const brick = heap.top(); heap.pop();
    if (brick.dir == 'x' || brick.dir == 'y') {
      let temp_z = brick.start[2] - 1;
      const zz = brick.start[2];
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
          mp[x][y][zz] = 0;
          mp[x][y][temp_z] = brick.index;
        }
      }
      brick.start[2] = brick.end[2] = temp_z;
      
      if (temp_z !== zz) {
        s.add(brick.index);
        heap.push(JSON.parse(JSON.stringify(brick)));
      }
    } else {
      let temp_z = Math.min(brick.start[2], brick.end[2]) - 1;
      let zz = Math.min(brick.start[2], brick.end[2]);
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
      brick.start[2] -= (zz - temp_z), brick.end[2] -= (zz - temp_z);
      for (let z = Math.min(brick.start[2], brick.end[2]); z <= Math.max(brick.start[2], brick.end[2]); ++z) {
        mp[x][y][z] = brick.index;
      }

      if (temp_z !== zz) {
        s.add(brick.index);
        heap.push(JSON.parse(JSON.stringify(brick)));
      }
    }
  }
  return s.size;
};

let ans = 0;

brickList.forEach((brick) => {
  const { start, end } = brick;
  const copy_mp = new Array((m_x + 1)).fill(0).map(() => new Array(m_y + 1).fill(0).map(() => new Array(m_z + 1).fill(0)));
  for (let x = 0; x <= m_x; ++x) {
    for (let y = 0; y <= m_y; ++y) {
      for (let z = 0; z <= m_z; ++z) {
        copy_mp[x][y][z] = mp[x][y][z];
      }
    }
  }

  for (let x = Math.min(start[0], end[0]); x <= Math.max(start[0], end[0]); x++) {
    for (let y = Math.min(start[1], end[1]); y <= Math.max(start[1], end[1]); ++y) {
      for (let z = Math.min(start[2], end[2]); z <= Math.max(start[2], end[2]); ++z) {
        mp[x][y][z] = 0;
      }
    }
  }

  ans += effect(brick.index);

  for (let x = 0; x <= m_x; ++x) {
    for (let y = 0; y <= m_y; ++y) {
      for (let z = 0; z <= m_z; ++z) {
        mp[x][y][z] = copy_mp[x][y][z];
      }
    }
  }
});

fs.writeFileSync('./output.txt', ans + "", { encoding: 'utf-8' });
