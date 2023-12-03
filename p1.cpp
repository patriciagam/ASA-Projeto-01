#include <iostream>
#include <vector>

using namespace std;

struct Piece {
    int width;
    int height;
};

int calculatePrice(const Piece& piece, vector<vector<int>>& dp) {
    for (int i = 1; i <= piece.width; ++i) {
        for (int j = 1; j <= piece.height; ++j) {
            int maxPrice = dp[i][j];

            for (int k = 1; k <= max(i / 2, j / 2); ++k) {
                if (k <= i / 2)
                    maxPrice = max(dp[i - k][j] + dp[k][j], maxPrice);
                if (k <= j / 2)
                    maxPrice = max(dp[i][j - k] + dp[i][k], maxPrice);
            }

            dp[i][j] = maxPrice;
        }
    }
    return dp[piece.width][piece.height];
}

int main() {
    int x, y, n;
    scanf("%d %d %d", &x, &y, &n);

    Piece marbleSheet = {x, y};
    vector<vector<int>> dp(x + 1, vector<int>(y + 1, 0));

    for (int i = 0; i < n; ++i) {
        int a, b, p;
        scanf("%d %d %d", &a, &b, &p);
        if (a <= x && b <= y) 
            dp[a][b] = p;
        if (a != b && a <= y && b <= x)
            dp[b][a] = p;
    }
    int maxPrice = calculatePrice(marbleSheet, dp);
    printf("%d\n", maxPrice);

    return 0;
}
