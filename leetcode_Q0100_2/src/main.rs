use std::cell::RefCell;
use std::rc::Rc;

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
            right: None,
        }
    }
}

struct Solution {}

impl Solution {

    fn is_same_rec(p: &Option<Rc<RefCell<TreeNode>>>, q: &Option<Rc<RefCell<TreeNode>>>) -> bool{
        match p {
            Some(x) => match q {
                Some(y) => {
                    let p1 = x.borrow();
                    let q1 = y.borrow();
                    if (*p1).val == (*q1).val {
                    Solution::is_same_rec(&(*p1).left, &(*q1).left) && Solution::is_same_rec(&(*p1).right, &(*q1).right)
                } else{
                    false
                }
                },
                None => false,
            }
            None => match q {
                Some(_) => false,
                None => true,
            }
        }
    }
    


    pub fn is_same_tree(
        p: Option<Rc<RefCell<TreeNode>>>,
        q: Option<Rc<RefCell<TreeNode>>>,
    ) -> bool {
        Solution::is_same_rec(&p, &q)
    }
}

fn main() {



}
