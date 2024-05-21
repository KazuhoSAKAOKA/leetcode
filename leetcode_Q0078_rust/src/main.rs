

struct Solution;

impl Solution {

    fn rec(nums: &Vec<i32>,index :usize, length: usize, current: &mut Vec<i32>, ans : &mut Vec<Vec<i32>>){
        if length == current.len() {
            ans.push(current.clone());
            return;
        }
        for i in index..nums.len() {
            current.push(nums[i]);
            Solution::rec(nums,i+1, length, current, ans);
            current.pop();
        }
    } 

    pub fn subsets(nums: Vec<i32>) -> Vec<Vec<i32>> {
        let mut ans = Vec::<Vec::<i32>>::new();
        for i in 0..nums.len() + 1{
            let mut current = Vec::<i32>::new();
            Solution::rec(&nums, 0, i, &mut current, &mut ans);
        }
        ans
    }
}

fn output(ans : &Vec<Vec<i32>>){
    println!("====================");
    for i in ans {
        for j in i {
            print!("{} ", j);
        }
        println!();
    }
    println!("====================");
}

fn main() {
    let ans1 = Solution::subsets(vec![1,2,3]);
    output(&ans1);
    let ans2 = Solution::subsets(vec![0]);
    output(&ans2);
}
