#include <iostream>
#include <vector>

struct Piece {
    int width;
    int height;
};

int calculatePrice(const Piece& piece, const std::vector<int>& prices) {
    std::vector<int> dp((piece.width + 1) * (piece.height + 1), 0);

    for (int i = 1; i <= piece.width; ++i) {
        for (int j = 1; j <= piece.height; ++j) {
            int maxPrice = prices[i * (piece.height + 1) + j];

            for (int k = 1; k <= i / 2; ++k) {
                maxPrice = std::max(maxPrice, dp[(i - k) * (piece.height + 1) + j] + dp[k * (piece.height + 1) + j]);
            }

            for (int k = 1; k <= j / 2; ++k) {
                maxPrice = std::max(maxPrice, dp[i * (piece.height + 1) + (j - k)] + dp[i * (piece.height + 1) + k]);
            }

            dp[i * (piece.height + 1) + j] = maxPrice;
        }
    }

    return dp[piece.width * (piece.height + 1) + piece.height];
}



int main() {
    int x, y, n;
    std::cin >> x >> y >> n;

    Piece marbleSheet = {x, y};
    std::vector<int> prices((x + 1) * (y + 1), 0);

    for (int i = 0; i < n; ++i) {
        int a, b, p;
        std::cin >> a >> b >> p;
        if (a <= x && b <= y) 
            prices[a * (y + 1) + b] = p;
        if (a != b && a <= y && b <= x)
            prices[b * (y + 1) + a] = p;
    }

    int maxPrice = calculatePrice(marbleSheet, prices);
    std::cout << maxPrice << std::endl;

    return 0;
}
