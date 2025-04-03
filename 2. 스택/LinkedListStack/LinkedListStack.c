#include "LinkedListStack.h"

int main( void )
{
    int i= 0;
    int Count = 0;
    Node* Popped;

    LinkedListStack* Stack;

    LLS_CreateStack(&Stack);
    
    LLS_Push( Stack, LLS_CreateNode("abc") );
    LLS_Push( Stack, LLS_CreateNode("def") );
    LLS_Push( Stack, LLS_CreateNode("efg") );
    LLS_Push( Stack, LLS_CreateNode("hij") );

    Count = LLS_GetSize(Stack);
    printf( "Size: %d, Top: %s\n\n", 
        Count, LLS_Top(Stack)->Data );

    for ( i=0; i<Count; i++ )
    {
        if ( LLS_IsEmpty(Stack) )
            break;

        Popped = LLS_Pop( Stack );

        printf( "Popped: %s, ", Popped->Data );

        LLS_DestroyNode(Popped);

        if ( ! LLS_IsEmpty(Stack) ) 
        {
            printf( "Current Top: %s\n", LLS_Top(Stack)->Data );
        }
        else
        {
            printf( "Stack Is Empty.\n");
        }
    }

    LLS_DestroyStack(Stack);

    return 0;
}

void  LLS_CreateStack( LinkedListStack** Stack ){
    (*Stack) = malloc(sizeof(LinkedListStack));
    (*Stack)->List = NULL;
    (*Stack)->Top = NULL;
}

void  LLS_DestroyStack( LinkedListStack* Stack ){
    while(!LLS_IsEmpty(Stack)){
        Node* Popped = LLS_Pop(Stack);
        LLS_DestroyNode(Popped);
    }

    free(Stack);
}

Node* LLS_CreateNode( char* NewData ){
    Node* NewNode = malloc(sizeof(Node));
    NewNode->Data = malloc(strlen(NewData) + 1); // null문자 추가하기 위한공간

    /*
    NewNode->Data = NewData할 경우 메모리 주소를 할당하므로 함수가 종료되면 NewData도 사라지므로
    값을 불러오지 못하게 된다
    */
    strcpy(NewNode->Data, NewData);

    NewNode->NextNode = NULL;

    return NewNode;
}

void  LLS_DestroyNode( Node* _Node ){
    free(_Node->Data);
    free(_Node);
}

void  LLS_Push( LinkedListStack* Stack, Node* NewNode ){
    if(Stack->List == NULL){
        Stack->List = NewNode;
    }
    else{
        Stack->Top->NextNode = NewNode;
    }

    Stack->Top = NewNode;
}

Node* LLS_Pop( LinkedListStack* Stack ){
    /*
    1. 현재 최상위 노드를 복사
    2. 최상위 노드의 이전 노드 탐색
    3. Top에 최상위 노드의 이전 노드의 주소를 등록
    4. 복사했던 최상위 노드를 반환
     */
    Node* TopNode = Stack->Top;

    if(Stack->List == Stack->Top){
        Stack->List = NULL;
        Stack->Top = NULL;
    }
    else{
        Node* Current = Stack->List;
        while(Current->NextNode != Stack->Top && Current != NULL){
            Current = Current->NextNode;
        }

        Stack->Top = Current;
        Stack->Top->NextNode = NULL;
    }

    return TopNode;
}

Node* LLS_Top( LinkedListStack* Stack ){
    return Stack->Top;
}

int   LLS_GetSize( LinkedListStack* Stack ){
    int count = 0;
    Node* Current = Stack->List;

    while(Current != NULL){
        Current = Current->NextNode;
        count++;
    }

    return count;
}

int   LLS_IsEmpty( LinkedListStack* Stack ){
    return (Stack->List == NULL);
}