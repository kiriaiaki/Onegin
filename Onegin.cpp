#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>

struct Data_Str
{
    char* Ptr_Str;
    size_t Len_Str;
};

int Strcmp_K (const Data_Str Data_1, const Data_Str Data_2);
int Strcmp_Reverse_K (const Data_Str Data_1, const Data_Str Data_2);
int Filling_Array_Struct_Based_Buffer (char* const Buffer, struct Data_Str* const Array_Struct,  const size_t Quantity_Struct);
int Filling_Buffer_Based_On_Array_Struct (char* const Buffer, const struct Data_Str* const Array_Struct, const size_t Quantity_Struct);
int Bubble_Sort_Array_Struct (struct Data_Str* const Array_Struct, const size_t Quantity_Struct, int (*Compare_Function) (const Data_Str Data_1, const Data_Str Data_2));
int Counter_Symbol_In_Str (const char* const Str, const char Symbol);
int Copying_File_In_Buffer (char** Buffer, size_t* Size_Onegin);
int Creation_Array_Struct_Based_On_Line (char** Buffer, struct Data_Str** Array_Struct, size_t* Quantity_Line_Onegin);
int Open_File_And_Array_Struct (char** Buffer, size_t* Size_Onegin, struct Data_Str** Array_Struct, size_t* Quantity_Line_Onegin);
int Print_Array_Struct_In_File (const struct Data_Str* const Array_Struct, const size_t Quantity_Struct, FILE* const File);

int main ()
{
    struct Data_Str* Array_Struct = (struct Data_Str*) malloc (2008);
    char* Buffer = (char*) malloc (2902);
    size_t Quantity_Line_Onegin = 0;
    size_t Size_Onegin = 0;

    if (Open_File_And_Array_Struct (&Buffer, &Size_Onegin, &Array_Struct, &Quantity_Line_Onegin) != 0)
    {
        return 0;
    }

    const int File_Answer = open ("Answer.txt", O_WRONLY);
    FILE* File_Answer_F = fopen ("Answer_F.txt", "w");

    Bubble_Sort_Array_Struct (Array_Struct, Quantity_Line_Onegin, Strcmp_K);
    char* Printer_Buffer_1 = (char*) calloc (Size_Onegin, sizeof (char));
    Filling_Buffer_Based_On_Array_Struct (Printer_Buffer_1, Array_Struct, Quantity_Line_Onegin);
    write (File_Answer, Printer_Buffer_1, Size_Onegin);
    write (File_Answer, "\n\n\n", 3);
    free (Printer_Buffer_1);

    Bubble_Sort_Array_Struct (Array_Struct, Quantity_Line_Onegin, Strcmp_Reverse_K);
    Print_Array_Struct_In_File (Array_Struct, Quantity_Line_Onegin, File_Answer_F);

    write (File_Answer, Buffer, Size_Onegin);
    free (Buffer);

    close (File_Answer);
    fclose (File_Answer_F);

    return 0;
}

int Counter_Symbol_In_Str (const char* const Str, const char Symbol)
{
    assert (Str != NULL);
    size_t i = 0;
    int Counter = 0;

    while (Str[i] != '\0')
    {
        if (Str[i] == Symbol)
        {
            Counter++;
        }

        i++;
    }

    return Counter;
}

int Filling_Array_Struct_Based_Buffer (char* const Buffer, struct Data_Str* const Array_Struct,  const size_t Quantity_Struct)
{
    assert (Buffer != NULL);
    assert (Array_Struct != NULL);

    char* Ptr_Last_Slash_N = Buffer;

    for (size_t i = 0; i < Quantity_Struct; i++)
    {
        char* Ptr_New_Slash_N = strchr (Ptr_Last_Slash_N, '\n');
        size_t Difference_Ptr = (size_t)((Ptr_New_Slash_N) - Ptr_Last_Slash_N + 1);

        Data_Str Data = {.Ptr_Str = Ptr_Last_Slash_N, .Len_Str = Difference_Ptr};
        Array_Struct[i] = Data;

        Ptr_Last_Slash_N = Ptr_New_Slash_N + 1;
    }

    return 0;
}

int Bubble_Sort_Array_Struct (struct Data_Str* const Array_Struct, const size_t Quantity_Struct, int (*Compare_Function) (const Data_Str Data_1, const Data_Str Data_2))
{
    assert (Array_Struct != NULL);
    assert (*Compare_Function != NULL);

    for (int n = 0; n < Quantity_Struct - 1; n++)
    {
        int Counter_Substitution = 0;

        for (size_t i = 0; i < (Quantity_Struct - 1) - n; i++)
        {
            if ((*Compare_Function) (Array_Struct[i], Array_Struct[i + 1]) > 0)
            {
                Data_Str Temporary = Array_Struct[i];
                Array_Struct[i] = Array_Struct[i + 1];
                Array_Struct[i + 1] = Temporary;
                Counter_Substitution ++;
            }
        }

        if (Counter_Substitution == 0)
        {
            return 0;
        }
    }

    return 0;
}

