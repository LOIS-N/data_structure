#ifndef LINKEDLIST_STACK_H
#define LINKEDLIST_STACK_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct tagNode
{
    char* Data;
    struct tagNode* NextNode;
} Node;
/*
Data 필드가 char* 형태로 선언됨 -> 문자열이 저장된 메모리 주소만 저장 가능
해당 데이터는 자동 저장소에 저장될 경우 사라지므로 자유 저장소에 저장해야 함
*/

typedef struct tagLinkedListStack
{
    Node* List;
    Node* Top;
} LinkedListStack;

void  LLS_CreateStack( LinkedListStack** Stack );
void  LLS_DestroyStack( LinkedListStack* Stack );

Node* LLS_CreateNode( char* Data );
void  LLS_DestroyNode( Node* _Node );

void  LLS_Push( LinkedListStack* Stack, Node* NewNode );
Node* LLS_Pop( LinkedListStack* Stack );

Node* LLS_Top( LinkedListStack* Stack );
int   LLS_GetSize( LinkedListStack* Stack );
int   LLS_IsEmpty( LinkedListStack* Stack );

#endif
