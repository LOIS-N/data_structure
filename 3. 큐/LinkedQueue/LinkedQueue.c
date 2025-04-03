#include "LinkedQueue.h"

int main( void )
{
    Node* Popped;
    LinkedQueue* Queue;

    LQ_CreateQueue(&Queue );
    
    LQ_Enqueue( Queue, LQ_CreateNode("abc") );
    LQ_Enqueue( Queue, LQ_CreateNode("def") );
    LQ_Enqueue( Queue, LQ_CreateNode("efg") );
    LQ_Enqueue( Queue, LQ_CreateNode("hij") );

    printf("Queue Size : %d\n", Queue->Count);

    while ( LQ_IsEmpty( Queue ) == 0 )
    {
        Popped = LQ_Dequeue( Queue );

        printf( "Dequeue: %s \n", Popped->Data );

        LQ_DestroyNode( Popped );
    }

    LQ_DestroyQueue( Queue );

    return 0;
}

void LQ_CreateQueue( LinkedQueue** Queue ){
    (*Queue) = malloc(sizeof(LinkedQueue));
    (*Queue)->Front = NULL;
    (*Queue)->Rear = NULL;
    (*Queue)->Count = 0;
}

void LQ_DestroyQueue( LinkedQueue* Queue ){
    while(!LQ_IsEmpty(Queue)){
        Node* Popped = LQ_Dequeue(Queue);
        LQ_DestroyNode(Popped);
    }

    free(Queue);
}

Node* LQ_CreateNode(char* Data){
    Node* NewNode = malloc(sizeof(Node));
    NewNode->Data = malloc(strlen(Data) + 1);

    strcpy(NewNode->Data, Data);
    NewNode->NextNode = NULL;

    return NewNode;
}

void LQ_DestroyNode(Node* _Node ){
    free(_Node->Data);
    free(_Node);
}

void LQ_Enqueue( LinkedQueue* Queue, Node* NewNode ){
    if(Queue->Front == NULL){
        Queue->Front = NewNode;
        Queue->Rear = NewNode;
    }
    else{
        Queue->Rear->NextNode = NewNode;
        Queue->Rear = NewNode;
    }
    Queue->Count++;
}

Node* LQ_Dequeue( LinkedQueue* Queue ){
    Node* Popped = Queue->Front;

    if(Queue->Front->NextNode == NULL){
        Queue->Front = NULL;
        Queue->Rear = NULL;
    }
    else{
        Queue->Front = Queue->Front->NextNode;
    }
    
    Queue->Count--;

    return Popped;
}

int LQ_IsEmpty( LinkedQueue* Queue ){
    return (Queue->Count == 0);
}
