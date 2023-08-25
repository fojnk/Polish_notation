#include "polish_calc.h"

#include <math.h>

#include "polish_parser.h"

double polish_calc(char arr[1000], double x) {
    double arr_numbers[1000];

    int current_symbol = 0;
    int current_number = 0;

    while (arr[current_symbol] != '\0') {
        if ((my_is_digit(arr[current_symbol])) || arr[current_symbol] == '~') {
            char number[100];
            int sign = 1;
            if (arr[current_symbol] == '~') {
                sign = -1;
                current_symbol++;
            }
            if (arr[current_symbol] == 'x') {
                arr_numbers[current_number] = sign * x;
                current_number++;
                current_symbol++;
                continue;
            }
            for (int digit_count = 0; arr[current_symbol] != ' '; current_symbol++, digit_count++)
                number[digit_count] = arr[current_symbol];

            arr_numbers[current_number] = sign * atof(number);
            current_number++;
        }

        if (arr[current_symbol] == 'x') {
            arr_numbers[current_number] = x;
            current_number++;
        }
        char c = arr[current_symbol];
        if (c == '*' || c == '+' || c == '-' || c == '/') {
            arr_numbers[current_number - 2] =
                bin_op_calc(c, arr_numbers[current_number - 2], arr_numbers[current_number - 1]);
            current_number--;
        } else if (c == 'L' || c == 'Q' || c == 'C' || c == 'S' || c == 'T' || c == 'G') {
            arr_numbers[current_number - 1] = unar_op_calc(c, arr_numbers[current_number - 1]);
        }

        current_symbol++;
    }

    return arr_numbers[0];
}

double bin_op_calc(char op, double fst, double scd) {
    double answer = 0;
    if (op == '+') {
        answer = fst + scd;
    } else if (op == '-') {
        answer = fst - scd;
    } else if (op == '/') {
        answer = fst / scd;
    } else if (op == '*') {
        answer = fst * scd;
    }
    return answer;
}

double unar_op_calc(char op, double x) {
    double answer = 0;
    if (op == 'L') {
        answer = log(x);
    } else if (op == 'S') {
        answer = sin(x);
    } else if (op == 'C') {
        answer = cos(x);
    } else if (op == 'G') {
        answer = 1.0 / tan(x);
    } else if (op == 'Q') {
        answer = sqrt(x);
    } else if (op == 'T') {
        answer = tan(x);
    }
    return answer;
}