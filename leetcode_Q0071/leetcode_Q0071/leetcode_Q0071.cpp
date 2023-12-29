// leetcode_Q0071.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <deque>

using namespace std;

class Solution {
public:

    class state_machine {

    private:
        string m_current;
        deque<string> m_buffer;
    public:
        
        void append(char c) {
            if (c == '/') {
                if (m_current == ".") {

                }
                else if (m_current == "..") {
                    if (!m_buffer.empty()) {
                        m_buffer.pop_back();
                    }
                }
                else if (!m_current.empty()) {
                    m_buffer.push_back(m_current);
                }
                m_current.clear();
                return;
            }
            m_current += c;
        }
 
        string create() {
            if (m_buffer.empty()) { return "/"; }
            string buffer;
            while (!m_buffer.empty()) {
                buffer += '/';
                buffer += m_buffer.front();
                m_buffer.pop_front();
            }
            return buffer;
        }


    };

    string simplifyPath(string path) {
        state_machine canonical_path;
        for (auto&& c : path) {
            canonical_path.append(c);
        }
        canonical_path.append('/');
        return canonical_path.create();
    }
};


int main()
{
    cout << Solution().simplifyPath("/a/./b/../../c/") << endl;
    cout << Solution().simplifyPath("/home/") << endl;
    cout << Solution().simplifyPath("/../") << endl;
    cout << Solution().simplifyPath("/home//foo/") << endl;
    cout << Solution().simplifyPath("/.../") << endl;
    cout << Solution().simplifyPath("/.../.../.././") << endl;
}