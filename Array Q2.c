#include <stdio.h>

int main(){
    int smallest,location;
    int arr1[10];
    for (int i = 0; i < 10; i++)
    {
        printf("Enter the Element:%d\n",i);
        scanf("%d", &arr1[i]);
    }

        smallest = arr1[1];
        for (int i = 0; i < 10; i++)
        {
            if (arr1[i]<smallest)
            {
                smallest=arr1[i];
                location = i;
            }
            
        }
        
        printf("the smallest element is %d which is in arr[%d]",smallest,location);


    return 0;
}
