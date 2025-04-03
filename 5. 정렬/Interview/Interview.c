#include "Point.h"
#include <stdio.h>
#include <string.h>

void Swap( Point* A, Point* B ){
    Point tmp = *A;
    *A = *B;
    *B = tmp;
}

int Partition(Point DataSet[], int Left, int Right ){
    /*
    오름차순
    1. Left - 배열 앞->뒤 방향으로 pivot보다 작은 값을 찾음
    2. Right - 배열 뒤->앞 방향으로 pivot보다 큰 값을 찾음
    3. 두 값의 위치를 교환
    4. Left와 Right가 서로 교차되면 종료
    5. pivot과 Right의 위치를 교환
    6. Right위치()를 반환
    */
    int First = Left;
    double pivot = DataSet[First].point;

    ++Left; // pivot을 정하고 값을 이동시켜주지 않으면 피벗값을 바꾸기때문에 오류가 발생한다

    while(Left<Right){
        while(DataSet[Left].point >= pivot && Left<Right){
            ++Left;
        }
    
        while(DataSet[Right].point <= pivot && Left<=Right){
            --Right;
        }
        
        if(Left<Right){
            Swap(&DataSet[Left], &DataSet[Right]);
        }
        else{
            break;
        }
    }

    Swap(&DataSet[First], &DataSet[Right]);

    return Right;
}

void QuickSort(Point DataSet[], int Left, int Right){
    if(Left<Right){ // 재귀 종료 조건
        int pivot = Partition(DataSet, Left, Right);

        QuickSort(DataSet, Left, pivot-1);
        QuickSort(DataSet, pivot+1, Right);
    }
}

int CompareScore(const void *_elem1, const void *_elem2){
    Point* elem1 = (Point*)_elem1;
    Point* elem2 = (Point*)_elem2;

    if(elem1->point < elem2->point){
        return 1;
    }
    else if(elem1->point > elem2->point){
        return -1;
    }
    else{
        return 0;
    }

}

int main(void){
    int length = (sizeof(DataSet) / sizeof(Point)) - 1;
    // QuickSort(DataSet, 0, length);
    qsort(DataSet, length, sizeof(Point), CompareScore);
    printf("14142번째 고객 ID는 %d, 점수는 %f", DataSet[14141].id, DataSet[14141].point);
    // int i = 14000;
    // while(i<14144){
    //     printf("%d번째 id - %d, point - %f\n", i, DataSet[i].id, DataSet[i].point);
    //     i++;
    // }
}