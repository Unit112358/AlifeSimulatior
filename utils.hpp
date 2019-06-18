#pragma once

#include <stdlib.h>
#include "alife.hpp"


#define LOWINT64(a) (int32)((a)&0xffffffff)
#define HIGHINT64(a) (int32)(((a)&0xffffffff00000000)>>32)

#define vec_x(a) HIGHINT64(a)
#define vec_y(a) LOWINT64(a)

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480


// typedef struct _AlifeList
// {
//     Alife **data;
//     uint len;
//     uint cap;
// }AlifeList;

// AlifeList* new_AlifeList()
// {
//     AlifeList *p = (AlifeList*)malloc(sizeof(AlifeList));
//     p->len = 0;
//     p->cap = 4;
//     p->data = (Alife**)malloc(sizeof(Alife*) * p->cap);
// }

// AlifeList* AlifeList_append(AlifeList* list, Alife *p)
// {
//     list->data[list->len++] = p;
//     if(list->len == list->cap)
//     {
//         list->cap *= 2;
//         list->data = (Alife**)realloc(list->data, sizeof(Alife*) * list->cap);
//     }
//     return list;
// }