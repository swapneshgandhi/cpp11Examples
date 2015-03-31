#include <stdio.h>

int main() { 
    char *input = "XYZ ::[1][20 BB EC 45 40 C8 97 20 84 8B 10]";

    char second_string[64];
    sscanf(input, "%*[^[][%*[^]]][%[^]]]", second_string);

    printf("content: %s\n", second_string);
    return 0;
}
