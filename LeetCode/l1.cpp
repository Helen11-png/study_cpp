//3116 hard
/*
You are given an integer array coins representing coins of different denominations and an integer k.
You have an infinite number of coins of each denomination. However, you are not allowed to combine coins of different denominations.
Return the kth smallest amount that can be made using these coins.
*/

class Solution {
public:
    long long findKthSmallest(vector<int>& coins, int k) {
        sort(coins.begin(), coins.end());
        vector<int> filtered;
        for (int i = 0; i < coins.size(); i++) {
            bool isMultiple = false;
            for (int j = 0; j < i; j++) {
                if (coins[i] % coins[j] == 0) {
                    isMultiple = true;
                    break;
                }
            }
            if (!isMultiple) filtered.push_back(coins[i]);
        }
        coins = filtered;
        
        long long left = 1, right = (long long)coins[0] * k;
        
        while (left < right) {
            long long mid = left + (right - left) / 2;
            long long count = countNumbers(mid, coins);
            
            if (count >= k) {
                right = mid;  // ищем левее
            } else {
                left = mid + 1; // ищем правее
            }
        }
        
        return left;
    }
    
    long long countNumbers(long long X, vector<int>& coins) {
        long long total = 0;
        int n = coins.size();
        
        for (int mask = 1; mask < (1 << n); mask++) {
            long long lcm = 1;
            int bits = 0;
            
            for (int i = 0; i < n; i++) {
                if (mask & (1 << i)) {
                    lcm = lcm / gcd(lcm, (long long)coins[i]) * coins[i];
                    bits++;
                    if (lcm > X) break;
                }
            }
            
            if (lcm > X) continue;
            
            if (bits % 2 == 1) total += X / lcm;
            else total -= X / lcm;
        }
        
        return total;
    }
};