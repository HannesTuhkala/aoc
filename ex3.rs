use std::io::BufReader;
use std::io::BufRead;
use std::fs::File;
use std::fmt;

#[derive(Debug)]
pub struct Point2 {
    pub x: f32,
    pub y: f32,
}

impl Point2 {
    pub fn new(x: f32, y: f32) -> Point2 {
        Point2 {
            x,
            y,
        }
    }

    pub fn get_manhattan_distance(&self) -> f32 {
        (self.x.abs() + self.y.abs())
    }
}

impl fmt::Display for Point2 {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "x: {}, y: {}", self.x, self.y)
    }
}

#[derive(Debug)]
pub struct LineSegment {
    pub p1: Point2,
    pub p2: Point2,
}

impl LineSegment {
    pub fn new(p1: Point2, p2: Point2) -> Self {
        LineSegment {
            p1,
            p2,
        }
    }

    pub fn intersects(&mut self, v: LineSegment) -> Option<Point2> {
        let a1 = self.p2.y - self.p1.y;
        let b1 = self.p1.x - self.p2.x;
        let c1 = a1 * self.p1.x + b1 * self.p1.y;

        let a2 = v.p2.y - v.p1.y;
        let b2 = v.p1.x - v.p2.x;
        let c2 = a2 * v.p1.x + b2 * v.p1.y;

        let det = a1 * b2 - a2 * b1;

        if det != 0. {
            let x = (b2 * c1 - b1 * c2) / det;
            let y = (a1 * c2 - a2 * c1) / det;
            let p = Point2::new(x, y);
        
            if self.check(x, y) && v.check(x, y) && !(x == 0. && y == 0.) {
                return Some(p);
            }
        }

        None
    }

    fn check(&self, x: f32, y: f32) -> bool {
        return self.min_x() <= x && x <= self.max_x() &&
            self.min_y() <= y && y <= self.max_y();
    }
    
    pub fn max_x(&self) -> f32 {
        let min = if self.p1.x >= self.p2.x {
            self.p1.x
        } else {
            self.p2.x
        };

        min
    }

    pub fn max_y(&self) -> f32 {
        let min = if self.p1.y >= self.p2.y {
            self.p1.y
        } else {
            self.p2.y
        };

        min

    }
    
    pub fn min_x(&self) -> f32 {
        let min = if self.p1.x <= self.p2.x {
            self.p1.x
        } else {
            self.p2.x
        };

        min
    }

    pub fn min_y(&self) -> f32 {
        let min = if self.p1.y <= self.p2.y {
            self.p1.y
        } else {
            self.p2.y
        };

        min
    }
}

pub fn read(filename: &str) -> Vec<(char, f32)> {
    let f = File::open(filename).unwrap();
    let reader = BufReader::new(f);
    let mut u: Vec<(char, f32)> = vec!();

    for line in reader.lines() {
        for value in line.unwrap().split(',') {
            let c: char = value.chars().next().unwrap();
            let d: f32 = value[1..].parse().unwrap();
            let g: (char, f32) = (c, d);
            u.push(g);
        }
    }
    
    u
}

fn main() {
    let u1: Vec<(char, f32)> = read("u1");
    let u2: Vec<(char, f32)> = read("u2");

    let mut v: Vec<Point2> = vec!();

    let (mut x1, mut y1) = (0., 0.);
    let (mut x2, mut y2) = (0., 0.);
    
    for (u, d) in &u1 {
        match u {
            'U' => {
                y2 += d;
            }, 
            'R' => {
                x2 += d;
            },
            'D' => {
                y2 -= d;
            },
            'L' => {
                x2 -= d;
            },
            _ => {
                continue;
            }
        }

        let (mut x3, mut y3) = (0., 0.);
        let (mut x4, mut y4) = (0., 0.);

        let p1 = Point2::new(x1, y1);
        let p2 = Point2::new(x2, y2);
        let mut v1 = LineSegment::new(p1, p2);

        for (l, g) in &u2 {
            match l {
                'U' => {
                    y4 += g;
                },
                'R' => {
                    x4 += g;
                },
                'D' => {
                    y4 -= g;
                },
                'L' => {
                    x4 -= g;
                },
                _ => {
                    continue;
                }
            }
            
            let p3 = Point2::new(x3, y3);
            let p4 = Point2::new(x4, y4);
            let v2 = LineSegment::new(p3, p4);

            if let Some(x) = v1.intersects(v2) {
                v.push(x);
            }

            x3 = x4;
            y3 = y4;
            x1 = x2;
            y1 = y2;
        }
    }

    println!("{:?}", v);

    let lowest: f32 = v.iter().fold(std::f32::INFINITY, |acc, x| {
        if acc <= x.get_manhattan_distance() {
            acc
        } else {
            x.get_manhattan_distance()
        }
    });

    println!("Lowest manhattan distance is: {}", lowest);
}

