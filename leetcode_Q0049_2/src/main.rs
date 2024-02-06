
use std::collections::HashMap;

struct Solution{

}

impl Solution {
    pub fn group_anagrams(strs: Vec<String>) -> Vec<Vec<String>> {
        
        let mut map :HashMap<String, Vec<String>> = HashMap::new();
        for s in strs {
            let mut buffer : Vec<char> = s.chars().collect();
            buffer.sort();
            let sorted :String = buffer.into_iter().collect();
            let mut p = map.get_mut(&sorted);

            match p {
                Some(mut items) => items.push(s),
                None => {
                    let newlist = vec![s];
                    map.insert(sorted, newlist);
                },
            };
        }
        let mut ans : Vec<Vec<String>> = vec![];
        for (_, values) in map {
            ans.push(values.clone());
        }
        ans
    }
}

fn main() {
    let ans = Solution::group_anagrams(vec!["eat".to_string(),"tea".to_string(),"tan".to_string(),"ate".to_string(),"nat".to_string(),"bat".to_string()]);

    for list in ans {
        for s in list {
            print!("{},", s);
        }
        println!("");
    }
}
