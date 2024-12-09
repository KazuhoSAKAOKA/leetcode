struct Solution;

impl Solution {

    fn check_invalid(current_val: i32, next_val:i32)->i32{
        if current_val % 2 == next_val % 2 {
            1
        }
        else{
            0
        }
    }

    pub fn is_array_special(nums: Vec<i32>, queries: Vec<Vec<i32>>) -> Vec<bool> {
        let mut prefix_sums= vec![0; nums.len()];
        for i in 0..(nums.len() - 1) {
            prefix_sums[i + 1] = prefix_sums[i] + Solution::check_invalid(nums[i], nums[i + 1]);
        }
        let mut ans = Vec::with_capacity(queries.len());
        for query in queries.iter() {
            let left = query[0] as usize;
            let right = query[1] as usize;
            ans.push(prefix_sums[right] == prefix_sums[left]);
        }
        ans
    }
}


fn main() {
    println!("Hello, world!");
}


#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_1() {
        let nums = vec![3, 4, 1, 2, 6];
        let queries = vec![vec![0, 4]];
        let result = Solution::is_array_special(nums, queries);
        assert_eq!(result, vec![false]);
    }
    #[test]
    fn test_2() {
        let nums = vec![4,3,1,6];
        let queries = vec![vec![0,2],vec![2,3]];
        let result = Solution::is_array_special(nums, queries);
        assert_eq!(result, vec![false, true]);
    }
}