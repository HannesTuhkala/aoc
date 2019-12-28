use std::collections::HashMap;

fn main() {
    let start: usize = 359282;
    let end: usize = 820401;
    let mut passwords: usize = 0;

    for n in start..=end {
        if is_valid_password(n) {
            passwords += 1;
        }
    }

    println!("The number of different passwords between {}-{} is: {}", start, end, passwords);
}

fn is_valid_password(n: usize) -> bool {
    let k = n.to_string();
    let x: Vec<char> = k.chars().collect();
    let mut adj: bool = false;
    let mut doubles: HashMap<char, usize> = HashMap::new();

    for i in 0..5 {
        if x[i] > x[i + 1] {
            return false;
        }

        if x[i] == x[i + 1] {
            let counter = doubles.entry(x[i]).or_insert(0);
            *counter += 1;
        }
    }

    for (_, v) in doubles.iter() {
        // If there is atleast 1 double in the digit, then it is a valid password
        if v - 1 == 0 {
            adj = true;
        }
    }

    adj
}
