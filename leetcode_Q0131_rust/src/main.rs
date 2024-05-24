use std::string;


struct Solution;

impl Solution {

    fn is_palindrome(s: &str)->bool{
        for i in 0..s.len() / 2 {
            if s.chars().nth(i) != s.chars().nth(s.len() - i - 1) {
                return false;
            }
        }
        true
    }


    fn rec(s: &str, index: usize, current : &mut Vec<String>, ans : &mut Vec<Vec<String>>){
        if s.len() <= index {
            ans.push(current.clone());
            return;
        }

        for i in index..s.len() {
            let substr = &s[index..(i + 1)];
            if Solution::is_palindrome(substr) {
                current.push(substr.to_string());
                Solution::rec(s, i+1, current, ans);
                current.pop();
            }
        }

    }

    pub fn partition(s: String) -> Vec<Vec<String>> {
        let mut ans = Vec::new();
        Solution::rec(&s, 0, &mut Vec::new(), &mut ans);
        ans
    }
}


fn test(s: String) {
    println!("Test s = {}", s);
    let result  = Solution::partition(s);
    for list in result.iter() {
        for item in list.iter() {
            print!("{} ", item);
        }
        println!();
    }
}



fn main() {
    let r = Solution::is_palindrome("a");
    println!("r = {}", r);

    test("aab".to_string());
    test("a".to_string());
}
