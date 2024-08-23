
struct Solution;

fn gcd<T: Copy + PartialEq + std::ops::Rem<Output = T> + Default>(a: T, b: T) -> T {
    if b == T::default() {
        return a;
    }
    gcd(b, a % b)
}

fn lcm<T: Copy + PartialEq + std::ops::Rem<Output = T> + std::ops::Div<Output = T> + std::ops::Mul<Output = T> + Default>(a: T, b: T) -> T {
    a / gcd(a, b) * b
}

fn find_first_of(s: &str, chars: &[char]) -> Option<usize> {
    s.char_indices()
        .filter(|(_, c)| chars.contains(c))
        .map(|(i, _)| i)
        .next()
}

#[derive(Debug, PartialEq)]
struct Fraction {
    numerator: i32,
    denominator: i32,
}

impl Fraction{
    pub fn new (numerator: i32, denominator: i32) -> Fraction {
        Fraction {
            numerator, 
            denominator,
        }
    }

    pub fn add(&self, other: &Fraction) -> Fraction {
        let new_denominator = lcm(self.denominator.abs(), other.denominator.abs());
        Fraction::new(
            self.numerator * (new_denominator / self.denominator) + other.numerator * (new_denominator / other.denominator),
            new_denominator
        )
    }

    pub fn reduce(&self) -> Fraction {
        let d = gcd(self.numerator.abs(), self.denominator.abs());
        Fraction::new(
            self.numerator / d,
            self.denominator / d,
        )
    }

    pub fn to_string(&self) -> String {
        format!("{}/{}", self.numerator, self.denominator)
    }

    pub fn parse(s: &str) -> Option<Fraction> {
        let mut parts = s.split('/');
        let numenator_str = parts.next();
        let denominator_str = parts.next();
        if numenator_str.is_none() || denominator_str.is_none() {
            return None;
        }
        let numerator = numenator_str.unwrap().parse().ok()?;
        let denominator = denominator_str.unwrap().parse().ok()?;
        if denominator == 0 {
            None
        }
        else {
            Some(Fraction::new(numerator, denominator))
        }
    }
}

const SEPARATORS: [char; 2] = ['+', '-'];


fn next_fraction(s: &str) -> Option<(Fraction, usize)> {
    let end = find_first_of(&s[1..], &SEPARATORS);
    if let Some(end) = end {
        let fraction = Fraction::parse(&s[0..end + 1])?;
        Some((fraction, end + 1))
    }
    else {
        let fraction = Fraction::parse(&s)?;
        Some((fraction, s.len()))
    }
}


impl Solution {
    pub fn fraction_addition(expression: String) -> String {
        let mut current = Fraction::new(0, 1);
        let mut index = 0;
        while index < expression.len() {
            let (fraction, len) = next_fraction(&expression[index..]).unwrap();
            current = current.add(&fraction);
            index += len;
        }
        current.reduce().to_string()
    }
}


fn main() {
    let expression = "-1/2+1/2+1/3".to_string();
    let mut index = 0;
    let mut fractions = Vec::new();
    while index < expression.len() {
        let (fraction, len) = next_fraction(&expression[index..]).unwrap();
        fractions.push(fraction);
        index += len;
    }
}

#[cfg(test)]
mod test{
    use super::*;

    #[test]
    fn test_gcd(){
        assert_eq!(gcd(10, 5), 5);
        assert_eq!(gcd(14, 21), 7);
        assert_eq!(gcd(21, 14), 7);
        assert_eq!(gcd(21, 0), 21);
        assert_eq!(gcd(0, 21), 21);
    }
    #[test]
    fn test_lcm(){
        assert_eq!(lcm(10, 5), 10);
        assert_eq!(lcm(14, 21), 42);
        assert_eq!(lcm(21, 14), 42);
        assert_eq!(lcm(21, 0), 0);
        assert_eq!(lcm(0, 21), 0);
    }

    #[test]
    fn test_parse_fraction(){
        let expression = "-1/2+1/2+1/3".to_string();
        let mut index = 0;
        let mut fractions = Vec::new();
        while index < expression.len() {
            let (fraction, len) = next_fraction(&expression[index..]).unwrap();
            fractions.push(fraction);
            index += len;
        }
        assert_eq!(fractions.len(), 3);
        assert_eq!(fractions[0], Fraction::new(-1, 2));
        assert_eq!(fractions[1], Fraction::new(1, 2));
        assert_eq!(fractions[2], Fraction::new(1, 3));
    
    }
    #[test]
    fn test_solution_1(){
        let expression = "-1/2+1/2".to_string();
        let result = Solution::fraction_addition(expression);
        assert_eq!(result, "0/1".to_string());
    }
    fn test_solution_2(){
        let expression = "-1/2+1/2+1/3".to_string();
        let result = Solution::fraction_addition(expression);
        assert_eq!(result, "1/3".to_string());
    }
    fn test_solution_3(){
        let expression = "1/3-1/2".to_string();
        let result = Solution::fraction_addition(expression);
        assert_eq!(result, "-1/6".to_string());
    }
}