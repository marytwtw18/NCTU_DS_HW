#include<iostream>
#include<cstring>
using namespace std;

#include<vector>
#include<string>

class Heap
{
public:
    int* heaparr;
    int heapsize;
    int last_num;
    Heap()
    {
        heapsize = 20;
        last_num = 0;
        heaparr = new int[heapsize];
    }
};

void reheapUp(Heap* heap,int *count);
void reheapDown(Heap* heap,int *count,int last);
void Heap_insert(Heap *heap,int *count,int value);
void heap_sort(Heap* heap,int *count);

void reheapUp(Heap* heap,int *count)
{
    int root = heap->last_num;

    while((root-1)/2 >= 0)
    {
        if(heap->heaparr[root] >heap->heaparr[(root-1)/2])
        {
            int temp = heap->heaparr[root];
            heap->heaparr[root] = heap->heaparr[(root-1)/2];
            heap->heaparr[(root-1)/2] = temp;

            (*count) += 3;
            root = (root-1)/2;
        }
        else
        {
            break;
        }
    }
}

void reheapDown(Heap* heap,int *count,int last)
{
    int root = 0;
    //leftchild
    while(root*2+1 <= last)
    {
        int leftpoint = root*2 + 1;


        //right child
        if(root*2+2<=last)
        {
            int rightpoint = root*2+2;
            if(heap->heaparr[leftpoint] > heap->heaparr[root])
            {
                if(heap->heaparr[leftpoint] > heap->heaparr[rightpoint])
                {
                    int temp_heap = heap->heaparr[leftpoint];
                    heap->heaparr[leftpoint] = heap->heaparr[root];
                    heap->heaparr[root] = temp_heap;
                    (*count) += 3;
                    root = leftpoint;
                }
                else
                {
                    int temp_heap = heap->heaparr[rightpoint];
                    heap->heaparr[rightpoint] = heap->heaparr[root];
                    heap->heaparr[root] = temp_heap;
                    (*count) += 3;
                    root = rightpoint;
                }
            }
            else if(heap->heaparr[rightpoint] > heap->heaparr[root])
            {
                int temp_node = heap->heaparr[rightpoint];
                heap->heaparr[rightpoint] = heap->heaparr[root];
                heap->heaparr[root] = temp_node ;
                (*count) += 3;
                root = rightpoint;
            }
            else
            {
                break;
            }
        }
        else if(heap->heaparr[leftpoint] > heap->heaparr[root])
        {
            int temp_point = heap->heaparr[leftpoint];
            heap->heaparr[leftpoint] = heap->heaparr[root];
            heap->heaparr[root] = temp_point;
            root = leftpoint;
            (*count)+=3;
        }
        else
        {
            break;
        }

    }
}

void Heap_insert(Heap *heap,int *count,int value)
{
    heap->heaparr[heap->last_num] = value;
    reheapUp(heap,count);
    heap->last_num++;
}

void heap_sort(Heap* heap,int *count)
{
    int temp_data = heap->heaparr[0];
    heap->heaparr[0] = heap->heaparr[heap->last_num];
    heap->heaparr[heap->last_num] = temp_data;
    --(heap->last_num);
    (*count) += 3;
    reheapDown(heap,count,heap->last_num);
}

int main()
{
    int data[20] = {47, 80, 42, 37, 45, 4, 52, 39, 65, 32, 54, 71, 82, 20, 99, 55, 30, 96, 2, 56};
    Heap heap ;
    cout<<"unsorted array: ";

    int count = 0;

    for(int i=0;i<20;++i)
    {
        cout<<" "<<data[i];
        Heap_insert(&heap,&count,data[i]);
    }
    heap.last_num--;
    cout<<endl;
    cout<<"sorted array: ";

    for(int i=0;i<heap.heapsize-1;++i)
    {
        heap_sort(&heap,&count);
    }

    for(int i=0;i<heap.heapsize;++i)
    {
        cout<<" "<<heap.heaparr[i];
    }
    cout<<endl;

    cout<<"Total exchanges:";
    cout<<" "<<count <<endl;


    return 0;
}
