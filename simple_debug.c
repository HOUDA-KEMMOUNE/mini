#include "minishell.h"

// Simple program to debug token parsing
int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("Usage: %s '<command>'\n", argv[0]);
        return 1;
    }
    
    t_token *tokens = lexer(argv[1]);
    t_token *curr = tokens;
    
    printf("Input: %s\n", argv[1]);
    printf("Tokens:\n");
    
    int i = 0;
    while (curr)
    {
        printf("  [%d] value='%s', type=%d, quote=%d\n", 
               i++, curr->value, curr->type, curr->quote);
        curr = curr->next;
    }
    
    // Clean up
    free_token_list(tokens);
    return 0;
}
