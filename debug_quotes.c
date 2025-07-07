#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *test1 = "'$USER'\"$USER\"";
    char *test2 = "\"$USER\"'$USER'";
    
    printf("Testing mixed quote detection:\n");
    printf("Test 1: %s\n", test1);
    
    int has_single_quote = 0;
    int has_double_quote = 0;
    int i = 0;
    
    while (test1[i]) {
        if (test1[i] == '\'')
            has_single_quote = 1;
        else if (test1[i] == '"')
            has_double_quote = 1;
        i++;
    }
    
    printf("Has single quote: %d, Has double quote: %d\n", has_single_quote, has_double_quote);
    printf("Quote type would be: %d\n", (has_single_quote && !has_double_quote) ? '\'' : 
                                        (has_double_quote && !has_single_quote) ? '"' : 0);
    
    printf("\nTest 2: %s\n", test2);
    
    has_single_quote = 0;
    has_double_quote = 0;
    i = 0;
    
    while (test2[i]) {
        if (test2[i] == '\'')
            has_single_quote = 1;
        else if (test2[i] == '"')
            has_double_quote = 1;
        i++;
    }
    
    printf("Has single quote: %d, Has double quote: %d\n", has_single_quote, has_double_quote);
    printf("Quote type would be: %d\n", (has_single_quote && !has_double_quote) ? '\'' : 
                                        (has_double_quote && !has_single_quote) ? '"' : 0);
    
    return 0;
}
