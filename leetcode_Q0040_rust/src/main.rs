use std::collections::HashMap;
struct Solution;


impl Solution {
    fn rec(freq_list : &Vec<(i32,i32)>, target: i32, index :usize, current : &mut Vec<i32>, current_sum: i32, result: &mut Vec<Vec<i32>>){
        if current_sum == target {
            result.push(current.clone());
            return;
        }
        if freq_list.len() == index {
            return;
        }
        let (value, count) = freq_list[index];

        Solution::rec(freq_list, target, index+1, current, current_sum, result);
        let mut push_count: usize = 0;
        for i in 1..=count {
            let new_sum: i32 = current_sum + value * i;
            if target < new_sum {
                break;
            }
            current.push(value);
            push_count += 1;
            Solution::rec(freq_list, target, index+1, current, new_sum, result);
        }
        current.truncate(current.len().saturating_sub(push_count));
    }

    pub fn combination_sum2(candidates: Vec<i32>, target: i32) -> Vec<Vec<i32>> {
        let mut freq_map = HashMap::new();
        for num in candidates {
            *freq_map.entry(num).or_insert(0) += 1;
        }
        let freq_list: Vec<(i32,i32)> = freq_map.iter().map(|k|(*k.0,*k.1)).collect();

        let mut result = Vec::new();
        let mut current = Vec::new();
        Solution::rec(&freq_list, target, 0, &mut current, 0, &mut result);
        result        
    }
}


fn test(candidates: Vec<i32>, target: i32) {
    println!("candidates = {:?}", candidates);
    println!("target = {:?}", target);
    let result = Solution::combination_sum2(candidates, target);
    println!("result = {:?}", result);
    println!();
}

fn main() {
    test(vec![10,1,2,7,6,1,5], 8);
    test(vec![2,5,2,1,2], 5);
}


#[cfg(test)]
mod tests{
    use super::*;

    fn vec_equals(a: &Vec<i32>, b: &Vec<i32>) -> bool {
        if a.len() != b.len() {
            return false;
        }
        let mut a = a.clone();
        a.sort();
        let mut b = b.clone();
        b.sort();
        a.iter().eq(b.iter())
    }

    fn check_collections(a: &Vec<Vec<i32>>, b: &Vec<Vec<i32>>) -> bool {
        if a.len() != b.len() {
            return false;
        }
        let mut a = a.clone();
        for inner in a.iter_mut() {
            inner.sort();
        }
        a.sort();

        for vlist in a.iter() {
            println!("{:?}", vlist);
        }

        let mut b = b.clone();
        for inner in b.iter_mut() {
            inner.sort();
        }
        b.sort();

        for vlist in a.iter() {
            println!("{:?}", vlist);
        }

        for i in 0..a.len() {
            if !vec_equals(&a[i], &b[i]) {
                return false;
            }
        }
        true
    }

    #[test]
    fn test1(){
        let ans = Solution::combination_sum2(vec![10,1,2,7,6,1,5], 8);
        assert!(check_collections(&ans, &(vec![vec![1,1,6],vec![1,2,5],vec![1,7],vec![2,6]])));
    }
    #[test]
    fn test2(){
        let ans = Solution::combination_sum2(vec![2,5,2,1,2], 5);
        assert!(check_collections(&ans, &(vec![vec![1,2,2],vec![5]])));
    }
}