
// print in main or func

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int next_field(FILE *csv, char *buffer, int max_len)
{
    char c;
    int i = 0;
    int quotes = 0;

    do
    {
        c = fgetc(csv);

        if(c == '"'){
            quotes = !quotes;//i++?
        }

        if( c == ',' && quotes){
            buffer[i] = c;
        }
        else if (c == ',')
        {
            buffer[i] = '\0';
            return 0;
        }
        else if (c == '\n')
        {
            buffer[i] = '\0';
            return 1;
        }
        
        if(c != '"'){
            buffer[i] = c;
            i++;
        }
       
        if (feof(csv))
        {
            return 2;
        }
    } while ((c != EOF) && (i < max_len));
    return 1;
}

int main(int argc, char *argv[])
{
    int maxLen = 128;
    char field[maxLen];
    int print = 0;

    FILE *csv = fopen(argv[1], "r"); //"r" means to open the file for reading.. w for writing
    if (csv == NULL)
    {
        perror("File doesnt exist");
        return 1;
    }
    else
    {

        while (1)
        {
            int i = next_field(csv, field, maxLen); 
            //could use switch case instead
            if (i == 0 && print)
            {
                printf("%s \n", field);
            }
            else if (i == 1)
            {
                if(print){
                    printf("%s\n\n", field);
                }
                print = 1;
            }
            else if (i == 2)
            {
                printf("%s \n", field);
                break;
            }
        }
    }
    return 0;
}
