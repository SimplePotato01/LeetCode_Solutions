#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <algorithm>
#include <deque>

using namespace std;

class Solution {
private:
    struct ListNode {
        int val;
        ListNode* next;
        ListNode(int x) : val(x), next(NULL) {}

    };

    int findFirst(const vector<int>& nums, int target) {
        // первое вхождение target (левый край)
        int lo = 0, hi = (int)nums.size() - 1;
        int result = -1;

        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;

            if (nums[mid] == target) {
                result = mid;       // запомнили, но ищем левее
                hi = mid - 1;
            }
            else if (nums[mid] < target) {
                lo = mid + 1;
            }
            else {
                hi = mid - 1;
            }
        }
        return result;
    }
    int findLast(const vector<int>& nums, int target) {
        // последнее вхождение target (правый край)
        int lo = 0, hi = (int)nums.size() - 1;
        int result = -1;

        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;

            if (nums[mid] == target) {
                result = mid;       // запомнили, но ищем правее
                lo = mid + 1;
            }
            else if (nums[mid] < target) {
                lo = mid + 1;
            }
            else {
                hi = mid - 1;
            }
        }
        return result;
    }

    void backtrack(const string& digits, int idx, const vector<string>& table, string& current, vector<string>& result) {
        // база: собрали букву для каждой цифры
        if (idx == (int)digits.size()) {
            result.push_back(current);
            return;
        }

        // буквы соответствующие текущей цифре
        const string& letters = table[digits[idx] - '0'];

        for (char c : letters) {
            current.push_back(c);              // выбор
            backtrack(digits, idx + 1, table, current, result);  // рекурсия
            current.pop_back();                // откат
        }
    }
    int expand(const string& s, int l, int r) {
        while (l >= 0 && r < (int)s.size() && s[l] == s[r]) {
            --l;
            ++r;
        }
        return r - l - 1;
    }
