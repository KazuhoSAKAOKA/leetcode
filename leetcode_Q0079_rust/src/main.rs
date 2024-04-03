struct Solution {}

impl Solution {
    fn rec(
        board: &Vec<Vec<char>>,
        word: &String,
        index: usize,
        visited: &mut Vec<Vec<bool>>,
        i: usize,
        j: usize,
    ) -> bool {
        if word.chars().nth(index).unwrap() != board[i][j] {
            return false;
        }
        if word.len() - 1 == index {
            return true;
        }
        visited[i][j] = true;
        let directions = vec![(-1, 0), (1, 0), (0, -1), (0, 1)];
        for (di, dj) in directions {
            let i1 = (i as i32) + di;
            let j1 = (j as i32) + dj;
            if 0 <= i1
                && i1 < board.len() as i32
                && 0 <= j1
                && j1 < board[i].len() as i32
                && !visited[i1 as usize][j1 as usize]
            {
                if Self::rec(board, word, index + 1, visited, i1 as usize, j1 as usize) {
                    return true;
                }
            }
        }
        visited[i][j] = false;
        false
    }

    pub fn exist(board: Vec<Vec<char>>, word: String) -> bool {
        if word.len() == 0 {
            true
        } else {
            let mut visited = vec![vec![false; board[0].len()]; board.len()];
            for i in 0..board.len() {
                for j in 0..board[i].len() {
                    if Solution::rec(&board, &word, 0, &mut visited, i, j) {
                        return true;
                    }
                }
            }
            false
        }
    }
}

fn test(board: Vec<Vec<char>>, word: String) {
    if Solution::exist(board, word) {
        println!("Exist");
    } else {
        println!("Not Exist");
    }
}

fn main() {
    test(vec![vec!['a']], "a".to_string());
    test(
        vec![
            vec!['A', 'B', 'C', 'E'],
            vec!['S', 'F', 'C', 'S'],
            vec!['A', 'D', 'E', 'E'],
        ],
        "ABCCED".to_string(),
    );
    test(
        vec![
            vec!['A', 'B', 'C', 'E'],
            vec!['S', 'F', 'C', 'S'],
            vec!['A', 'D', 'E', 'E'],
        ],
        "SEE".to_string(),
    );
    test(
        vec![
            vec!['A', 'B', 'C', 'E'],
            vec!['S', 'F', 'C', 'S'],
            vec!['A', 'D', 'E', 'E'],
        ],
        "ABCB".to_string(),
    );
}
