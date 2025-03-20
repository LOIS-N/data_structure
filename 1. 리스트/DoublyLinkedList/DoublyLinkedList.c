#include "DoublyLInkedList.h"

Node* DLL_CreateNode( ElementType NewData ){
    Node* NewNode = malloc(sizeof(Node));

    NewNode->Data = NewData;
    NewNode->PrevNode = NULL;
    NewNode->NextNode = NULL;

    return NewNode;
}

void  DLL_DestroyNode( Node* Node){
    free(Node);
}

void  DLL_AppendNode( Node** Head, Node* NewNode ){
    if(*Head == NULL){
        *Head = NewNode;
    }
    else{
        Node* Tail = (*Head);

        while(Tail->NextNode != NULL){
            Tail = Tail->NextNode;
        }

        Tail->NextNode = NewNode;
        NewNode->PrevNode = Tail;
    }
}

void  DLL_InsertAfter( Node* Current, Node* NewNode ){
    NewNode->NextNode = Current->NextNode;
    NewNode->PrevNode = Current;

    if(Current->NextNode != NULL){
        Current->NextNode->PrevNode = NewNode;
        Current->NextNode = NewNode;
    }
}

void  DLL_RemoveNode( Node** Head, Node* Remove ){
    if(*Head == Remove){
        *Head = Remove->NextNode;

        if(*Head != NULL){
            (*Head)->PrevNode = NULL;
        }

        Remove->NextNode = NULL;
        Remove->PrevNode = NULL;
    }
    else{
        if(Remove->PrevNode != NULL){
            Remove->PrevNode->NextNode = Remove->NextNode;
        }
        
        if(Remove->NextNode != NULL){
            Remove->NextNode->PrevNode = Remove->PrevNode;
        }

        Remove->PrevNode = NULL;
        Remove->NextNode = NULL;
    }
}

Node* DLL_GetNodeAt( Node* Head, int Location ){
    Node* Current = Head;

    while(Current != NULL && (--Location) >= 0){
        Current = Current->NextNode;
    }

    return Current;
}

int   DLL_GetNodeCount( Node* Head ){
    Node* Current = Head;
    int count = 0;

    while(Current != NULL){
        count++;
        Current = Current->NextNode;
    }

    return count;
}

int main( void )
{
    int   i       = 0;
    int   Count   = 0;
    Node* List    = NULL;
    Node* NewNode = NULL;
    Node* Current = NULL;

    printf("노드 생성\n");
    //  노드 5개 추가 
    for ( i = 0; i<5; i++ )
    {
        NewNode = DLL_CreateNode( i );
        DLL_AppendNode( &List, NewNode );
    }

    //  리스트 출력 
    Count = DLL_GetNodeCount( List );
    for ( i = 0; i<Count; i++ )
    {
        Current = DLL_GetNodeAt( List, i );
        printf( "List[%d] : %d\n", i, Current->Data );
    }

    //  리스트의 세번째 칸 뒤에 노드 삽입 
    printf( "\nInserting 3000 After [2]...\n\n" );

    Current = DLL_GetNodeAt( List, 2 );
    NewNode = DLL_CreateNode( 3000 );
    DLL_InsertAfter( Current, NewNode );

    //  리스트 출력 
    Count = DLL_GetNodeCount( List );
    for ( i = 0; i<Count; i++ )
    {
        Current = DLL_GetNodeAt( List, i );
        printf( "List[%d] : %d\n", i, Current->Data );
    }

    //  모든 노드를 메모리에서 제거     
    printf( "\nDestroying List...\n" );

    Count = DLL_GetNodeCount(List);

    for ( i = 0; i<Count; i++ )
    {
        Current = DLL_GetNodeAt( List, 0 );

        if ( Current != NULL ) 
        {
            DLL_RemoveNode( &List, Current );
            DLL_DestroyNode( Current );
        }
    }

    return 0;
}
