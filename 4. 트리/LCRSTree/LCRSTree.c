#include "LCRSTree.h"

int main( void )
{
    //  노드 생성 
    LCRSNode* Root = LCRS_CreateNode('A');
    
    LCRSNode* B = LCRS_CreateNode('B');
    LCRSNode* C = LCRS_CreateNode('C');
    LCRSNode* D = LCRS_CreateNode('D');
    LCRSNode* E = LCRS_CreateNode('E');
    LCRSNode* F = LCRS_CreateNode('F');
    LCRSNode* G = LCRS_CreateNode('G');
    LCRSNode* H = LCRS_CreateNode('H');
    LCRSNode* I = LCRS_CreateNode('I');
    LCRSNode* J = LCRS_CreateNode('J');
    LCRSNode* K = LCRS_CreateNode('K');

    //  트리에 노드 추가 
    LCRS_AddChildNode( Root, B );
        LCRS_AddChildNode( B, C );
        LCRS_AddChildNode( B, D );
            LCRS_AddChildNode( D, E );
            LCRS_AddChildNode( D, F );

    LCRS_AddChildNode( Root, G );
        LCRS_AddChildNode( G, H );

    LCRS_AddChildNode( Root, I );
        LCRS_AddChildNode( I, J );
            LCRS_AddChildNode( J, K );
    
    //  트리 출력 
    LCRS_PrintTree( Root, 0 );

    //  트리 소멸시키기 
    LCRS_DestroyTree( Root );

    return 0;
}

LCRSNode* LCRS_CreateNode( ElementType NewData ){
    LCRSNode* NewNode = malloc(sizeof(LCRSNode));
    NewNode->LeftChild = NULL;
    NewNode->RightSibling = NULL;
    NewNode->Data = NewData;

    return NewNode;
}

void LCRS_DestroyNode( LCRSNode* Node ){
    free(Node);
}

void LCRS_DestroyTree( LCRSNode* Root ){
    // LeftChild부터 삭제하면 이전 depth의 노드를 탐색할 방법이 없어지므로 같은 레벨의 노드부터 탐색
    if(Root->RightSibling != NULL){
        LCRS_DestroyNode(Root->RightSibling);
    }

    if(Root->LeftChild != NULL){
        LCRS_DestroyNode(Root->LeftChild);
    }

    Root->LeftChild = NULL;
    Root->RightSibling = NULL;

    LCRS_DestroyNode(Root);
}

void LCRS_AddChildNode( LCRSNode* ParentNode, LCRSNode *ChildNode){
    /*
    1. parentnode가 child를 갖고 있는지 확인
    2. child가 없다면 newnode를 child로 추가
    3. child가 있다면 childnode의 sibling에 추가
    */
    if(ParentNode->LeftChild == NULL){
        ParentNode->LeftChild = ChildNode;
    }
    else{
        LCRSNode* TempNode = ParentNode->LeftChild;

        while(TempNode->RightSibling != NULL){
            TempNode = TempNode->RightSibling;
        }

        TempNode->RightSibling = ChildNode;
    }
}

void LCRS_PrintTree( LCRSNode* Node, int Depth ){
    int i=0;

    for(i=0; i<Depth-1; i++){
        printf("   ");
    }

    if(Depth > 0){
        printf("+--");
    }

    printf("%c\n", Node->Data);

    if(Node->LeftChild != NULL){
        LCRS_PrintTree(Node->LeftChild, Depth+1);
    }

    if(Node->RightSibling != NULL){
        LCRS_PrintTree(Node->RightSibling, Depth);
    }
}