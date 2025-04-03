/*
    - order함수 3개 null 확인 조건문 추가안함
    null일 경우 Data를 접근할 시 Segmentation fault 발생
*/
#include "BinaryTree.h"

int main( void )
{
    //  노드 생성 
    SBTNode* A = SBT_CreateNode('A');
    SBTNode* B = SBT_CreateNode('B');
    SBTNode* C = SBT_CreateNode('C');
    SBTNode* D = SBT_CreateNode('D');
    SBTNode* E = SBT_CreateNode('E');
    SBTNode* F = SBT_CreateNode('F');
    SBTNode* G = SBT_CreateNode('G');
    
    //  트리에 노드 추가 
    A->Left  = B;
    B->Left  = C;
    B->Right = D;

    A->Right = E;
    E->Left  = F;
    E->Right = G;
    
    //  트리 출력 
    printf("Preorder ...\n");
    SBT_PreorderPrintTree( A );
    printf("\n\n");

    printf("Inorder ... \n");
    SBT_InorderPrintTree( A );
    printf("\n\n");

    printf("Postorder ... \n");
    SBT_PostorderPrintTree( A );
    printf("\n");

    //  트리 소멸시키기 
    SBT_DestroyTree( A );

    return 0;
}

SBTNode* SBT_CreateNode( ElementType NewData ){
    SBTNode* NewNode = malloc(sizeof(SBTNode));

    NewNode->Left = NULL;
    NewNode->Right = NULL;
    NewNode->Data = NewData;

    return NewNode;
}

void SBT_DestroyNode( SBTNode* Node ){
    free(Node);
}

void SBT_DestroyTree( SBTNode* Root ){
    if(Root->Right != NULL){
        SBT_DestroyNode(Root->Right);
    }

    if(Root->Left != NULL){
        SBT_DestroyNode(Root->Left);
    }

    Root->Left = NULL;
    Root->Right = NULL;

    SBT_DestroyNode(Root);
}

void SBT_PreorderPrintTree( SBTNode* Node ){
    // printf("%c ", Node->Data);

    // if(Node->Left != NULL){
    //     SBT_PreorderPrintTree(Node->Left);
    // }

    // if(Node->Right != NULL){
    //     SBT_PreorderPrintTree(Node->Right);
    // }

    if(Node == NULL){
        return;
    }

    printf("%c ", Node->Data);

    if(Node->Left != NULL){
        SBT_PreorderPrintTree(Node->Left);
    }

    if(Node->Right != NULL){
        SBT_PreorderPrintTree(Node->Right);
    }
}

void SBT_InorderPrintTree( SBTNode* Node ){
    // if(Node->Left != NULL){
    //     SBT_InorderPrintTree(Node->Left);
    // }

    // printf("%c ", Node->Data);

    // if(Node->Right != NULL){
    //     SBT_InorderPrintTree(Node->Right);
    // }

    if(Node == NULL){
        return;
    }

    if(Node->Left != NULL){
        SBT_InorderPrintTree(Node->Left);
    }

    printf("%c ", Node->Data);

    if(Node->Right != NULL){
        SBT_InorderPrintTree(Node->Right);
    }
}

void SBT_PostorderPrintTree( SBTNode* Node ){
    // if(Node->Left != NULL){
    //     SBT_PostorderPrintTree(Node->Left);
    // }

    // if(Node->Right != NULL){
    //     SBT_PostorderPrintTree(Node->Right);
    // }

    // printf("%c ", Node->Data);

    if(Node==NULL){
        return;
    }

    if(Node->Left != NULL){
        SBT_PostorderPrintTree(Node->Left);
    }

    if(Node->Right != NULL){
        SBT_PostorderPrintTree(Node->Right);
    }

    printf("%c ", Node->Data);
}