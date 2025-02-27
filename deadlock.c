#include <stdio.h>

int main() {
    int process[3] = {1, 2, 3};
    int res[3] = {1, 2, 3};
    int request[3] = {1, 0, 2};
    int n = 3;

    for (int i = 0; i < n; i++) {
        if (request[i] > 1) {
            printf("Deadlock happened\n");
        } else {
            const char* status = (request[i] == 1) ? "allocated to" : "not allocated to";
            printf("P%d %s R%d\n", process[i], status, res[i]);
        }
    }

    return 0;
}
