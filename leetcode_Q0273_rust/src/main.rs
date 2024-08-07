

struct Solution;


const ONES : [&str; 10] = ["Zero", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine"];
const TEENS : [&str; 10] = ["Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"];
const TENS : [&str; 10] = ["", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"];
const HUNDRED : &str = "Hundred";
const THOUSANDS : [&str; 4] = ["", "Thousand", "Million", "Billion"];

impl Solution {

    fn convert(num : i32, mother : i32) -> Vec<i32> {
        let mut current = num;
        let mut temp = Vec::new();
        while current > 0 {
            temp.push(current % mother);
            current /= mother;
        }
        temp.reverse();
        temp
    }

    fn try_append_with_space(buffer : &mut String, value : &str) {
        if value.len() == 0 {
            return;
        }
        if buffer.len() > 0 {
            buffer.push_str(" ");
        }
        buffer.push_str(value);
    }

    fn get_eng(value : i32) -> String {
        let mut result = String::new();
        let hundreds_val = value / 100;
        if hundreds_val > 0 {
            result.push_str(ONES[hundreds_val as usize]);
            result.push_str(" ");
            result.push_str(HUNDRED);
        }
        let tens_val = value % 100;

        match tens_val{
            0 => result,
            10..=19 => {
                Solution::try_append_with_space(&mut result, TEENS[(tens_val - 10) as usize]);
                result
            },
            _ => {
                if tens_val > 10 {
                    Solution::try_append_with_space(&mut result, TENS[(tens_val / 10) as usize]);
                }
                let ones_val = tens_val % 10;
                if ones_val > 0 {
                    Solution::try_append_with_space(&mut result, ONES[ones_val as usize]);
                }
                result
            },
        }
    }


    pub fn number_to_words(num: i32) -> String {
        if num == 0 {
            "Zero".to_string()
        }
        else{
            let mut result = String::new();
            
            let engs = Solution::convert(num, 1000);
            let mut end_index = engs.len();
            for eng in engs {
                let eng_str = Solution::get_eng(eng);
                if eng_str.len() > 0 {
                    Solution::try_append_with_space(&mut result, &eng_str);
                    Solution::try_append_with_space(&mut result, THOUSANDS[end_index - 1]);
                }
                end_index -= 1;
            }
            result
        }
    }
}


fn test(value :i32){
    println!("ans = {}", Solution::number_to_words(value));
}

fn main() {
    test(123);
    test(12345);
    test(1234567);
    test(1000);
    test(1001);
}

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn test1() {
        assert_eq!(Solution::number_to_words(123), "One Hundred Twenty Three".to_string());
        assert_eq!(Solution::number_to_words(12345), "Twelve Thousand Three Hundred Forty Five".to_string());
        assert_eq!(Solution::number_to_words(1234567), "One Million Two Hundred Thirty Four Thousand Five Hundred Sixty Seven".to_string());
        assert_eq!(Solution::number_to_words(110110), "One Hundred Ten Thousand One Hundred Ten".to_string());
        assert_eq!(Solution::number_to_words(101), "One Hundred One".to_string());
        assert_eq!(Solution::number_to_words(1000), "One Thousand".to_string());
        assert_eq!(Solution::number_to_words(1001), "One Thousand One".to_string());
    }
}