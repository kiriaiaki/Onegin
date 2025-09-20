#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

struct Data_Str
{
    char* Ptr_Str;
    size_t Len_Str;
};

int Strcmp_K (const char* const Str_1, const char* const Str_2);
int Changed_Str (char* const Changeable_Str, const char* const Str);

int main ()
{
    size_t Size_Mini_Onegin = 851;
    size_t N_Str_Mini_Onegin = 28;

    int Mini_Onegin = open ("Mini_Onegin.txt", O_RDONLY);

    char* Buffer = (char*) calloc (Size_Mini_Onegin, sizeof (char));
    int k = read (Mini_Onegin, Buffer, Size_Mini_Onegin);

    struct Data_Str* Array_Struct = (struct Data_Str*) (calloc (N_Str_Mini_Onegin, sizeof (Data_Str)));

    char* Ptr_Last_Slash_N = Buffer;
    for (size_t i = 0; i < N_Str_Mini_Onegin + 1; i++)
    {
        char* Ptr_New_Slash_N = strchr (Ptr_Last_Slash_N, '\n');
        size_t k_2 = (size_t)((Ptr_New_Slash_N) - Ptr_Last_Slash_N + 1);

        Data_Str Data = {.Ptr_Str = Ptr_Last_Slash_N, .Len_Str = k_2};
        Array_Struct[i] = Data;

        Ptr_Last_Slash_N = Ptr_New_Slash_N + 1;
    }

    for (int n = 0; n < N_Str_Mini_Onegin - 1; n++)
    {
        for (size_t i = 0; i < (N_Str_Mini_Onegin -  1) - n; i++)
        {
            char* Str_1 = (char*) calloc(Array_Struct[i].Len_Str + 1, sizeof(char));
            char* Str_2 = (char*) calloc(Array_Struct[i+1].Len_Str + 1, sizeof(char));

            for (size_t j = 0; j < Array_Struct[i].Len_Str; j++)
            {
                Str_1[j] = (Array_Struct[i].Ptr_Str[j]);
            }

            for (size_t j = 0; j < Array_Struct[i+1].Len_Str; j++)
            {

                Str_2[j] = (Array_Struct[i+1].Ptr_Str[j]);
            }

            if (Strcmp_K (Str_1, Str_2) > 0)
            {
                Data_Str Temporary = Array_Struct[i];
                Array_Struct[i] = Array_Struct[i + 1];
                Array_Struct[i + 1] = Temporary;
            }

            free (Str_1);
            free (Str_2);
        }
    }

    for (size_t i = 0; i < N_Str_Mini_Onegin; i++)
    {
        for (size_t j = 0; j < Array_Struct[i].Len_Str; j++)
        {
            putchar (Array_Struct[i].Ptr_Str[j]);
        }
    }

    printf ("\n\n%s", Buffer);
    close (Mini_Onegin);
    free (Buffer);
    return 0;
 }

int Changed_Str (char* const Changeable_Str, const char* const Str)
{
    assert (Str != NULL);
    assert (Changeable_Str != NULL);

    const size_t Len_Str = strlen (Str);
    size_t Changeable_Str_Index = 0;

    for (size_t i = 0; i < Len_Str + 1; i++)
    {
        if ('A' <= Str[i] && Str[i] <= 'Z')
        {
            Changeable_Str[Changeable_Str_Index] = Str[i] + ('a' - 'A');
            Changeable_Str_Index++;
        }

        if ('a' <= Str[i] && Str[i] <= 'z')
        {
            Changeable_Str[Changeable_Str_Index] = Str[i];
            Changeable_Str_Index++;
        }
    }

    Changeable_Str[Changeable_Str_Index + 1] = '\0';

    return 0;
}

int Strcmp_K (const char* const Str_1, const char* const Str_2)
{
    assert (Str_1 != NULL);
    assert (Str_2 != NULL);

    const size_t Len_Str_1 = strlen (Str_1);
    const size_t Len_Str_2 = strlen (Str_2);

    char* Changeable_Str_1 = (char*) calloc(Len_Str_1 + 1, sizeof(char));
    char* Changeable_Str_2 = (char*) calloc(Len_Str_2 + 1, sizeof(char));

    Changed_Str (Changeable_Str_1, Str_1);
    Changed_Str (Changeable_Str_2, Str_2);

    const size_t Len_Str = strlen (Changeable_Str_1);


    for (size_t i = 0; i < Len_Str + 1; i++)
    {
        int Difference = (Changeable_Str_1[i] - Changeable_Str_2[i]);

        if (Difference != 0)
        {
            return Difference;
        }
    }

    return 0;
}
