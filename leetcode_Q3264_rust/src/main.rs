use std::collections::BinaryHeap;

struct Solution;

#[derive(Eq, PartialEq)]
struct MyPair {
    value : i32,
    index : usize,
}

impl Ord for MyPair {
    fn cmp(&self, other: &Self)-> std::cmp::Ordering {
        if other.value == self.value {
            self.index.cmp(&other.index)
        }
        else{
            other.value.cmp(&self.value)
        }
    }
}
impl PartialOrd for MyPair {
    fn partial_cmp(&self, other: &Self)-> Option<std::cmp::Ordering> {
        Some(self.cmp(other))
    }
}



impl Solution {
    pub fn get_final_state(nums: Vec<i32>, k:i32, multiplier: i32) -> Vec<i32> {
        let mut heap = BinaryHeap::new();
        for i in 0..nums.len() {
            heap.push(MyPair{value:nums[i], index:i});
        }

        for _ in 0..k {
            let pair = heap.pop().unwrap();
            heap.push(MyPair{value:pair.value*multiplier, index: pair.index});
        }
        let mut result = vec![0;nums.len()];
        for i in 0..nums.len() {
            let pair = heap.pop().unwrap();
            result[pair.index] = pair.value;
        }
        result
    }
}
fn main() {
}
