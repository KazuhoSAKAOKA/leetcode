struct Solution;

impl Solution {
    pub fn max_score_sightseeing_pair(values: Vec<i32>) ->i32 {
        let mut best_score = 0;
        let mut best_left = values[0] - 1;

        for i in 1..values.len() {
            let cur_score = best_left + values[i];
            best_score = best_score.max(cur_score);
            best_left = best_left.max(values[i]) - 1;
        }
        best_score
    }
}



fn main() {
    println!("Hello, world!");
}
