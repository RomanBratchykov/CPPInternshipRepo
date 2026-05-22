#pragma once
#include <string.h>
#include <stdlib.h>
#define IN
#define OUT
#define INOUT
namespace ISXCStringList {
    //Initializes empty array
    void ListInit(OUT char*** list)
    {
        *list = (char**)malloc(sizeof(char*));
        (*list)[0] = NULL;
    }
    //Frees memory of array and set pointer to NULL
    void ListFree(OUT char*** list)
    {
        if (list == NULL || *list == NULL)
        {
            return;
        }
        for (int i = 0; (*list)[i] != NULL; i++)
        {
            free((*list)[i]);
        }
        free(*list);
        *list = NULL;
    }
    //Gets size of array
    int GetSize(IN char** list)
    {
        if (list == NULL)
        {
            return 0;
        }
        int size = 0;
        for (int i = 0; list[i] != NULL; i++)
        {
            size++;
        }
        return size;
    }
    //Adds string element to the end of array
    void AddString(INOUT char*** list, IN const char* text)
    {
        if (list == NULL || *list == NULL)
        {
            return;
        }
        if (text == NULL)
        {
            return;
        }
        int size = GetSize(*list);
        *list = (char**)realloc(*list, (size + 2) * sizeof(char*));
        const int text_length = strlen(text);
        (*list)[size] = (char*)malloc((text_length + 1) * sizeof(char));
        strcpy((*list)[size], text);
        (*list)[size + 1] = NULL;
    }
    //Removes string from index
    void RemoveString(INOUT char*** list, IN const int index)
    {
        if (list == NULL || *list == NULL)
        {
            return;
        }
        if (index < 0 || index >= GetSize(*list))
        {
            return;
        }
        const int size = GetSize(*list);
        free((*list)[index]);
        for (int i = index; i < size; i++)
        {
            (*list)[i] = (*list)[i + 1];
        }
        *list = (char**)realloc(*list, size * sizeof(char*));
    }
    //Finds string with identical text and return index
    int FindString(IN char** list, IN const char* text)
    {
        if (list == NULL)
        {
            return -1;
        }
        if (text == NULL)
        {
            return -1;
        }
        for (int i = 0; list[i] != NULL; i++)
        {
            if (strcmp(list[i], text) == 0)
            {
                return i;
            }
        }
        return -1;
    }
    //Comparer for qsort(Quicksort algorythm) function(Ascending)
    int CompareStringAsc(IN const void* word1, IN const void* word2)
    {
        if (word1 == NULL || word2 == NULL)
        {
            return 0;
        }
        const char* word1Pointer = *(const char**)word1;
        const char* word2Pointer = *(const char**)word2;
        return strcmp(word1Pointer, word2Pointer);
    }
    //Comparer for qsort(Quicksort algorythm) function(Descending)
    int CompareStringDesc(IN const void* word1, IN const void* word2)
    {
        if (word1 == NULL || word2 == NULL)
        {
            return 0;
        }
        const char* word1Pointer = *(const char**)word1;
        const char* word2Pointer = *(const char**)word2;
        return strcmp(word2Pointer, word1Pointer);
    }
    //Sorts array ascending by alphabet
    void SortStringAscending(INOUT char*** list)
    {
        if (list == NULL || *list == NULL)
        {
            return;
        }
        if (const int size = GetSize(*list); size >= 2)
        {
            qsort(*list, size, sizeof(char*), CompareStringAsc);
        }
    }
    //Sorts array descending by alphabet
    void SortStringDescending(INOUT char*** list)
    {
        if (list == NULL || *list == NULL)
        {
            return;
        }
        if (const int size = GetSize(*list);size >= 2)
        {
            qsort(*list, size, sizeof(char*), CompareStringDesc);
        }
    }
    //Removes duplicates from array and leave only unique items
    void RemoveDuplicates(INOUT char*** list)
    {
        if (list == NULL || *list == NULL)
        {
            return;
        }
        int write_index = 0;
        const int size = GetSize((*list));
        for (int read_index = 0; read_index < size; read_index++)
        {
            int is_duplicate = 0;
            for (int k = 0; k < write_index; k++) {
                if (strcmp((*list)[k], (*list)[read_index]) == 0)
                {
                    is_duplicate = 1;
                    break;
                }
            }
            if (is_duplicate)
            {
                free((*list)[read_index]);
            }
            else
            {
                (*list)[write_index] = (*list)[read_index];
                write_index++;
            }
        }
        (*list)[write_index] = NULL;
        *list = (char**)realloc(*list, (write_index + 1) * sizeof(char*));
    }
    //Replaces previous text in item by index with yours text
    void ReplaceTextInItem(INOUT char*** list, IN const int index, IN const char* text)
    {
        if (list == NULL || *list == NULL)
        {
            return;
        }
        if (text == NULL)
        {
            return;
        }
        if (index < 0 || index >= GetSize(*list))
        {
            return;
        }
        free((*list)[index]);
        const int text_length = strlen(text);
        (*list)[index] = (char*)malloc((text_length + 1) * sizeof(char));
        strcpy((*list)[index], text);
    }
    //Replaces previous text in item with yours text if pattern is identical to text in item
    void ReplaceTextInItemByPattern(INOUT char*** list, IN const char* pattern, IN const char* text)
    {
        if (list == NULL || *list == NULL)
        {
            return;
        }
        if (pattern == NULL)
        {
            return;
        }
        char** listCopy = *list;
        if ( const int index = FindString(listCopy, pattern);index != -1)
        {
            ReplaceTextInItem(list, index, text);
        }
    }
}