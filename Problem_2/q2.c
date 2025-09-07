#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 模擬的總次數
#define NUM_SIMULATIONS 1000000

// Elmer 的勝率
const double PROB_VS_FATHER = 0.8;   // 勝率 f
const double PROB_VS_CHAMPION = 0.3; // 勝率 c

// 模擬一局比賽，根據勝率返回是否獲勝 (1=贏, 0=輸)
int play_game(double win_probability)
{
    // 產生一個 0.0 到 1.0 之間的隨機數
    double random_val = (double)rand() / RAND_MAX;
    return random_val < win_probability;
}

// 檢查三盤比賽結果是否滿足二連勝的獲獎條件
int check_prize(int r1, int r2, int r3)
{
    if ((r1 && r2) || (r2 && r3))
    {
        return 1;
    }
    return 0;
}

int main()
{
    // 使用當前時間來初始化隨機數生成器，確保每次運行的結果不同
    srand(time(NULL));

    int fcf_prize_wins = 0;
    int cfc_prize_wins = 0;

    printf("正在進行 %d 次模擬...\n", NUM_SIMULATIONS);
    printf("對戰父親的勝率 (f): %.2f\n", PROB_VS_FATHER);
    printf("對戰冠軍的勝率 (c): %.2f\n\n", PROB_VS_CHAMPION);

    // --- 模擬情況 1: F-C-F 順序 ---
    for (int i = 0; i < NUM_SIMULATIONS; ++i)
    {
        int result1 = play_game(PROB_VS_FATHER);
        int result2 = play_game(PROB_VS_CHAMPION);
        int result3 = play_game(PROB_VS_FATHER);
        if (check_prize(result1, result2, result3))
        {
            fcf_prize_wins++;
        }
    }

    // --- 模擬情況 2: C-F-C 順序 ---
    for (int i = 0; i < NUM_SIMULATIONS; ++i)
    {
        int result1 = play_game(PROB_VS_CHAMPION);
        int result2 = play_game(PROB_VS_FATHER);
        int result3 = play_game(PROB_VS_CHAMPION);
        if (check_prize(result1, result2, result3))
        {
            cfc_prize_wins++;
        }
    }

    // --- 計算並輸出結果 ---
    double prob_fcf_simulated = (double)fcf_prize_wins / NUM_SIMULATIONS;
    double prob_cfc_simulated = (double)cfc_prize_wins / NUM_SIMULATIONS;

    // 理論值計算
    double f = PROB_VS_FATHER;
    double c = PROB_VS_CHAMPION;
    double prob_fcf_theory = f * c * (2 - f);
    double prob_cfc_theory = c * f * (2 - c);

    printf("--- 結果分析 ---\n");
    printf("順序 F-C-F:\n");
    printf("  - 理論獲獎機率: %.4f (%.2f%%)\n", prob_fcf_theory, prob_fcf_theory * 100);
    printf("  - 模擬獲獎機率: %.4f (%.2f%%)\n\n", prob_fcf_simulated, prob_fcf_simulated * 100);

    printf("順序 C-F-C:\n");
    printf("  - 理論獲獎機率: %.4f (%.2f%%)\n", prob_cfc_theory, prob_cfc_theory * 100);
    printf("  - 模擬獲獎機率: %.4f (%.2f%%)\n\n", prob_cfc_simulated, prob_cfc_simulated * 100);

    if (prob_cfc_simulated > prob_fcf_simulated)
    {
        printf("結論：模擬結果顯示，選擇 C-F-C順序的獲獎機率更高，這與我們的數學推導一致。\n");
    }
    else
    {
        printf("結論：模擬結果顯示，選擇 F-C-F順序的獲獎機率更高（這可能由於隨機波動，但理論上不應發生）。\n");
    }

    return 0;
}