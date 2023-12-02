#include <iostream>
#include <vector>

struct Piece {
    int width;
    int height;
};



int calculatePrice(const Piece& piece, std::vector<std::vector<int>>& prices) {
    std::vector<std::vector<int>> dp(piece.width + 1, std::vector<int>(piece.height + 1, 0));

    for (int i = 1; i <= piece.width; ++i) {
        for (int j = 1; j <= piece.height; ++j) {
            int maxPrice = prices[i][j];

            for (int k = 1; k <= i / 2; ++k) {
                maxPrice = std::max(dp[i - k][j] + dp[k][j], maxPrice);
            }
            for (int k = 1; k <= j / 2; ++k) {
                maxPrice = std::max(dp[i][j - k] + dp[i][k], maxPrice);
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
    std::vector<std::vector<int>> prices(x + 1, std::vector<int>(y + 1, 0));

    for (int i = 0; i < n; ++i) {
        int a, b, p;
        scanf("%d %d %d", &a, &b, &p);
        if (a <= x && b <= y) 
            prices[a][b] = p;
        if (a != b && a <= y && b <= x)
            prices[b][a] = p;
    }
    int maxPrice = calculatePrice(marbleSheet, prices);
    printf("%d\n", maxPrice);

    return 0;
}
