use std::collections::HashMap;

struct Solution;

impl Solution {
    pub fn minimum_pushes(word: String) -> i32 {
        let mut freq_map = HashMap::new();
        for c in word.chars() {
            *(freq_map.entry(c).or_insert(0)) += 1;
        }
        let mut order_list = vec![];
        for (k, v) in freq_map.iter() {
            order_list.push((*v,*k));
        }
        order_list.sort_by(|a,b| b.0.cmp(&a.0));        

        let mut result = 0;
        let mut key_index = 0;
        for (count, _) in order_list {
            let multiple = key_index/ 8 + 1;
            let push_count = count * multiple;
            result += push_count;
            key_index += 1;
        }

        result
    }
}


fn main() {
    let word = "abcde".to_string();
    let result = Solution::minimum_pushes(word);
    println!("Result: {}", result);
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_minimum_pushes() {
        assert_eq!(Solution::minimum_pushes("abcde".to_string()), 5);
        assert_eq!(Solution::minimum_pushes("xyzxyzxyzxyz".to_string()), 12);
        assert_eq!(Solution::minimum_pushes("aabbccddeeffgghhiiiiii".to_string()), 24);
    }
}