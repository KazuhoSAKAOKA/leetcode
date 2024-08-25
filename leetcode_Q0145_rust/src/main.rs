// Definition for a binary tree node.
#[derive(Debug, PartialEq, Eq)]
pub struct TreeNode {
    pub val: i32,
   pub left: Option<Rc<RefCell<TreeNode>>>,
   pub right: Option<Rc<RefCell<TreeNode>>>,
}
 
 impl TreeNode {
  #[inline]
   pub fn new(val: i32) -> Self {
     TreeNode {
       val,
       left: None,
       right: None
     }
   }
}

struct Solution;

use std::rc::Rc;
use std::cell::RefCell;


impl Solution {

    fn postorder_traversal_rec(node : &Option<Rc<RefCell<TreeNode>>>, result: &mut Vec<i32>) {
        if let Some(node) = node {
            let node = node.borrow();
            Solution::postorder_traversal_rec(&node.left, result);
            Solution::postorder_traversal_rec(&node.right, result);
            result.push(node.val);
        }
    }

    pub fn postorder_traversal(root: Option<Rc<RefCell<TreeNode>>>) -> Vec<i32> {
        let mut result = Vec::new();
        Solution::postorder_traversal_rec(&root, &mut result);
        result
    }
}


fn main() {
    println!("Hello, world!");
}


#[cfg(test)]
mod test{
    use super::*;
    #[test]
    fn test_1() {
        let root = Rc::new(RefCell::new(TreeNode::new(1)));
        let right = Rc::new(RefCell::new(TreeNode::new(2)));
        let right_left = Rc::new(RefCell::new(TreeNode::new(3)));
        root.borrow_mut().right = Some(right.clone());
        right.borrow_mut().left = Some(right_left.clone());
        assert_eq!(Solution::postorder_traversal(Some(root)), vec![3, 2, 1]);
    }
    #[test]
    fn test_2() {
        assert_eq!(Solution::postorder_traversal(None), vec![]);
    }
    #[test]
    fn test_3() {
        let root = Rc::new(RefCell::new(TreeNode::new(1)));
        assert_eq!(Solution::postorder_traversal(Some(root)), vec![1]);
    }
}