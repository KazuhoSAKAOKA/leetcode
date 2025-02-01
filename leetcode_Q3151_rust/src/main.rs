struct Solution;

impl Solution {
    pub fn is_array_special(nums: Vec<i32>) -> bool {
        for i in 0..nums.len() - 1 {
            if nums[i] % 2 == nums[i + 1] % 2{
                return false;
            }
        }
        true
    }
}


fn main() {
    println!("{}", Solution::is_array_special(vec![1]));
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_example1() {
        assert!(Solution::is_array_special(vec![1]));
    }
    #[test]
    fn test_example2() {
        assert!(Solution::is_array_special(vec![2,1,4]));
    }
    #[test]
    fn test_example3() {
        assert!(!Solution::is_array_special(vec![4,3,1,6]));
    }
}
