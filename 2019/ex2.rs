use std::fs::File;
use std::io::{BufRead, BufReader};
 
fn read() -> Vec<usize> {
    let f = File::open("input_ex2").unwrap();
    let mut br = BufReader::new(f);
 
    let mut line = String::new();
    br.read_line(&mut line).unwrap();
    line.split(",")
        .map(|x| x.trim().parse::<usize>().expect("Not an integer"))
        .collect()
}
 
fn main() {
    println!("Part 1 answer: {}", run(12, 2));

    for n in 0..100 {
        for v in 0..100 {
            if run(n, v) == 19690720 {
                println!("Part 2 answer: {}", 100 * n + v);
            }
        }
    }
}

fn run(noun: usize, verb: usize) -> usize {
    let mut vec = read();
    let mut i = 0;

    vec[1] = noun;
    vec[2] = verb;
 
    loop {
        match vec[i] {
            1 => {
                let out = vec[i + 3];
                vec[out] = vec[vec[i + 1]] + vec[vec[i + 2]];
            },
            2 => {
                let out = vec[i + 3];
                vec[out] = vec[vec[i + 1]] * vec[vec[i + 2]];
            },
            _ => {
                break;
            },
        }
        i += 4;
    }

    vec[0]
}
