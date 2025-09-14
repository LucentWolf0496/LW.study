// 数字谜
#include <iostream>
using namespace std;

int main()
{
    int C = 0, E = 0, G = 0, I = 0, N = 0, Q = 0, R = 0, T = 1, V = 0;
    for (C = 2 ; C <= 9 ; C ++){
        for (E = 0 ; E <= 9 ; E ++){
        if (E == 1 || E == C) continue;
            for (G = 0 ; G <= 9 ; G ++){
            if (G == 1 || G == E || G == C) continue;
                for (I = 0 ; I <= 9 ; I ++){
                if (I == 1 || I == G || I == E | I == C) continue;
                    for (N = 0 ; N <= 9 ; N ++){
                    if (N == 1 || N == I || N == G || N == E || N == C) continue;
                        for (Q = 0 ; Q <= 9 ; Q ++){
                        if (Q == 1 || Q == N || Q == I || Q == G || Q == E || Q == C) continue;
                            for (R = 0 ; R <= 9 ; R ++){
                            if (R == 1 || R == Q || R == N || R == I || R == G || R == E || R == C) continue;
                                for (V = 8 ; V <= 9 ; V ++){
                                if (V == 1 || V == R || V == Q || V == N || V == I || V == G || V == E || V == C) continue;
                                {
                                    int a = 10000 * V + 1000 * I + 100 * N + 10 * G + T;
                                    int b = 1000 * C + 100 * I + 10 * N + Q;
                                    int c = 100000 * T + 10000 * R + 1000 * E + 100 * N + 10 * T + E;
                                    if (a + 2 * b == c)
                                    {
                                        cout 
                                        << "C" << ":" << C << " " 
                                        << "E" << ":" << E << " " 
                                        << "G" << ":" << G << " " 
                                        << "I" << ":" << I << " " 
                                        << "N" << ":" << N << " " 
                                        << "Q" << ":" << Q << " " 
                                        << "R" << ":" << R << " " 
                                        << "T" << ":" << T << " " 
                                        << "V" << ":" << V << endl;
                                    }
                                }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}