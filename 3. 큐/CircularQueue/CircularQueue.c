#include "CircularQueue.h"

int main( void )
{
    int i;
    CircularQueue* Queue;

    CQ_CreateQueue(&Queue, 10);
    
    CQ_Enqueue( Queue, 1 );
    CQ_Enqueue( Queue, 2 );
    CQ_Enqueue( Queue, 3 );
    CQ_Enqueue( Queue, 4 );

    for ( i=0; i<3; i++)
    {
        printf( "Dequeue: %d, ",       CQ_Dequeue( Queue ) );
        printf( "Front:%d, Rear:%d\n", Queue->Front, Queue->Rear );
    }
    
    i = 100;
    while ( CQ_IsFull( Queue ) == 0 )
    {
        CQ_Enqueue( Queue, i++ );
    }

    printf( "Capacity: %d, Size: %d\n\n", 
        Queue->Capacity, CQ_GetSize(Queue ) );

    while ( CQ_IsEmpty( Queue ) == 0)
    {        
        printf( "Dequeue: %d, ",       CQ_Dequeue( Queue ) );
        printf( "Front:%d, Rear:%d\n", Queue->Front, Queue->Rear );
    }

    CQ_DestroyQueue( Queue );

    return 0;
}

void CQ_CreateQueue( CircularQueue** Queue, int Capacity){
    (*Queue) = malloc(sizeof(CircularQueue));

    // +1 = 큐가 가득 찼을때의 rear를 위한 더미노드
    (*Queue)->Nodes = malloc(sizeof(Node) * (Capacity+1));

    (*Queue)->Capacity = Capacity;
    (*Queue)->Front = 0;
    (*Queue)->Rear = 0;
}

void CQ_DestroyQueue( CircularQueue* Queue ){
    free(Queue->Nodes);
    free(Queue);
}

void CQ_Enqueue( CircularQueue* Queue, ElementType Data){
    // Rear는 실제 후단의 값 +1을 가지므로 새로운 데이터를 Rear위치에 저장하고, Rear를 한칸 뒤로 옮긴다.
    int Position = 0;
    
    if(Queue->Capacity == Queue->Rear){
        Position = Queue->Rear;
        Queue->Rear = 0;
    }
    else
        Position = Queue->Rear++;

        Queue->Nodes[Position].Data = Data;
}

ElementType CQ_Dequeue( CircularQueue* Queue ){
    int Position = Queue->Front;

    if(Queue->Front == Queue->Capacity){
        Queue->Front = 0;
    }
    else
        Queue->Front++;

    return Queue->Nodes[Position].Data;
}

int CQ_GetSize( CircularQueue* Queue ){
    if(Queue->Front <= Queue->Rear)
        return Queue->Rear - Queue->Front;
    else
        return Queue->Rear + (Queue->Capacity - Queue->Front + 1);
}

int CQ_IsEmpty( CircularQueue* Queue ){
    return (Queue->Front == Queue->Rear);
}

int CQ_IsFull( CircularQueue* Queue ){
    if(Queue->Front < Queue->Rear) // Front가 0이고 Rear가 Capacity인 경우;
        return (Queue->Rear - Queue->Front) == Queue->Capacity;
    else
        return (Queue->Rear+1) == Queue->Front;
}