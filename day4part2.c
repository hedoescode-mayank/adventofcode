#include <stdio.h>
#include <string.h>

#define MAX_ROWS 3000
#define MAX_COLS 3000

// grid ko static/global rakhenge taaki stack overflow na ho
static char grid[MAX_ROWS][MAX_COLS + 1];
static char to_remove[MAX_ROWS][MAX_COLS];  // 0/1 flags

int main(void) {
    FILE *fp = fopen("input.txt", "r");
    if (!fp) {
        perror("Error opening input.txt");
        return 1;
    }

    int rows = 0;
    int cols = -1;

    // --- Read all lines into grid[] ---
    while (rows < MAX_ROWS && fgets(grid[rows], sizeof(grid[rows]), fp)) {
        size_t len = strcspn(grid[rows], "\r\n");
        grid[rows][len] = '\0';

        if (cols == -1) {
            cols = (int)len;            // length of first line
        }
        rows++;
    }
    fclose(fp);

    if (rows == 0 || cols <= 0) {
        printf("No grid data found.\n");
        return 0;
    }

    long long total_removed = 0;

    // Directions for 8 neighbors
    int dr[8] = {-1, -1, -1,  0, 0, 1, 1, 1};
    int dc[8] = {-1,  0,  1, -1, 1,-1, 0, 1};

    while (1) {
        // Clear to_remove flags
        for (int r = 0; r < rows; r++) {
            memset(to_remove[r], 0, cols * sizeof(char));
        }

        long long remove_this_round = 0;

        // 1) Mark all accessible rolls in current grid
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                if (grid[r][c] != '@') continue;

                int neigh = 0;
                for (int k = 0; k < 8; k++) {
                    int nr = r + dr[k];
                    int nc = c + dc[k];
                    if (nr < 0 || nr >= rows || nc < 0 || nc >= cols)
                        continue;
                    if (grid[nr][nc] == '@')
                        neigh++;
                }

                if (neigh < 4) {
                    to_remove[r][c] = 1;
                    remove_this_round++;
                }
            }
        }

        // 2) If this round me kuch bhi nahi remove hona, stop
        if (remove_this_round == 0) {
            break;
        }

        // 3) Remove all marked rolls from grid
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                if (to_remove[r][c]) {
                    grid[r][c] = '.'; // remove roll
                }
            }
        }

        total_removed += remove_this_round;
    }

    printf("Total rolls of paper removed: %lld\n", total_removed);
    return 0;
}
