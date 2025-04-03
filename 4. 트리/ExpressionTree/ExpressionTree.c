#include "ExpressionTree.h"

int main( void )
{
    ETNode* Root = NULL;

    char PostfixExpression[20] = "71*52-/";
    ET_BuildExpressionTree( PostfixExpression, &Root);

    //  트리 출력 
    printf("Preorder ...\n");
    ET_PreorderPrintTree( Root );
    printf("\n\n");

    printf("Inorder ... \n");
    ET_InorderPrintTree( Root );
    printf("\n\n");

    printf("Postorder ... \n");
    ET_PostorderPrintTree( Root );
    printf("\n");

    printf("Evaulation Result : %f \n", ET_Evaluate( Root ) );

    //  트리 소멸
    ET_DestroyTree( Root );

    return 0;
}

ETNode* ET_CreateNode( ElementType NewData ){
    ETNode* NewNode = malloc(sizeof(ETNode));

    NewNode->Left = NULL;
    NewNode->Right = NULL;
    NewNode->Data = NewData;

    return NewNode;
}

void ET_DestroyNode( ETNode* Node ){
    free(Node);
}

void ET_DestroyTree( ETNode* Root ){
    if(Root->Right != NULL){
        ET_DestroyNode(Root->Right);
    }

    if(Root->Left != NULL){
        ET_DestroyNode(Root->Left);
    }

    Root->Left = NULL;
    Root->Right = NULL;

    ET_DestroyNode(Root);
}

void ET_PreorderPrintTree( ETNode* Node ){
    if(Node == NULL){
        return;
    }

    printf("%c ", Node->Data);

    if(Node->Left != NULL){
        ET_PreorderPrintTree(Node->Left);
    }

    if(Node->Right != NULL){
        ET_PreorderPrintTree(Node->Right);
    }
}

void ET_InorderPrintTree( ETNode* Node ){
    if(Node == NULL){
        return;
    }

    printf("(");

    if(Node->Left != NULL){
        ET_InorderPrintTree(Node->Left);
    }

    printf("%c", Node->Data);

    if(Node->Right != NULL){
        ET_InorderPrintTree(Node->Right);
    }

    printf(")");
}

void ET_PostorderPrintTree( ETNode* Node ){
    if(Node==NULL){
        return;
    }

    if(Node->Left != NULL){
        ET_PostorderPrintTree(Node->Left);
    }

    if(Node->Right != NULL){
        ET_PostorderPrintTree(Node->Right);
    }

    printf("%c ", Node->Data);
}

void ET_BuildExpressionTree( char* PostfixExpression, ETNode** Node ){
    int len = strlen(PostfixExpression);
    char Token = PostfixExpression[len-1];
    PostfixExpression[len-1] = '\0';

    switch(Token){
        // 연산자
        case '+':
        case '-':
        case '*':
        case '/':
            (*Node) = ET_CreateNode(Token);
            ET_BuildExpressionTree(PostfixExpression, &(*Node)->Right);
            ET_BuildExpressionTree(PostfixExpression, &(*Node)->Left);
            break;

        // 피연산자
        default:
            (*Node) = ET_CreateNode(Token);
            break;
    }
}

double ET_Evaluate( ETNode* Tree ){
    char Temp[2];

    double left = 0;
    double right = 0;
    double result = 0;

    if(Tree == NULL){
        return 0;
    }

    switch(Tree->Data){
        // 연산자
        case '+':
        case '-':
        case '*':
        case '/':
            left = ET_Evaluate(Tree->Left);
            right = ET_Evaluate(Tree->Right);

            if(Tree->Data == '+') result = left + right;
            else if(Tree->Data == '-')result = left - right;
            else if(Tree->Data == '*')result = left * right;
            else if(Tree->Data == '/')result = left / right;

            break;

        default:
            memset(Temp, 0, sizeof(Temp));
            Temp[0] = Tree->Data;
            result = atof(Temp);
            break;
    }

    return result;
}