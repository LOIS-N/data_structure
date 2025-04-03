#include "CircularDoublyLinkedList.h"

Node* CDLL_CreateNode(ElementType NewData){
    Node* NewNode = malloc(sizeof(Node));

    NewNode->Data = NewData;
    NewNode->NextNode = NULL;
    NewNode->PrevNode = NULL; 

    return NewNode;
}

void  CDLL_DestroyNode(Node* Node){
    free(Node);
}

void  CDLL_AppendNode(Node** Head, Node* NewNode){
    if(*Head == NULL){
        *Head = NewNode;
        (*Head)->NextNode = *Head;
        (*Head)->PrevNode = *Head;
    }
    else{ 
        // CDLL은 head와  tail이 연결되어있으므로 그 사이에 추가하면 됨
        NewNode->PrevNode = (*Head)->PrevNode;
        NewNode->NextNode = (*Head);

        (*Head)->PrevNode->NextNode = NewNode;
        (*Head)->PrevNode = NewNode;
    }
}

void  CDLL_InsertAfter(Node* Current, Node* NewNode){
    NewNode->NextNode = Current->NextNode;
    NewNode->PrevNode = Current;

    if(Current->NextNode != NULL){
        Current->NextNode->PrevNode = NewNode;
        Current->NextNode = NewNode;
    }
}

void  CDLL_RemoveNode(Node** Head, Node* Remove){
    if(*Head == Remove){
        (*Head)->PrevNode->NextNode = Remove->NextNode;
        (*Head)->NextNode->PrevNode = Remove->PrevNode;

        (*Head) = Remove->NextNode;

        Remove->NextNode = NULL;
        Remove->PrevNode = NULL;
    }
    else{
        Remove->NextNode->PrevNode = Remove->PrevNode;
        Remove->PrevNode->NextNode = Remove->NextNode;

        Remove->PrevNode = NULL;
        Remove->NextNode = NULL;
    }
}

Node* CDLL_GetNodeAt(Node* Head, int Location){
    Node* Current = Head;

    while(Current != NULL && (--Location)>=0){
        Current = Current->NextNode;
    }

    return Current;
}

int   CDLL_GetNodeCount(Node* Head){
    Node* Current = Head;
    int count = 0;

    while(Current != NULL){
        Current = Current->NextNode;
        count++;

        if(Current == Head){
            break;
        }
    }

    return count;
}

// int main( void )
// {
//     int   i       = 0;
//     int   Count   = 0;
//     Node* List    = NULL;
//     Node* NewNode = NULL;
//     Node* Current = NULL;

//     //  노드 5개 추가 
//     for ( i = 0; i<5; i++ )
//     {
//         NewNode = CDLL_CreateNode( i );
//         CDLL_AppendNode( &List,NewNode );
//     }

//     //  리스트 출력 
//     Count = CDLL_GetNodeCount( List );
//     for ( i = 0; i<Count; i++ )
//     {
//         Current = CDLL_GetNodeAt( List, i );
//         printf( "List[%d] : %d\n", i, Current->Data );
//     }

//     //  리스트의 세번째 칸 뒤에 노드 삽입 
//     printf( "\nInserting 3000 After [2]...\n\n" );

//     Current = CDLL_GetNodeAt( List, 2 );
//     NewNode = CDLL_CreateNode( 3000 );
//     CDLL_InsertAfter( Current, NewNode );

//     printf( "\nRemoving Node at 2...\n" );
//     Current = CDLL_GetNodeAt( List, 2 );
//     CDLL_RemoveNode( &List, Current );
//     CDLL_DestroyNode( Current );

//     //  리스트 출력  
//     //  (노드 수의 2배만큼 루프를 돌며 환형임을 확인한다.) 
//     Count = CDLL_GetNodeCount( List );
//     for ( i = 0; i<Count*2; i++ )
//     {
//         if ( i == 0 )
//             Current = List;
//         else
//             Current = Current->NextNode;
        
//         printf( "List[%d] : %d\n", i, Current->Data );
//     }

//     //  모든 노드를 메모리에서 제거     
//     printf( "\nDestroying List...\n" );

//     Count = CDLL_GetNodeCount( List );

//     for ( i = 0; i<Count; i++ )
//     {
//         Current = CDLL_GetNodeAt( List, 0 );

//         if ( Current != NULL ) 
//         {
//             CDLL_RemoveNode( &List, Current );
//             CDLL_DestroyNode( Current );
//         }
//     }

//     return 0;
// }
