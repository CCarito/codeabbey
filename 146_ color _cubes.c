#include <stdio.h>

int removeGroup(int board[][100], int N, int x, int y, int color) {
    if (x < 0 || x >= N || y < 0 || y >= N || board[x][y] != color) {
        return 0;
    }

    int count = 1;
    board[x][y] = -1;

    count += removeGroup(board, N, x - 1, y, color);
    count += removeGroup(board, N, x + 1, y, color);
    count += removeGroup(board, N, x, y - 1, color);
    count += removeGroup(board, N, x, y + 1, color);

    return count;
}

void shiftDown(int board[][100], int N, int column) {
    for (int i = N - 1; i >= 0; i--) {
        if (i == 0) {
            board[i][column] = -1;
        } else {
            board[i][column] = board[i - 1][column];
        }
    }
}

void shiftLeft(int board[][100], int N, int column) {
    for (int i = column; i < N - 1; i++) {
        for (int j = 0; j < N; j++) {
            board[j][i] = board[j][i + 1];
        }
    }

    for (int j = 0; j < N; j++) {
        board[j][N - 1] = -1;
    }
}

int calculateScore(int count) {
    return count * (count + 1) / 2;
}

int main() {
    int N;
    scanf("%d", &N);

    int board[100][100];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%1d", &board[i][j]);
        }
    }

    int K;
    scanf("%d", &K);

    int moves[100][2];
    for (int i = 0; i < K; i++) {
        scanf("%d %d", &moves[i][0], &moves[i][1]);
    }

    int score = 0;

    for (int i = 0; i < K; i++) {
        int x = moves[i][0];
        int y = moves[i][1];
        int color = board[x][y];

        if (color == -1) {
            continue;
        }

        int groupCount = removeGroup(board, N, x, y, color);

        if (groupCount > 1) {
            score += calculateScore(groupCount);
        }

        for (int j = 0; j < N; j++) {
            for (int k = N - 1; k >= 0; k--) {
                if (board[k][j] == -1) {
                    shiftDown(board, N, j);
                    break;
                }
            }
        }

        for (int j = N - 1; j >= 0; j--) {
            int emptyColumn = 1;

            for (int k = 0; k < N; k++) {
                if (board[k][j] != -1) {
                    emptyColumn = 0;
                    break;
                }
            }

            if (emptyColumn) {
                shiftLeft(board, N, j
