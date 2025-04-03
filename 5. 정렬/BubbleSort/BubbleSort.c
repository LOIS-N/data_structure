#include <stdio.h> 
 
void BubbleSort(int DataSet[], int Length) 
{ 
    for(int i=0; i<Length-1; i++){
        for(int j=0; j<Length-(i+1); j++){
            if(DataSet[j] > DataSet[j+1]){
                int tmp = DataSet[j];
                DataSet[j] = DataSet[j+1];
                DataSet[j+1] = tmp;
            }
        }
    }
} 
 
int main( void ) 
{ 
    int DataSet[] = {6, 4, 2, 3, 1, 5}; 
    int Length = sizeof DataSet / sizeof DataSet[0];     
    int i = 0; 
 
    BubbleSort(DataSet, Length); 
 
    for ( i=0; i<Length; i++ ) 
    { 
        printf("%d ", DataSet[i]); 
    } 
 
    printf("\n"); 
 
    return 0; 
}
