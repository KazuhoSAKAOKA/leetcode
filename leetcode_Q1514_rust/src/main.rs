struct Solution;

fn check_update(probablities: &mut Vec<f64>, from: i32, to: i32, prob: f64) -> bool{
    if probablities[from as usize] != 0.0 && probablities[to as usize] < probablities[from as usize] * prob {
        probablities[to as usize] = probablities[from as usize] * prob;
        true
    } 
    else{
        false
    }
}

fn bellman_ford(n: i32, edges: &Vec<Vec<i32>>, prob: &Vec<f64>, s: i32, e: i32) -> f64 {
    let mut probabilities = vec![0.0; n as usize];
    probabilities[s as usize] = 1.0;
    let mut updated = true;
    while updated {
        updated = false;
        for i in 0..edges.len() {
            updated |= check_update(&mut probabilities, edges[i][0], edges[i][1], prob[i]);
            updated |= check_update(&mut probabilities, edges[i][1], edges[i][0], prob[i]);
        }
    }
    probabilities[e as usize]
}


impl Solution {
    pub fn max_probability(n: i32, edges: Vec<Vec<i32>>, succ_prob: Vec<f64>, start_node: i32, end_node: i32) -> f64 {
        bellman_ford(n, &edges, &succ_prob, start_node, end_node)
    }
}


fn main() {
    println!("Hello, world!");
}

#[cfg(test)]
mod tests{
    use super::*;
    #[test]
    fn test_example_1(){
        let edges = vec![vec![0, 1], vec![1, 2], vec![0, 2]];
        let succ_prob = vec![0.5, 0.5, 0.2];
        let ans = Solution::max_probability(3, edges, succ_prob, 0, 2);
        assert_eq!(ans, 0.25);
    }
    #[test]
    fn test_example_2(){
        let edges = vec![vec![0, 1], vec![1, 2], vec![0, 2]];
        let succ_prob = vec![0.5, 0.5, 0.3];
        let ans = Solution::max_probability(3, edges, succ_prob, 0, 2);
        assert_eq!(ans, 0.3);
    }

    #[test]
    fn test_example_3(){
        let edges = vec![vec![0, 1]];
        let succ_prob = vec![0.5];
        let ans = Solution::max_probability(3, edges, succ_prob, 0, 2);
        assert_eq!(ans, 0.0);
    }
}