#include "ArrayStack.h"

int main( void )
{
    int i= 0;
    ArrayStack* Stack = NULL;

    AS_CreateStack(&Stack, 10);
    
    AS_Push(Stack, 3);
    AS_Push(Stack, 37);
    AS_Push(Stack, 11);
    AS_Push(Stack, 12);

    printf( "Capacity: %d, Size: %d, Top: %d\n\n", 
        Stack->Capacity, AS_GetSize(Stack), AS_Top(Stack) );

    for ( i=0; i<4; i++ )
    {
        if ( AS_IsEmpty(Stack) )
            break;
        
        printf( "Popped: %d, ", AS_Pop(Stack) );
        
        if ( ! AS_IsEmpty(Stack) )
            printf( "Current Top: %d\n", AS_Top(Stack) );
        else
            printf( "Stack Is Empty.\n" );
    }

    AS_DestroyStack(Stack);

    return 0;
}

void AS_CreateStack(ArrayStack** Stack, int Capacity){
    // 스택을 자유 저장소에 생성
    (*Stack) = malloc(sizeof(ArrayStack));

    // 입력된 capacity만큼의 노드를 자유 저장소에 저장
    (*Stack)->Nodes = malloc(sizeof(Node)*Capacity);

    // capacity와 top 초기화
    (*Stack)->Capacity = Capacity;
    (*Stack)->Top = -1;
}

void AS_DestroyStack(ArrayStack* Stack){
    free(Stack->Nodes);
    free(Stack);
}

void AS_Push(ArrayStack* Stack, ElementType Data){
    Stack->Top++;
    Stack->Nodes[Stack->Top].Data = Data;
}

ElementType AS_Pop(ArrayStack* Stack){
    int Position = Stack->Top--;
    return Stack->Nodes[Position].Data;
}

ElementType AS_Top(ArrayStack* Stack){
    return Stack->Nodes[Stack->Top].Data;
}

int AS_GetSize(ArrayStack* Stack){
    return Stack->Top+1;
}

int AS_IsEmpty(ArrayStack* Stack){
    if(Stack->Top == -1){
        return 1;
    }
    else{
        return 0;
    }
}