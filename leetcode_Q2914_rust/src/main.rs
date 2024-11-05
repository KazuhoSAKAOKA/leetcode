
struct Solution;
impl Solution {
    pub fn min_changes(s: String) -> i32 {
        let mut count = 0;
        let mut even = false;
        let mut prev = 'x';
        let mut index = 0;
        for c in s.chars() {
            if even {
                println!("current even {}", c);
                prev = c;
                even = false;
            }
            else{
                if c != prev {
                    count += 1;
                    println!("current odd {} inc, {}", c, count);
                }
                else{
                    println!("current odd {}", c);
                }
                even = true;
            }


            index += 1;
        }
        count
    }
}
fn main() {
    println!("{}", Solution::min_changes("1001".to_string()));
}
