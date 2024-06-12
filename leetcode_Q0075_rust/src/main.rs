

struct Solution;
impl Solution {
    pub fn sort_colors(nums: &mut Vec<i32>) {
        let mut bucket = vec![0; 3];
        for n in nums.iter(){
            bucket[*n as usize] += 1;
        }
        let mut index = 0;
        for i in 0..bucket.len() {
            for _ in 0..bucket[i] {
                nums[index] = i as i32;
                index += 1;
            }
        }
    }
}

fn test(mut s : Vec<i32>) {
    Solution::sort_colors(&mut s);
    for v in s.iter() {
        print!("{},", v);
    }
    println!("");
}

fn main() {
    test(vec![2,0,2,1,1,0]);
    test(vec![2,0,1]);
}
