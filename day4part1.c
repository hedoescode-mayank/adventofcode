#include <stdio.h>
#include <string.h>

#define MAX_ROWS 3000
#define MAX_COLS 3000

static char grid[MAX_ROWS][MAX_COLS + 1]; // <-- yaha static

int main(void) {
    FILE *fp = fopen("input.txt", "r");
    if (!fp) {
        perror("Error opening input.txt");
        return 1;
    }

    int rows = 0;
    int cols = -1;

    while (rows < MAX_ROWS && fgets(grid[rows], sizeof(grid[rows]), fp)) {
        size_t len = strcspn(grid[rows], "\r\n");
        grid[rows][len] = '\0';

        if (cols == -1) {
            cols = (int)len;
        }

        rows++;
    }
    fclose(fp);

    if (rows == 0 || cols <= 0) {
        printf("No grid data found.\n");
        return 0;
    }

    long long accessible_count = 0;

    int dr[8] = {-1, -1, -1,  0, 0, 1, 1, 1};
    int dc[8] = {-1,  0,  1, -1, 1,-1, 0, 1};

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (grid[r][c] != '@') continue;

            int neighbor_at = 0;

            for (int k = 0; k < 8; k++) {
                int nr = r + dr[k];
                int nc = c + dc[k];

                if (nr < 0 || nr >= rows || nc < 0 || nc >= cols)
                    continue;

                if (grid[nr][nc] == '@')
                    neighbor_at++;
            }

            if (neighbor_at < 4) {
                accessible_count++;
            }
        }
    }

    printf("Accessible rolls of paper: %lld\n", accessible_count);
    return 0;
}
