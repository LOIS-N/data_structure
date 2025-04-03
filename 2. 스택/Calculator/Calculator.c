#include <stdio.h>
#include <string.h>
#include "Calculator.h"

int main( void )
{
    char InfixExpression[100];
    char PostfixExpression[100];

	double Result = 0.0;

    memset( InfixExpression,   0, sizeof(InfixExpression) );
    memset( PostfixExpression, 0, sizeof(PostfixExpression) );
    
    printf( "Enter Infix Expression:" );
    scanf( "%s", InfixExpression );
    
    GetPostfix( InfixExpression, PostfixExpression );
    
    printf( "Infix:%s\nPostfix:%s\n",
             InfixExpression,
             PostfixExpression );

	Result = Calculate( PostfixExpression );

    printf( "Calculation Result : %f\n", Result );

    return 0;
}

char NUMBER[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.'};

int IsNumber( char Cipher ){
    int ArrayLength = sizeof(NUMBER);

    for(int i=0; i<ArrayLength; i++){
        if(Cipher == NUMBER[i]){
            return 1;
        }
    }

    return 0;
}

unsigned int GetNextToken( char* Expression, char* Token, int* TYPE ){
    unsigned int i = 0;
    for(i=0; 0 != Expression[i]; i++){
        Token[i] = Expression[i];

        if( IsNumber(Expression[i]) == 1){
            *TYPE = OPERAND;

            if(IsNumber(Expression[i+1]) != 1){
                break;
            }
        }
        else{
            *TYPE = Expression[i];
            break;
        }
    }

    Token[++i] = '\0';
    return i;
}

int GetPriority(char Operator, int InStack){
    int Priority = -1;

    switch(Operator){
        case LEFT_PARENTHESIS:
            if(InStack){
                Priority = 3;
            }
            else{
                Priority = 0;
            }
            break;
        case MULTIPLY:
        case DIVIDE:
            Priority = 1;
            break;
        case PLUS:
        case MINUS:
            Priority = 2;
            break;
    }

    return Priority;
}

// 연산자의 우선순위 검사
int IsPrior( char Operator1, char Operator2 ){ // operator1-스택 최상단에 있는 연산자, operator2-새로운 연산자
    return GetPriority(Operator1, 1) > getpriority(Operator2, 0);
}

void GetPostfix( char* InfixExpression, char* PostfixExpression ){
    /*
    infix->postfix 변환 알고리즘
    1. 토큰이 피연산자라면 결과에 출력
    2. 토큰이 연산자라면 스택의 최상위 노드에 담긴 연산자와 우선순위를 비교하여, 결과가 참이면 최상위 노드를 꺼내 출력, 거짓이면 연산자를 스택에 삽입
    3. ')'인 경우 '('가 올때가지 스택에서 제거연산을 수행하고, 해당 노드에 담긴 연산자 출력. '(' 연산자는 제거만 수행
    4. infix 표현식을 전부 순회한 경우 스택에 남아있는 연산자를 모두 출력
    */
    LinkedListStack* Stack;

    char Token[32];
    int Type = -1;
    unsigned int Position = 0;
    unsigned int Length = strlen(InfixExpression);

    LLS_CreateStack(&Stack);

    while(Position < Length){
        Position += GetNextToken(&InfixExpression[Position], Token, &Type);

        if(Type == OPERAND){ // 숫자일 때 -> 출력연산
            strcat(PostfixExpression, Token);
            strcat(PostfixExpression, " ");
        }
        else if(Type == RIGHT_PARENTHESIS){ // ')'일 때 -> '(' 까지 연산자 출력
            while(!LLS_IsEmpty(Stack)){
                Node* Popped = LLS_Pop(Stack);

                if(Popped->Data[0] == LEFT_PARENTHESIS){
                    LLS_DestroyNode(Popped);
                    break;
                }
                else{
                    strcat(PostfixExpression, Popped->Data);
                    LLS_DestroyNode(Popped);
                }
            }
        }
        else{ // ')'를 뺀 나머지 기호일 때 -> 우선순위 비교 후 출력 또는 연산자 스택에 삽입 
            while(!LLS_IsEmpty(Stack) && !IsPrior(LLS_Top(Stack)->Data[0], Token[0])){
                Node* Popped = LLS_Pop(Stack);

                if(Popped->Data[0] != LEFT_PARENTHESIS){
                    strcat(PostfixExpression, Popped->Data);
                }

                LLS_DestroyNode(Popped);
            }

            LLS_Push(Stack, LLS_CreateNode(Token));
        }
    }

    while(!LLS_IsEmpty(Stack)){ // infix 표현식 순회 완료 -> 스택에 남은 연산자를 출력
        Node* Popped = LLS_Pop(Stack);

        if(Popped->Data[0] != LEFT_PARENTHESIS){
            strcat(PostfixExpression, Popped->Data);
        }

        LLS_DestroyNode(Popped);
    }

    LLS_DestroyStack(Stack);
}

double Calculate( char* PostfixExpression ){
    /*
    계산 알고리즘
    1. 토큰이 피연산자라면 스택에 토큰 삽입
    2. 연산자라면 스택 제거 2회 수행 후 계산, 결과값을 스택에 삽입
    */
    LinkedListStack* Stack;
    Node*  ResultNode;

    double Result;
    char Token[32];
    int  Type = -1;
    unsigned int Read = 0; 
    unsigned int Length = strlen( PostfixExpression );

    LLS_CreateStack(&Stack);

    while ( Read < Length )
    {
        Read += GetNextToken( &PostfixExpression[Read], Token, &Type );

        if ( Type == SPACE )  
            continue;
        
        if ( Type == OPERAND ) // 피연산자 -> 스택에 삽입
        {
            Node* NewNode = LLS_CreateNode( Token );
            LLS_Push( Stack, NewNode );
        }
        else // 연산자 -> 스택 제거 2회 수행 후 결과값 스택에 삽입
        {
            char   ResultString[32];            
            double Operator1, Operator2, TempResult;
            Node* OperatorNode;

            OperatorNode = LLS_Pop( Stack );
            Operator2 = atof( OperatorNode->Data );
            LLS_DestroyNode( OperatorNode );

            OperatorNode = LLS_Pop( Stack );
            Operator1 = atof( OperatorNode->Data );
            LLS_DestroyNode( OperatorNode );
            
            switch (Type)
            {
            case PLUS:     TempResult = Operator1 + Operator2; break;
            case MINUS:    TempResult = Operator1 - Operator2; break;
            case MULTIPLY: TempResult = Operator1 * Operator2; break;
            case DIVIDE:   TempResult = Operator1 / Operator2; break;
            }

            gcvt( TempResult, 10, ResultString );            
            LLS_Push( Stack, LLS_CreateNode( ResultString ) );
        }
    }

    ResultNode = LLS_Pop( Stack );            
    Result = atof( ResultNode->Data );
    LLS_DestroyNode( ResultNode );

    LLS_DestroyStack( Stack );

    return Result;
}