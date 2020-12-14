use std::fs::File;
use std::io::{BufRead, BufReader};
 
fn read() -> Vec<usize> {
    let f = File::open("input_ex5").unwrap();
    let mut br = BufReader::new(f);
 
    let mut line = String::new();
    br.read_line(&mut line).unwrap();
    println!("{}", line);
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
    
    let input: usize = 1;

    loop {
        let s = vec[i].to_string();
        let r: Vec<char> = s.chars().collect();
        let len: usize = r.len();

        let op_code: usize = r[len-2] as usize + r[len-1] as usize;
        let mut ten: usize = 0;
        let mut hundred: usize = 0;
        let mut thousand: usize = 0;
        let param: usize = len - 2;

        if len >= 3 {
            if r[len - 3] as usize == 1 {
                ten = vec[i + 1];
            } else {
                ten = vec[vec[i + 1]];
            }
        }

        if len >= 4 {
            if r[len - 4] as usize == 1 {
                hundred = vec[i + 2];
            } else {
                hundred = vec[vec[i + 2]];
            }
        }

        if len >= 5 {
            if r[len - 5] as usize == 1 {
                thousand = vec[i + 3];
            } else {
                thousand = vec[vec[i + 3]];
            }
        }

        match op_code {
            1 => {
                let out = vec[i + 3];
                vec[out] = ten + hundred;
            },
            2 => {
                let out = vec[i + 3];
                vec[out] = ten * hundred;
            },
            3 => {
                let out = vec[i + 1];
                vec[out] = input;
            },
            4 => {
                let out = vec[i + 1];
                println!("{}", vec[out]);
            },
            _ => {
                break;
            },
        }

        i += param + 1;
    }

    vec[0]
}
