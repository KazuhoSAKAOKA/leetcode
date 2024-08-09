
struct Solution;

const SIZE : usize = 3;
const SQUARE_SIZE : usize = SIZE * SIZE;
const TOTAL_SUM : usize = SQUARE_SIZE * (SQUARE_SIZE + 1) / 2;
const PART_SUM : usize = TOTAL_SUM / SIZE;

impl Solution {
    fn get_box_sum(prefix_sum: &Vec<Vec<i32>>, y_begin: usize, x_begin: usize, y_end : usize, x_end : usize) -> i32{
        return prefix_sum[y_end][x_end] - prefix_sum[y_end][x_begin] - prefix_sum[y_begin][x_end] + prefix_sum[y_begin][x_begin];
    }

    fn is_magic_square(grid: &Vec<Vec<i32>>, prefix_sum: &Vec<Vec<i32>>, y: usize, x: usize) -> bool {
        let mut used = vec![false; SQUARE_SIZE];
        for i in 0..SIZE {
            for j in 0..SIZE {
                let value = grid[y + i][x + j];
                if value < 1 || value > SQUARE_SIZE as i32 {
                    return false;
                }
                if used[(value - 1) as usize] {
                    return false;
                }
                used[(value - 1) as usize] = true;
            }
        }

        for i in 0..SIZE {
            if Solution::get_box_sum(&prefix_sum, y + i, x, y + i + 1, x + SIZE) as usize != PART_SUM {
                return false;
            }
            if Solution::get_box_sum(&prefix_sum, y, x + i, y + SIZE, x + i + 1) as usize != PART_SUM {
                return false;
            }
        }
        let mut diagonals_sum1 = 0;
        let mut diagonals_sum2 = 0;
        for i in 0..SIZE {
            diagonals_sum1 += grid[y + i][x + i];
            diagonals_sum2 += grid[y + i][x + SIZE - i - 1];
        }
        if diagonals_sum1 as usize != PART_SUM || diagonals_sum2 as usize != PART_SUM {
            return false;
        }
        return true;
    }

    pub fn num_magic_squares_inside(grid : Vec<Vec<i32>>) -> i32 {
        let height = grid.len();
        let width = grid[0].len();
        if height < SIZE || width < SIZE {
            0
        }
        else{
            let mut prefix_sum = vec![vec![0;width+1];height+1];
            for i in 0..height {
                for j in 0..width {
                    prefix_sum[i + 1][j + 1] = prefix_sum[i + 1][j] + grid[i][j];
                }
            }
            for i in 0..height {
                for j in 0..width {
                    prefix_sum[i + 1][j + 1] += prefix_sum[i][j + 1];
                }
            }
            
            let mut count = 0;

            for i in 0..(height - SIZE + 1) {
                for j in 0..(width - SIZE + 1) {
                    if Solution::is_magic_square(&grid, &prefix_sum, i, j) {
                        count += 1;
                    }
                }
            }
            count
        }
    }
}

fn test(grid: Vec<Vec<i32>>) {
    println!("========");
    for row in grid.iter() {
        println!("{:?}", row);
    }
    let ans = Solution::num_magic_squares_inside(grid);
    println!("ans = {}", ans);
}


fn main() {
    test(vec![vec![4,3,8,4],vec![9,5,1,9],vec![2,7,6,2]]);
}


#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    pub fn test1(){
        let grid = vec![vec![4,3,8,4],vec![9,5,1,9],vec![2,7,6,2]];
        let result = Solution::num_magic_squares_inside(grid);
        assert_eq!(result, 1);
    }

    #[test]
    pub fn test2(){
        let grid = vec![vec![8]];
        let result = Solution::num_magic_squares_inside(grid);
        assert_eq!(result, 0);
    }

    #[test]
    pub fn test3(){
        let grid = vec![vec![4,7,8],vec![9,5,1],vec![2,3,6]];
        let result = Solution::num_magic_squares_inside(grid);
        assert_eq!(result, 0);
    }

    #[test]
    pub fn test4(){
        let grid = vec![vec![5,5,5],vec![5,5,5],vec![5,5,5]];
        let result = Solution::num_magic_squares_inside(grid);
        assert_eq!(result, 0);
    }
}