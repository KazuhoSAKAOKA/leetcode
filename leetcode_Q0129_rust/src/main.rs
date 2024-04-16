use std::rc::Rc;
use std::cell::RefCell;

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

impl Solution {
    fn rec(node : Option<Rc<RefCell<TreeNode>>>, current :&mut Vec<i32>) -> i32 {

        match node {
            None => 0,
            Some(node_ptr) =>{
                let tn = (*node_ptr).borrow();
                if tn.left.is_none() && tn.right.is_none(){
                    let mut sum = tn.val;
                    let mut m = 10;
                    for value in current.iter().rev() {
                        sum += value * m;
                        m *= 10;
                    }
                    sum
                }
                else{
                    let mut sum = 0;
                    current.push(tn.val);
                    if !tn.left.is_none() {
                        sum += Solution::rec(tn.left.clone(), current);
                    }
                    
                    if !tn.right.is_none(){
                        sum += Solution::rec(tn.right.clone(), current);
                    }
                    current.pop();
                    sum
                }
            }
        }
    }


    pub fn sum_numbers(root: Option<Rc<RefCell<TreeNode>>>) -> i32 {
        let mut current = Vec::<i32>::new();
        Solution::rec(root, &mut current)
    }
}




fn main() {
    let mut root = TreeNode::new(1);
    let left = TreeNode::new(2);
    let right = TreeNode::new(3);
    root.left = Some(Rc::new(RefCell::new(left)));
    root.right = Some(Rc::new(RefCell::new(right)));

    let result = Solution::sum_numbers(Some(Rc::new(RefCell::new(root))));
    println!("{:?}", result);
}
