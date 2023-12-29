// leetcode_Q0157.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>


/**
 * The read4 API is defined in the parent class Reader4.
 *     
 */
int read4(char* buf4);

class Solution {
public:
    /**
     * @param buf Destination buffer
     * @param n   Number of characters to read
     * @return    The number of actual characters read
     */
    int read(char* buf, int n) {
        int readed = 0;
        while (readed < n) {
            const auto current = read4(buf + readed);
            readed += current;
        }
        return readed;
    }
};
int main()
{
    char temp[50];
    const auto v = Solution().read(temp, 3);

}


static const char* const PTR = "ABC";
int read4(char* buf4)
{
    memcpy_s(buf4, 50, PTR, 3);
    return 3;
}
