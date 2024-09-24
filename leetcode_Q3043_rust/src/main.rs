struct Solution;

use std::cmp::max;
use std::collections::HashMap;

struct Node {
    nodes: HashMap<u8, Box<Node>>,
}

struct TrieTree {
    root: Node,
}

fn create_digit_vec(value: i32) -> Vec<u8> {
    if value == 0 {
        return vec![0];
    }
    let mut rev_digits = Vec::new();
    let mut current = value;
    while current > 0 {
        rev_digits.push((current % 10) as u8);
        current /= 10;
    }
    rev_digits.reverse();
    rev_digits
}

impl TrieTree {
    fn new() -> TrieTree {
        TrieTree {
            root: Node {
                nodes: HashMap::new(),
            },
        }
    }

    fn add(&mut self, value: i32) {
        let digits = create_digit_vec(value);
        let mut current_node = &mut self.root;
        for digit in digits {
            current_node = current_node.nodes.entry(digit).or_insert(Box::new(Node {
                nodes: HashMap::new(),
            }));
        }
    }

    fn get_max_common_length(&self, value: i32) -> usize {
        let digits = create_digit_vec(value);
        let mut current_node = &self.root;
        for (i, digit) in digits.iter().enumerate() {
            match current_node.nodes.get(digit) {
                Some(node) => {
                    current_node = node;
                }
                None => {
                    return i;
                }
            }
        }
        digits.len()
    }
}

impl Solution {
    pub fn longest_common_prefix(arr1: Vec<i32>, arr2: Vec<i32>) -> i32 {
        let mut trie = TrieTree::new();
        for value in arr1 {
            trie.add(value);
        }

        let mut max_common_length = 0;
        for value in arr2 {
            max_common_length = max(max_common_length, trie.get_max_common_length(value));
        }
        max_common_length as i32
    }
}

fn view(arr1: Vec<i32>, arr2: Vec<i32>) {
    println!("ans={}", Solution::longest_common_prefix(arr1, arr2));
}

fn main() {
    view(vec![1, 10, 100], vec![1000]);
    view(vec![1, 2, 3], vec![4, 4, 4]);
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn test_example_1() {
        let arr1 = vec![1, 10, 100];
        let arr2 = vec![1000];
        assert_eq!((Solution::longest_common_prefix(arr1, arr2)), 3);
    }

    #[test]
    fn test_example_2() {
        let arr1 = vec![1, 2, 3];
        let arr2 = vec![4, 4, 4];
        assert_eq!((Solution::longest_common_prefix(arr1, arr2)), 0);
    }
}
