struct Solution;


#[derive(PartialEq, Eq, Clone, Debug)]
pub struct ListNode {
    pub val: i32,
    pub next: Option<Box<ListNode>>
}
 
impl ListNode {
    #[inline]
    fn new(val: i32) -> Self {
        ListNode {
        next: None,
        val
        }
    }
}


use std::collections::HashSet;
impl Solution {
    pub fn modified_list(nums: Vec<i32>, head: Option<Box<ListNode>>) -> Option<Box<ListNode>> {
        let nums_set = nums.iter().collect::<HashSet<_>>();
        let mut dummy_head = ListNode::new(0);
        let mut before = &mut dummy_head;

        let mut current = head;
        while let Some(mut node) = current {
            if !nums_set.contains(&node.val) {
                before.next = Some(Box::new(ListNode::new(node.val)));
                before = before.next.as_mut().unwrap();
            }
            current = node.next.take();
        }
        
        dummy_head.next
    }
}


fn main() {
    println!("Hello, world!");
}

#[cfg(test)]
mod test{
    use super::*;
    #[test]
    fn test_example1() {
        let head = Some(Box::new(ListNode {
            val: 1,
            next: Some(Box::new(ListNode {
                val: 2,
                next: Some(Box::new(ListNode {
                    val: 3,
                    next: Some(Box::new(ListNode {
                        val: 4,
                        next: Some(Box::new(ListNode {
                            val: 5,
                            next: None,
                        })),
                    })),
                })),
            })),
        }));
        let nums = vec![1, 2, 3];
        let result = Solution::modified_list(nums, head);
        let expected = Some(Box::new(ListNode {
            val: 4,
            next: Some(Box::new(ListNode {
                val: 5,
                next: None,
            })),
        }));
        assert_eq!(result, expected);
    } 

    #[test]
    fn test_example2() {
        let head = Some(Box::new(ListNode {
            val: 1,
            next: Some(Box::new(ListNode {
                val: 2,
                next: Some(Box::new(ListNode {
                    val: 1,
                    next: Some(Box::new(ListNode {
                        val: 2,
                        next: Some(Box::new(ListNode {
                            val: 1,
                            next: Some(Box::new(ListNode { val: 2, next: None })),
                        })),
                    })),
                })),
            })),
        }));
        let nums = vec![1,];
        let result = Solution::modified_list(nums, head);
        let expected = Some(Box::new(ListNode {
            val: 2,
            next: Some(Box::new(ListNode {
                val: 2,
                next: Some(Box::new(ListNode { val: 2, next: None })),
            })),
        }));
        assert_eq!(result, expected);
    }     
    #[test]
    fn test_example3() {
        let head = Some(Box::new(ListNode {
            val: 1,
            next: Some(Box::new(ListNode {
                val: 2,
                next: Some(Box::new(ListNode {
                    val: 3,
                    next: Some(Box::new(ListNode {
                        val: 4,
                        next: None,
                    })),
                })),
            })),
        }));
        let nums = vec![5,];
        let result = Solution::modified_list(nums, head);
        let expected = Some(Box::new(ListNode {
            val: 1,
            next: Some(Box::new(ListNode {
                val: 2,
                next: Some(Box::new(ListNode {
                    val: 3,
                    next: Some(Box::new(ListNode {
                        val: 4,
                        next: None,
                    })),
                })),
            })),
        }));
        assert_eq!(result, expected);
    }     
}