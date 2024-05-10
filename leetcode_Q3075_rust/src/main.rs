
use std::cmp::max;
struct Solution;

impl Solution {
    pub fn maximum_happiness_sum(happiness: Vec<i32>, k: i32) -> i64 {
        let mut total :i64 = 0;
        let mut happiness = happiness;
        happiness.sort_by(|a, b| a.cmp(&b).reverse());
        for (i, happy) in happiness.iter().enumerate().take(k as usize) {
            let happy_current = max(0, *happy - i as i32);
            total += happy_current as i64;
        }
        total
    }
}

fn main() {
    let happiness = vec![1,2,3];
    println!("{}", Solution::maximum_happiness_sum(happiness, 2));

    let happiness = vec![1,1,1,1];
    println!("{}", Solution::maximum_happiness_sum(happiness, 2));

    let happiness = vec![2,3,4,5];
    println!("{}", Solution::maximum_happiness_sum(happiness, 1));

}
