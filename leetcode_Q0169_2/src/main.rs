use std::collections::HashMap;

struct Solution{

}


impl Solution {
    pub fn majority_element(nums: Vec<i32>) -> i32 {
        let mut hm  = HashMap::new();
        let mut max_len = 0;
        let mut max_item = 0;
        for n in nums {
            let e = hm.entry(n).or_insert(0);
            *e += 1;
            if max_len < *e {
                max_len = *e;
                max_item = n;
            }
        };

        max_item
    }
}

fn main() {
    println!("{}", Solution::majority_element(vec![3,2,3]));
    println!("{}", Solution::majority_element(vec![2,2,1,1,1,2,2]));
}
