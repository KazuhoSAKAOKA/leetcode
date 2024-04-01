
struct Solution{
}

impl Solution {
    pub fn length_of_last_word(s: String) -> i32 {
        s.chars().rev().skip_while(|&c| c == ' ').take_while(|&c| c != ' ').count() as i32
    }
}

fn main() {
    println!("{}", Solution::length_of_last_word("   fly me   to   the moon  ".to_string()));
    println!("{}", Solution::length_of_last_word("Hello World".to_string()));
    println!("{}", Solution::length_of_last_word("HelloWorld".to_string()));
    println!("{}", Solution::length_of_last_word("".to_string()));
}
