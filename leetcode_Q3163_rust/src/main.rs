

struct Solution;

struct Compresser{
    buffer: Vec<char>,
    current: char,
    current_streak : i32,
}

impl Compresser {
    pub fn new () -> Compresser{
        Compresser{
            buffer: Vec::new(),
            current: ' ',
            current_streak: 0,
        }
    }

    pub fn append(&mut self, c: char){
        if self.current == c {
            if self.current_streak == 9 {
                self.flush();
                self.current_streak = 1;
            }
            else {
                self.current_streak += 1;
            }
        }
        else{
            self.flush();
            self.current = c;
            self.current_streak = 1;
        }
    }

    pub fn flush(&mut self){
        if self.current_streak > 0 {
            let c = std::char::from_digit(self.current_streak as u32, 10).unwrap();
            self.buffer.push(c);
            self.buffer.push(self.current);
            self.current_streak = 0;
        }
    }

    pub fn to_string(&self) -> String {
        self.buffer.iter().collect()
    }

}


impl Solution {
    pub fn compressed_string(word: String) -> String {
        let mut compresser = Compresser::new();
        for c in word.chars(){
            compresser.append(c);
        }
        compresser.flush();
        compresser.to_string()
    }
}



fn main() {
    println!("Hello, world!");
}

#[cfg(test)]
mod test{
    use super::*;

    #[test]
    fn test_example1(){
        let ans = Solution::compressed_string("abcde".to_string());
        assert!(ans == "1a1b1c1d1e");
    }
    #[test]
    fn test_example2(){
        let ans = Solution::compressed_string("aaaaaaaaaaaaaabb".to_string());
        assert!(ans == "9a5a2b");
    }
}
