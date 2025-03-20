#include "LinkedList.h"

// 노드 생성
Node* SLL_CreateNode(ElementType NewData){
    Node* NewNode = (Node*)malloc(sizeof(Node));

    NewNode->Data = NewData;
    NewNode->NextNode = NULL;

    return NewNode;
}

// 노드 소멸
void  SLL_DestroyNode(Node* Node){
    free(Node);
}

// 노드 추가
void  SLL_AppendNode(Node** Head, Node* NewNode){
    if(*Head == NULL){
        (*Head)=NewNode;
    }
    else{
        Node* Tail = (*Head);

        while(Tail->NextNode!=NULL){
            Tail = Tail->NextNode;
        }

        Tail->NextNode = NewNode;
    }
}

// 노드 삽입
void  SLL_InsertAfter(Node* Current, Node* NewNode){
    NewNode->NextNode = Current->NextNode;
    Current->NextNode = NewNode;
}

void  SLL_InsertNewHead(Node** Head, Node* NewHead){
    if(*Head == NULL){
        (*Head)=NewHead;
    }
    else{
        NewHead->NextNode = (*Head);
        (*Head) = NewHead;
    }
}

// 노드 삭제
void  SLL_RemoveNode(Node** Head, Node* Remove){
    if((*Head) == Remove){
        (*Head) = (*Head)->NextNode;
    }
    else{
        Node* Current = (*Head);

        while(Current != NULL && Current->NextNode != Remove){
            Current = Current->NextNode;
        }
        
        if(Current != NULL){
            Current->NextNode = Remove->NextNode;
        }
    }
}

// 노드 탐색
Node* SLL_GetNodeAt(Node* Head, int Location){
    Node* Current = Head;

    while(Current != NULL && (--Location) >= 0){
        Current = Current->NextNode;
    }

    return Current;
}

// 노드 갯수
int  SLL_GetNodeCount(Node* Head){
    int count = 0;
    Node* Current = Head;

    while(Current != NULL){
        count++;
        Current = Current->NextNode;
    }

    return count;
}

#include "LinkedList.h"

int main( void )
{
    int   i       = 0;
    int   Count   = 0;
    Node* List    = NULL;
    Node* Current = NULL;
    Node* NewNode = NULL;

    //  노드 5개 추가 
    for ( i = 0; i<5; i++ )
    {
        NewNode = SLL_CreateNode(i);
        SLL_AppendNode(&List, NewNode);
    }

    NewNode = SLL_CreateNode(-1);
    SLL_InsertNewHead(&List, NewNode);

    NewNode = SLL_CreateNode(-2);
    SLL_InsertNewHead(&List, NewNode);

    //  리스트 출력 
    Count = SLL_GetNodeCount(List);
    for ( i = 0; i<Count; i++ )
    {
        Current = SLL_GetNodeAt(List, i);
        printf("List[%d] : %d\n", i, Current->Data);
    }

    //  리스트의 세번째 노드 뒤에 새 노드 삽입 
    printf("\nInserting 3000 After [2]...\n\n");

    Current = SLL_GetNodeAt(List, 2);
    NewNode  = SLL_CreateNode(3000);

    SLL_InsertAfter(Current, NewNode);

    //  리스트 출력 
    Count = SLL_GetNodeCount(List);
    for ( i = 0; i<Count; i++ )
    {
        Current = SLL_GetNodeAt(List, i);
        printf("List[%d] : %d\n", i, Current->Data);
    }

    //  모든 노드를 메모리에서 제거     
    printf("\nDestroying List...\n");

    for ( i = 0; i<Count; i++ )
    {
        Current = SLL_GetNodeAt(List, 0);

        if ( Current != NULL ) 
        {
            SLL_RemoveNode(&List, Current);
            SLL_DestroyNode(Current);
        }
    }

    return 0;
}
