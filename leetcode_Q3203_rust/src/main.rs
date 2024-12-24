struct Solution;


fn get_far(graph : &Vec<Vec<usize>>, start:usize, from :usize) -> (usize, usize) {
    let mut current_max : usize = 0;
    let mut current_max_index : usize = start;

    for next in graph[start].iter() {
        if *next != from {
            let (next_max, next_max_index) = get_far(graph, *next, start);
            if current_max < next_max + 1 {
                current_max = next_max + 1;
                current_max_index = next_max_index;
            }
        }
    }
    (current_max, current_max_index)
}

fn tree_diameter(edges : &Vec<Vec<i32>>) -> i32 {
    let mut graph: Vec<Vec<usize>> = vec![Vec::new();edges.len() + 1];
    for edge in edges.iter() {
        let u = edge[0] as usize;
        let v = edge[1] as usize;
        graph[u].push(v);
        graph[v].push(u);
    }
    let (_, p1) = get_far(&graph, 0, usize::MAX);
    let (len, _) = get_far(&graph,  p1, usize::MAX);
    len as i32
}

impl Solution {
    pub fn minimum_diameter_after_merge(edges1: Vec<Vec<i32>>, edges2: Vec<Vec<i32>>) -> i32 {
        let diameter1 = tree_diameter(&edges1);
        let diameter2 = tree_diameter(&edges2);
        let radius1 = (diameter1 + 1) / 2;
        let radius2 = (diameter2 + 1) / 2;
        std::cmp::max(std::cmp::max(diameter1, diameter2), radius1 + radius2 + 1)
    }
}


fn main() {
    println!("Hello, world!");
}

#[cfg(test)]
mod tests {
    use std::vec;

    use super::*;

    #[test]
    fn test_example_1(){
        let result = Solution::minimum_diameter_after_merge(vec![vec![0,1],vec![0,2],vec![0,3]],vec![vec![0,1]]);
        assert_eq!(3, result);
    }
    #[test]
    fn test_example_2(){
        let result = Solution::minimum_diameter_after_merge(vec![vec![0,1],vec![0,2],vec![0,3],vec![2,4],vec![2,5],vec![3,6],vec![2,7]],vec![vec![0,1],vec![0,2],vec![0,3],vec![2,4],vec![2,5],vec![3,6],vec![2,7]]);
        assert_eq!(5, result);
    }
    
}