#pragma once
#include <string.h>
#include <stdlib.h>

void ListInit(char*** list) {
    *list = (char**)malloc(sizeof(char*));
    (*list)[0] = NULL;
}

void AddString(char*** list) {
    if (list == NULL || *list == NULL) {
        return;
    }

}

void RemoveString(char*** list) {
    if (list == NULL || *list == NULL) {
        return;
    }
}

int GetSize(char** list) {
    if (list == NULL) {
        return 0;
    }
    return 0;
}

int FindSting(char** list, char* pattern) {
    if (list == NULL) {
        return 0;
    }
    if (pattern == NULL) {
        return 0;
    }
    return 0;
}

void SortStringAscending(char*** list) {
    if (list == NULL || *list == NULL) {
        return;
    }
}

void SortStringDescending(char*** list) {
    if (list == NULL || *list == NULL) {
        return;
    }
}

void RemoveDublicates(char*** list) {
    if (list == NULL || *list == NULL) {
        return;
    }
}

void ReplaceTextInItem(char*** list, int index) {
    if (list == NULL || *list == NULL) {
        return;
    }
    if (index < 0 || index >= GetSize(*list)) {
        return;
    }

}

void ReplaceTextInItemByPattern(char*** list, char* pattern) {
    if (list == NULL || *list == NULL) {
        return;
    }
    if (pattern == NULL) {
        return;
    }
}