int Strcmp_Reverse_K (const Data_Str Data_1, const Data_Str Data_2)
{
    size_t j = Data_1.Len_Str - 1, k = Data_2.Len_Str - 1;

    for (size_t i = 0; i < Data_1.Len_Str - 1; i++)
    {
        int Offset_1 = 0;
        int Offset_2 = 0;

        while ('a' > Data_1.Ptr_Str[j] || Data_1.Ptr_Str[j] > 'z')
        {
            if ('A' <= Data_1.Ptr_Str[j] && Data_1.Ptr_Str[j] <= 'Z')
            {
                Offset_1 = 'a' - 'A';
                break;
            }

            j--;
        }
        while ('a' > Data_2.Ptr_Str[k] || Data_2.Ptr_Str[k] > 'z')
        {
            if ('A' <= Data_2.Ptr_Str[k] && Data_2.Ptr_Str[k] <= 'Z')
            {
                Offset_2 = 'a' - 'A';
                break;
            }

            k--;
        }

        const int Compare_Symbol_1 = Data_1.Ptr_Str[j] + Offset_1;
        const int Compare_Symbol_2 = Data_2.Ptr_Str[k] + Offset_2;

        const int Difference = (Compare_Symbol_1 - Compare_Symbol_2);

        if (Difference != 0)
        {
            return Difference;
        }

        j--;
        k--;
    }

    return 0;
}

int Filling_Buffer_Based_On_Array_Struct (char* const Buffer, const struct Data_Str* const Array_Struct, const size_t Quantity_Struct)
{
    assert (Buffer != NULL);
    assert (Array_Struct != NULL);

    size_t k = 0;

    for (size_t i = 0; i < Quantity_Struct; i++)
    {
        for (size_t j = 0; j < Array_Struct[i].Len_Str; j++)
        {
            Buffer[k] = Array_Struct[i].Ptr_Str[j];

            k++;
        }
    }

    return 0;
}

int Strcmp_K (const Data_Str Data_1, const Data_Str Data_2)
{
    size_t j = 0, k = 0;
    for (size_t i = 0; i < Data_1.Len_Str; i++)
    {
        int Offset_1 = 0;
        int Offset_2 = 0;

        while ('a' > Data_1.Ptr_Str[j] || Data_1.Ptr_Str[j] > 'z')
        {
            if ('A' <= Data_1.Ptr_Str[j] && Data_1.Ptr_Str[j] <= 'Z')
            {
                Offset_1 = 'a' - 'A';
                break;
            }

            j++;
        }
        while ('a' > Data_2.Ptr_Str[k] || Data_2.Ptr_Str[k] > 'z')
        {
            if ('A' <= Data_2.Ptr_Str[k] && Data_2.Ptr_Str[k] <= 'Z')
            {
                Offset_2 = 'a' - 'A';
                break;
            }

            k++;
        }

        const int Compare_Symbol_1 = Data_1.Ptr_Str[j] + Offset_1;
        const int Compare_Symbol_2 = Data_2.Ptr_Str[k] + Offset_2;

        const int Difference = (Compare_Symbol_1 - Compare_Symbol_2);

        if (Difference != 0)
        {
            return Difference;
        }

        j++;
        k++;
    }

    return 0;
}

int Copying_File_In_Buffer (char** Buffer, size_t* Size_Onegin)
{
    struct stat Data_Onegin = {};

    if (stat ("Onegin.txt", &Data_Onegin) != 0)
    {
        return -1;
    }

    *Size_Onegin = Data_Onegin.st_size;

    const int File_Onegin = open ("Onegin.txt", O_RDONLY);

    *Buffer = (char*) calloc (*Size_Onegin, sizeof (char));

    if (read (File_Onegin, *Buffer, *Size_Onegin) < *Size_Onegin)
    {
        return -1;
    }

    close (File_Onegin);

    return 0;
}

int Creation_Array_Struct_Based_On_Line (char** Buffer, struct Data_Str** Array_Struct, size_t* Quantity_Line_Onegin)
{
    *Quantity_Line_Onegin = size_t (Counter_Symbol_In_Str (*Buffer, '\n'));

    *Array_Struct = (struct Data_Str*) (calloc (*Quantity_Line_Onegin, sizeof (Data_Str)));
    Filling_Array_Struct_Based_Buffer (*Buffer, *Array_Struct, *Quantity_Line_Onegin);

    return 0;
}

int Open_File_And_Array_Struct (char** Buffer, size_t* Size_Onegin, struct Data_Str** Array_Struct, size_t* Quantity_Line_Onegin)
{
    if (Copying_File_In_Buffer (Buffer, Size_Onegin) != 0)
    {
        return -1;
    }

    Creation_Array_Struct_Based_On_Line (Buffer, Array_Struct, Quantity_Line_Onegin);

    return 0;
}

int Print_Array_Struct_In_File (const struct Data_Str* const Array_Struct, const size_t Quantity_Struct, FILE* const File)
{
    assert (Array_Struct != NULL);

    size_t k = 0;

    for (size_t i = 0; i < Quantity_Struct; i++)
    {
        for (size_t j = 0; j < Array_Struct[i].Len_Str; j++)
        {
            fputc (Array_Struct[i].Ptr_Str[j], File);

            k++;
        }
    }

    fputc ('\n', File);
    fputc ('\n', File);
    fputc ('\n', File);

    return 0;
}
