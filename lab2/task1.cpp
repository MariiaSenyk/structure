#include <iostream>
#include <time.h>
using namespace std;
void bubbleSortAsc(int A[],int n)
{
    for(int i=0;i<n-1;i++)
    {
        for(int j=0;j<n-i-1;j++)
            if(A[j]>A[j+1]) swap(A[j],A[j+1]);
    }
}
void bubbleSortDesc(int A[],int n)
{
    for(int i=0;i<n-1;i++)
    {
        for(int j=0;j<n-i-1;j++)
            if(A[j]<A[j+1]) swap(A[j],A[j+1]);
    }
}
void processArray(int A[],int n)
{
    int evenCount=0,oddCount=0;
    for(int i=0;i<n;i++)
    {
        if(A[i]%2==0) evenCount++;
        else oddCount++;
    }
    int even[evenCount],odd[oddCount];
    int evenIndex=0,oddIndex=0;
    for(int i=0;i<n;i++)
    {
        if(A[i]%2==0) even[evenIndex++]=A[i];
        else odd[oddIndex++]=A[i];
    }
    clock_t start=clock();
    bubbleSortAsc(even,evenCount);
    clock_t end=clock();
    double elapsed=(double(end-start))/CLOCKS_PER_SEC;
    cout<<"Time for ascending sort (even numbers): "<<elapsed<<" seconds"<<endl;
    start=clock();
    bubbleSortDesc(odd,oddCount);
    end=clock();
    elapsed=(double(end-start))/CLOCKS_PER_SEC;
    cout<<"Time for descending sort (odd numbers): "<<elapsed<<" seconds"<<endl;
    int k=0;
    for(int i=0;i<evenCount;i++) A[k++]=even[i];
    for(int i=0;i<oddCount;i++) A[k++]=odd[i];
}
void printArray(int A[],int n)
{
    for(int i=0;i<n;i++) cout<<A[i]<<" ";
    cout<<endl;
}
int main()
{
    int n;
    cout<<"Enter the size of the array: ";
    cin>>n;
    int A[n];
    cout<<"Enter the elements of the array: ";
    for(int i=0;i<n;i++) cin>>A[i];
    cout<<"Original array: ";
    printArray(A,n);
    processArray(A,n);
    cout<<"Transformed array: ";
    printArray(A,n);
    return 0;
}