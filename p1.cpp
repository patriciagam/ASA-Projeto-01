#include <iostream>
#include <vector>
#include <algorithm> 

struct Piece {
    int width;
    int height;
    int price;
};

bool comparePricePerArea(const Piece& a, const Piece& b) {
    return (a.price / (a.width * a.height)) > (b.price / (b.width * b.height));
}

int calculatePrice(Piece& marbleSheet, std::vector<Piece>& pieces, int i) {
    int size = pieces.size();
    if (i >= size || marbleSheet.width == 0 || marbleSheet.height == 0) {
        return 0;
    }

    if (marbleSheet.width >= pieces[i].width && marbleSheet.height >= pieces[i].height) {
        int piecesAlongWidth =  marbleSheet.width / pieces[i].width;
        int piecesAlongHeight = marbleSheet.height / pieces[i].height;
        int pieceCount = piecesAlongWidth * piecesAlongHeight;
            
        marbleSheet.width -= pieces[i].width * piecesAlongWidth;
        marbleSheet.height -= pieces[i].height * piecesAlongHeight;
        marbleSheet.price += pieces[i].price * pieceCount;
    }

    return marbleSheet.price + calculatePrice(marbleSheet, pieces, i + 1);
}

int main() {
    int x, y, n;
    std::cin >> x >> y >> n;

    Piece marbleSheet = {x, y, 0};
    std::vector<Piece> pieces;

    for (int i = 0; i < n; ++i) {
        int a, b, p;
        std::cin >> a >> b >> p;
        if (a <= marbleSheet.width && b <= marbleSheet.height) {
            Piece piece = {a, b, p};
            pieces.push_back(piece);
        }
        if (a <= marbleSheet.height && b <= marbleSheet.width && a != b) {
            Piece piece = {b, a, p};
            pieces.push_back(piece);
        }
    }

    std::sort(pieces.begin(), pieces.end(), comparePricePerArea);

    marbleSheet.price = calculatePrice(marbleSheet, pieces, 0);

    std::cout << marbleSheet.price << std::endl;

    return 0;
}