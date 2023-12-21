import fs from 'node:fs';

const lines = fs.readFileSync('./input.txt', { encoding: 'utf-8' }).split('\n').filter(line => line.length > 0);

const graph = {};
const node = {};

let root = '';

lines.map((line) => line.split(' -> ')).map(([from, to_list]) => {
  to_list = to_list.split(',').map(_ => _.trim());
  if (from.startsWith('%')) {
    graph[from.substring(1)] = {
      to_list,
      type: 1
    };
    node[from.substring(1)] = {
      type: 1,
      status: 'off'
    };
  } else if (from.startsWith('&')) {
    graph[from.substring(1)] = {
      to_list,
      type: 2
    };
    node[from.substring(1)] = {
      type: 2,
      status: 'off',
      conj: [],
    };
  } else {
    graph[from] = {
      to_list,
      type: 3
    };
    root = from;
  }
});

Object.keys(graph).map(v => {
  const { type, to_list } = graph[v];
  if (type === 1) {
    to_list.map((nxt) => {
      if (node[nxt].type == 2) {
        node[nxt].conj[v] = 'low';
      }
    });
  }
});

const flip = (node, pulse, from) => {
  if (!node) {
    return 'none';
  }
  if (node.type === 1) {
    if (pulse === 'high') {
      return 'none';
    }
    if (node.status == 'off') {
      node.status = 'on'; 
      return 'high';
    }
    node.status = 'off';
    return 'low';
  }
  node.conj[from] = pulse;
  if (Object.keys(node.conj).filter(v => node.conj[v] === 'high').length === Object.keys(node.conj).length) {
    return 'low';
  }
  return 'high';
};

let low_pulse_count = 0, high_pulse_count = 0;

for (let _ = 1; _ <= 1000; ++_) {
  let queue = [];
  low_pulse_count++;
  for (let j = 0; j < graph[root].to_list.length; ++j) {
    const to = graph[root].to_list[j];
    const pulse = flip(node[to], 'low');
    low_pulse_count++;
    if (pulse !== 'none') {
      queue.push([to, pulse]);
    }
  }
  while (queue.length > 0) {
    const new_queue = [];
    while (queue.length > 0) {
      const [to, pulse] = queue.shift();
      for (let j = 0; j < graph[to].to_list.length; ++j) {
        const to2 = graph[to].to_list[j];
        const nxt_pulse = flip(node[to2], pulse, to);
        if (pulse === 'low') {
          low_pulse_count++;
        } else {
          high_pulse_count++;
        }
        if (nxt_pulse !== 'none') {
          new_queue.push([to2, nxt_pulse]);
        }
      }
    }

    queue = new_queue;
  }
}

let ans = low_pulse_count * high_pulse_count;

fs.writeFileSync('./output.txt', ans + "", { encoding: 'utf-8' });