public:
    ListNode* detectCycle(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;

        // Фаза 1: ищем точку встречи
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;

            if (slow == fast) {
                // Фаза 2: ищем вход в цикл
                slow = head;
                while (slow != fast) {
                    slow = slow->next;
                    fast = fast->next;
                }
                return slow;   // вход в цикл
            }
        }
        return nullptr;   // цикла нет
    }
    bool hasCycle(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;

        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;          // +1 шаг
            fast = fast->next->next;    // +2 шага

            if (slow == fast) return true;
        }
        return false;
    }
    int lengthOfLIS(vector<int>& nums) {
        vector<int> tails;

        for (int x : nums) {
            auto it = lower_bound(tails.begin(), tails.end(), x);
            if (it == tails.end()) {
                tails.push_back(x);       // продлеваем
            }
            else {
                *it = x;                  // заменяем первый >= x
            }
        }
        return tails.size();
    }
    int findDuplicate(vector<int>& nums) {
        // Фаза 1: находим точку встречи медленного и быстрого
        int slow = nums[0];
        int fast = nums[0];

        do {
            slow = nums[slow];          // +1 шаг
            fast = nums[nums[fast]];    // +2 шага
        } while (slow != fast);

        // Фаза 2: находим вход в цикл
        slow = nums[0];                 // ставим одного в начало
        while (slow != fast) {
            slow = nums[slow];
            fast = nums[fast];
        }
        return slow;                    // это дубликат
    }
    int searchInsert(vector<int>& nums, int target) {
        int lo = 0, hi = (int)nums.size() - 1;

        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;

            if (nums[mid] == target) {
                return mid;
            }
            else if (nums[mid] < target) {
                lo = mid + 1;
            }
            else {
                hi = mid - 1;
            }
        }
        return lo;
    }
    vector<int> searchRange(vector<int>& nums, int target) {
        int first = findFirst(nums, target);
        int last = findLast(nums, target);
        return { first, last };
    }
    int search(vector<int>& nums, int target) {
        int lo = 0, hi = (int)nums.size() - 1;

        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;

            if (nums[mid] == target) return mid;

            // левая половина [lo..mid] отсортирована?
            if (nums[lo] <= nums[mid]) {
                // target в отсортированной левой половине?
                if (nums[lo] <= target && target < nums[mid]) {
                    hi = mid - 1;   // искать слева
                }
                else {
                    lo = mid + 1;   // искать справа
                }
            }
            // иначе отсортирована правая половина [mid..hi]
            else {
                // target в отсортированной правой половине?
                if (nums[mid] < target && target <= nums[hi]) {
                    lo = mid + 1;   // искать справа
                }
                else {
                    hi = mid - 1;   // искать слева
                }
            }
        }
        return -1;
    }
    int removeElement(vector<int>& nums, int val) {
        int write = 0;

        for (int read = 0; read < (int)nums.size(); ++read) {
            if (nums[read] != val) {
                nums[write] = nums[read];
                ++write;
            }
        }
        return write;
    }
    int removeDuplicates(vector<int>& nums) {
        if (nums.empty()) return 0;

        int write = 1;   // позиция для следующего уникального

        for (int read = 1; read < (int)nums.size(); ++read) {
            if (nums[read] != nums[write - 1]) {
                nums[write] = nums[read];
                ++write;
            }
        }
        return write;
    }
    vector<int> twoSum(vector<int>& nums, int target) {
        int n = nums.size();

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (nums[i] + nums[j] == target) {
                    return { i, j };
                }
            }
        }

        return {};
    }
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        vector<vector<int>> result;

        for (int a = 0; a < n - 3; ++a) {
            // пропускаем дубликаты для a
            if (a > 0 && nums[a] == nums[a - 1]) continue;

            for (int b = a + 1; b < n - 2; ++b) {
                // пропускаем дубликаты для b
                if (b > a + 1 && nums[b] == nums[b - 1]) continue;

                int c = b + 1;
                int d = n - 1;

                // теперь классический 2Sum: nums[c] + nums[d] == target - nums[a] - nums[b]
                while (c < d) {
                    long long sum = (long long)nums[a] + nums[b] + nums[c] + nums[d];

                    if (sum == target) {
                        result.push_back({ nums[a], nums[b], nums[c], nums[d] });

                        // пропускаем дубликаты для c и d
                        while (c < d && nums[c] == nums[c + 1]) ++c;
                        while (c < d && nums[d] == nums[d - 1]) --d;

                        ++c;
                        --d;
                    }
                    else if (sum < target) {
                        ++c;
                    }
                    else {
                        --d;
                    }
                }
            }
        }
        return result;
    }
    vector<string> letterCombinations(string digits) {
        if (digits.empty()) return {};

        vector<string> table = {"", "", "abc", "def", "ghi", "jkl","mno", "pqrs", "tuv", "wxyz"};

        vector<string> result;
        string current;
        backtrack(digits, 0, table, current, result);
        return result;
    }
    int threeSumClosest(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        int best = nums[0] + nums[1] + nums[2];
        for (int i = 0; i < n - 2; ++i) {
            int l = i + 1, r = n - 1;

            while (l < r) {
                int sum = nums[i] + nums[l] + nums[r];

                if (abs(sum - target) < abs(best - target))
                    best = sum;

                if (sum == target)
                    return sum;
                if (sum < target)
                    ++l;
                else
                    --r;
            }
        }
        return best;
    }
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> result;
        sort(nums.begin(), nums.end());
        int n = nums.size();

        for (int i = 0; i < n - 2; ++i) {
            if (i > 0 && nums[i] == nums[i - 1]) continue;

            if (nums[i] > 0) break;

            int l = i + 1, r = n - 1;
            int target = -nums[i];

            while (l < r) {
                int sum = nums[l] + nums[r];

                if (sum == target) {
                    result.push_back({ nums[i], nums[l], nums[r] });

                    while (l < r && nums[l] == nums[l + 1]) ++l;
                    while (l < r && nums[r] == nums[r - 1]) --r;

                    ++l;
                    --r;
                }
                else if (sum < target) {
                    ++l;
                }
                else {
                    --r;
                }
            }
        }
        return result;
    }
    string longestCommonPrefix(vector<string>& strs) {
        if (strs.empty()) return "";
        string prefix = strs[0];

        for (int i = 1; i < (int)strs.size(); ++i) {
            // укорачиваем prefix, пока он не станет префиксом strs[i]
            while (strs[i].find(prefix) != 0) {
                prefix.pop_back();
                if (prefix.empty()) return "";
            }
        }
        return prefix;
    }
    int romanToInt(string s) {
        int values[128] = {};
        values['I'] = 1;
        values['V'] = 5;
        values['X'] = 10;
        values['L'] = 50;
        values['C'] = 100;
        values['D'] = 500;
        values['M'] = 1000;

        int sum = 0;
        for (int i = 0; i < (int)s.size(); ++i) {
            int cur = values[(unsigned char)s[i]];
            int next = (i + 1 < (int)s.size()) ? values[(unsigned char)s[i + 1]] : 0;

            if (cur < next)
                sum -= cur;
            else
                sum += cur;
        }
        return sum;
    }
    string intToRoman(int num) {
        const pair<int, string> table[] = {
            {1000, "M"},  {900, "CM"}, {500, "D"},  {400, "CD"},
            {100,  "C"},  {90,  "XC"}, {50,  "L"},  {40,  "XL"},
            {10,   "X"},  {9,   "IX"}, {5,   "V"},  {4,   "IV"},
            {1,    "I"}
        };
        string result = string();
        for (const auto& [value, symbol] : table) {
            while (num >= value) {
                result += symbol;
                num -= value;
            }
        }
        return result;
    }
    bool isPalindrome(int x) {
        if (x < 0 || (x % 10 == 0 && x != 0)) return false;

        int reversedHalf = 0;
        while (x > reversedHalf) {
            reversedHalf = reversedHalf * 10 + x % 10;
            x /= 10;
        }

        return x == reversedHalf || x == reversedHalf / 10;
    }
    string longestPalindrome(string s) {
        if (s.empty()) return "";
        int start = 0, maxLen = 1;

        for (int i = 0; i < (int)s.size(); ++i) {
            int len1 = expand(s, i, i);
            int len2 = expand(s, i, i + 1);
            int len = max(len1, len2);

            if (len > maxLen) {
                maxLen = len;
                start = i - (len - 1) / 2;
            }
        }
        return s.substr(start, maxLen);
    }
};

int main(void) {
    Solution solution = Solution();

    int n, k;
    cin >> n >> k;

    vector<int> nums(n);
    for (int i = 0;i < n;i++) cin >> nums[i];

    deque<int> dq;
    for (int i = 0;i < n;i++) {
        while (!dq.empty() && nums[dq.back()] >= nums[i]) dq.pop_back();
        dq.push_back(i);

        if (dq.front() <= i - k) dq.pop_front();

        if (i >= k - 1) cout << nums[dq.front()] << endl;
    }
    

   

    return 0;
}