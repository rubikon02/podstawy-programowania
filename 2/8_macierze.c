#include <stdio.h>

void mPrint(double m[3][3]) {
    for(int x = 0; x < 3; x++) {
        for(int y = 0; y < 3; y++) {
            printf("%f ", m[x][y]);
        }
        printf("\n");
    }
}

void mSet(double m[3][3], double value) {
    for(int x = 0; x < 3; x++) {
        for(int y = 0; y < 3; y++) {
            m[x][y] = value;
        }
    }
}

int main() {
    double m1[3][3] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    double m2[3][3] = {11, 12, 13, 14, 15, 16, 17, 18, 19};
    double m3[3][3];

    for(int x = 0; x < 3; x++) {
        for(int y = 0; y < 3; y++) {
            m3[x][y] = m1[x][y] + m2[x][y];
        }
    }

    mPrint(m3);

    mSet(m3, 0);

    for(int x = 0; x < 3; x++) {
        for(int y = 0; y < 3; y++) {
            for (int i = 0; i < 3; i++) {
                m3[x][y] += m1[x][i] * m2[i][y];
            }
        }
    }

    mPrint(m3);
}