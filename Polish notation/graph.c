#include "graph.h"

#include "polish_calc.h"
#include "polish_parser.h"

void draw_graph(char *str);
void free_func(char *str1, char *str2);

int main() {
    int error = 1, exit = 1;
    while (exit && error) {
        char *input_str = (char *)malloc(sizeof(char) * 1000);
        fgets(input_str, 1000, stdin);
        char *output_string = polish_notation(input_str, &error, &exit);
        if (error == 0) {
            printf("n/a\n");
        } else {
            if (exit != 0) {
                printf("%s\n", output_string);
                draw_graph(output_string);
            }
        }
        free_func(input_str, output_string);
    }
    return 0;
}

void free_func(char *str1, char *str2) {
    if (str1 != NULL) free(str1);
    if (str2 != NULL) free(str2);
}

void draw_graph(char *str) {
    for (int y = -12; y <= 12; y++) {
        for (double x = 0; x <= 4 * M_PI; x += 4 * M_PI / 80) {
            double fun_x = polish_calc(str, x);

            if (y == round(fun_x * 12))
                printf("*");
            else
                printf(".");
        }
        printf("\n");
    }
}
