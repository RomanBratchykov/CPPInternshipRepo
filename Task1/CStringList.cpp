#include "CStringList.h"
#include <stdio.h>

void PrintList(IN char*** list)
{
    if (list == NULL || *list == NULL) {
        printf("List is empty.\n");
        return;
    }
    for (int i = 0; (*list)[i] != NULL; i++) {
        printf("%s\n", (*list)[i]);
    }
}
int main()
{
    char** list;
    printf("_______________\n");
    ISXCStringList::ListInit(&list);
    ISXCStringList::AddString(&list, "Hello");
    ISXCStringList::AddString(&list, "World");
    ISXCStringList::AddString(&list, "World");
    ISXCStringList::AddString(&list, "I");
    ISXCStringList::AddString(&list, "AM");
    ISXCStringList::AddString(&list, "HERE");
    ISXCStringList::AddString(&list, "Hello");
    ISXCStringList::AddString(&list, "Apple");
    printf("_______________\n");
    PrintList(&list);
    printf("_______________\n");
    ISXCStringList::SortStringAscending(&list);
    PrintList(&list);
    printf("_______________\n");
    ISXCStringList::SortStringDescending(&list);
    PrintList(&list);
    printf("_______________\n");
    ISXCStringList::RemoveString(&list, 2);
    PrintList(&list);
    printf("_______________\n");
    ISXCStringList::RemoveDuplicates(&list);
    ISXCStringList::ReplaceTextInItem(&list, 2, "New");
    PrintList(&list);
    printf("_______________\n");
    ISXCStringList::ReplaceTextInItemByPattern(&list, "AM", "ETC");
    PrintList(&list);
    printf("_______________\n");
    printf("Size: %d\n", ISXCStringList::GetSize(list));
    printf("_______________\n");
    printf("Index of word 'Hello': %d\n", ISXCStringList::FindString(list, "Hello") );
}
