#include<stdio.h>
#include<ctype.h>
#include<stdbool.h>

bool isLesser(int need[], int work[], int m){
    for(int i = 0; i < m; i++){
        if(need[i] > work[i]){
            return false;
            
        }
    }
    return true;
}

bool isSafe(int available[],int max[][3], int allocation[][3], int need[][3], int n, int m){
    int i = 0, j = 0, flag, f;
    int work[m];
    int finish[n];
    for(i = 0; i < m; i++){
        work[i] = available[i];
    }
    for(i = 0; i < n; i++){
        finish[i] = false;
    }

    while(true){
        flag = 0;
        f = 0;
        i = 0;
        for (i = 0; i < n; i++){
            if(finish[i] == false){
                f = 1;
                if(isLesser(need[i], work, m) == true){
                    for(j = 0; j < m; j++){
                        work[j] = work[j] + allocation[i][j];
                        finish[i] = true;
                    }
                    printf("p%d ",i);
                    flag = 1;
                    break;
                    
                }
            }
        }
            
            if(f == 0){
                return true;
            }

            if(f == 1 && flag == 0){
                return false;
            }
            
    }

}
int main(){
    int n, m, i, j, p;
    printf("Enter the total number of processes\n");
    scanf("%d",&n);
    printf("Enter the total number of resource types\n");
    scanf("%d",&m);
    int available[m];
    int max[n][m];
    int allocation[n][m];
    int need[n][m];
    int request[n];
    printf("Enter the number of avaliable resources of each type\n");
    for(i = 0; i < m; i++){
        scanf("%d", &available[i]);
    }
    printf("Enter the maximum demand of each process\n");
    for(i = 0; i < n; i++){
        for(j = 0; j < m; j++){
            scanf("%d",&max[i][j]);
        }
    }
    printf("Enter the number of resources of each type currenty allocated to each process\n");
    for(i = 0; i < n; i++ ){
        for(j =0 ;j < m; j++){
            scanf("%d",&allocation[i][j]);
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
   

    
    
    
    bool s = isSafe(available, max, allocation, need, n, m);
    
    if(s == true){
        printf("\nThe system is in safe mode");
    }
    else printf("\nThe system is not in safe mode");

    printf("\nEnter request vector for any process");
    printf("\nWhich process\n");
    scanf("%d",&p);
    printf("Enter the values of that vector\n");
    for(i = 0; i < m; i++){
        scanf("%d",&request[i]);
    }

    if(isLesser(request, need[p], m)){
        if(isLesser(request, available, m)){
            for(i = 0; i < m; i++){
                available[i] -=request[i];
                allocation[p][i] += request[i];
                need[p][i] -= request[i];
            }
            if(isSafe(available, max, allocation, need, n, m)){
                printf("Request can be granted\n");
            }
            else{
                printf("Request cannot be granted\n");
                for(i = 0; i < m; i++){
                    available[i] +=request[i];
                    allocation[p][i] -= request[i];
                    need[p][i] += request[i];
                }
            }
            
        }
        else printf("Required Resources are not available\n");
    }
    else printf("Request cant be granted\n");
}
/*
output:
Enter the total number of processes
5
Enter the total number of resource types
3
Enter the number of avaliable resources of each type
3 3 2
Enter the maximum demand of each process
7 5 3
3 2 2
9 0 2
2 2 2
4 3 3
Enter the number of resources of each type currenty allocated to each process
0 1 0
2 0 0
3 0 2
2 1 1
0 0 2
p1 p3 p0 p2 p4
The system is in safe mode
Enter request vector for any process
Which process
1
Enter the values of that vector
1 0 2
p1 p3 p0 p2 p4 Request can be granted

(5 3 3 3 2 7 5 3 3 2 2 9 0 2 2 2 2 4 3 3 0 1 0 2 0 0 3 0 2 2 1 1 0 0 2)
*/