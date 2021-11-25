#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include<vector>
#include<ctime>
#include <math.h>
#include <stdbool.h>

using namespace std;

typedef struct
{
   void** heapAry;
   int    last;
   int    size;
   int    (*compare) (void* argu1, void* argu2);
   int    maxSize;
} HEAP;

int compare(void* p1, void* p2)
{
    return *((int*)p1) - *((int*)p2);
}

//	Prototype Definitions

HEAP* heapCreate (int maxSize,int (*compare) (void* arg1, void* arg2));
bool  heapInsert  (HEAP* heap, void*  dataPtr, int *sum);
bool  heapDelete  (HEAP* heap, void** dataOutPtr, int *sum);
int   heapCount   (HEAP* heap);
bool  heapFull    (HEAP* heap);
bool  heapEmpty   (HEAP* heap);
void  heapDestroy (HEAP* heap);

static void _reheapUp   (HEAP* heap, int childLoc, int *sum);
static void _reheapDown (HEAP* heap, int root, int *sum);

HEAP* heapCreate (int maxSize,int  (*compare) (void* argu1, void* argu2))
{
//	Local Definitions
	HEAP* heap;

//	Statements
	heap = (HEAP*)malloc(sizeof (HEAP));
	if (!heap)
	   return NULL;

	heap->last    = -1;
	heap->compare = compare;

	// Force heap size to power of 2 -1
	heap->maxSize = (int) pow (2, ceil(log2(maxSize))) - 1;
	heap->heapAry = (void**)
	                 calloc(heap->maxSize, sizeof(void*));
	return heap;
}	// createHeap

bool heapInsert (HEAP* heap, void* dataPtr, int *sum)
{
//	Statements
	if (heap->size == 0)                 // Heap empty
	   {
	    heap->size                = 1;
	    heap->last                = 0;
	    heap->heapAry[heap->last] = dataPtr;
	    return true;
	   } // if
	if (heap->last == heap->maxSize - 1)
	  return false;
	++(heap->last);
	++(heap->size);
	heap->heapAry[heap->last] = dataPtr;
	_reheapUp (heap, heap->last, sum);
	return true;
}	// heapInsert

void  _reheapUp  (HEAP* heap, int childLoc, int *sum)
{
//	Local Definitions
	int    parent;
	void** heapAry;
	void*  hold;

	//(*sum)++;//counting from here//////////////////////////////////////////////////////////////////

//	Statements
	// if not at root of heap -- index 0
	if (childLoc)
	   {
        //(*sum)++;
	    heapAry = heap->heapAry;
	    parent = (childLoc - 1)/ 2;
        (*sum)++;
	    if (heap->compare(heapAry[childLoc],
	                      heapAry[parent]) > 0)
	        // child is greater than parent -- swap
	        {
	         hold             = heapAry[parent];
	         heapAry[parent]  = heapAry[childLoc];
	         heapAry[childLoc] = hold;
	        _reheapUp (heap, parent, sum);
	       } // if heap[]
	   } // if newNode
	return;
}	// reheapUp

bool heapDelete (HEAP* heap, void** dataOutPtr, int *sum)
{
//	Statements
	if (heap->size == 0)
	    // heap empty
	    return false;
	*dataOutPtr = heap->heapAry[0];
	heap->heapAry[0]  = heap->heapAry[heap->last];
	(heap->last)--;
	(heap->size)--;
	_reheapDown (heap, 0, sum);
	return true;
}	// heapDelete


void _reheapDown (HEAP* heap, int root, int *sum)
{
//	Local Definitions
	void* hold;
	void* leftData;
	void* rightData;
	int   largeLoc;
	int   last;

	//(*sum)++;//counting from here///////////////////////////////////////////////////////////////////

//	Statements
	last = heap->last;
    //(*sum)++;

	if ((root * 2 + 1) <= last)         // left subtree
	    // There is at least one child
	   {
        //(*sum)++;
	    leftData   = heap->heapAry[root * 2 + 1];

	    //(*sum)++;
	    if ((root * 2 + 2) <= last)  // right subtree
	       rightData = heap->heapAry[root * 2 + 2];
	    else
	       rightData = NULL;

	    // Determine which child is larger
        //(*sum)++;

	    if ((!rightData)
	         || heap->compare (leftData, rightData) > 0)
	       {
	        largeLoc = root * 2 + 1;
	       } // if no right key or leftKey greater
	    else
	       {
	        largeLoc = root * 2 + 2;
	       } // else
	    // Test if root > larger subtree
	     (*sum)++;

	    if (heap->compare (heap->heapAry[root], heap->heapAry[largeLoc]) < 0)
	        {
	         // parent < children
	         hold                = heap->heapAry[root];
	         heap->heapAry[root] = heap->heapAry[largeLoc];
	         heap->heapAry[largeLoc] = hold;
	         _reheapDown (heap, largeLoc, sum);
	        } // if root <
	} // if root
	return;
}	// reheapDown

int main()
{
    HEAP* heap;
    HEAP *heaparr[5];
    ifstream inFile("data.csv", ios::in);
    int *inputdata;
    string data[5][2001];
    int data_int[5][2001];
    //int *test;
    for(int i=0;i<5;++i)
    {
        for(int j=0;j<2001;++j)
        {
            data_int[i][j] = 0;
        }
    }

    int size[5] = {100,200,500,1000,2000};  //array size

    if (!inFile)
    {
        cout << "fail!\n" << endl;
        exit(1);
    }

    string line;
    int col = 0;

    //read in .csv data into array data
    while(getline(inFile, line))
    {
        istringstream sin(line);
        //cout << "org=" << line << endl;
        string field;
        int row = 0;
        while(getline(sin,field,','))
        {
            data[row][col] = field;
            row = row +1;
        }
        //cout << data[0][col] <<" \t"<<data[1][col]<<"\t"<<data[2][col]<<"\t"<<data[3][col]<<"\t"<<data[4][col]<<endl;

        col = col+1;
    }
    //check
/*
    cout<<data[0][0]<<endl;
    cout<<data[0][1]<<endl;
    cout<<data[0][99]<<endl;
    cout<<data[4][1999]<<endl;
    cout<<endl;
*/
    //transform data to data_int
    for(int i=0;i<5;++i)
    {
        for(int j=1;j<=size[i];++j)
        {
            data_int[i][j] = stoi(data[i][j]);
        }
    }
    /*check
    cout<<data_int[0][0]<<endl;
    cout<<data_int[0][1]<<endl;
    cout<<data_int[0][99]<<endl;
    cout<<data_int[4][1999]<<endl;
    cout<<endl;
    */

    srand(time(NULL));
    int sum = 0,num;
    double avg[10]={0};

    //cout<<"create heap:"<<endl;

    for(int i=0;i<5;++i)
    {
        heaparr[i] = heapCreate(size[i],compare);
        for(int j=1;j<=size[i];++j)
        {
            inputdata = new int;
            *inputdata = data_int[i][j];
            heapInsert(heaparr[i],inputdata,&sum);
        }
        sum = 0;
        //cout<<"array size = "<< size[i];
        //cout<<endl;
    }

    cout<<"number of iretation:";
    cin>>num;
    void* dataOut;


    int sum_heapup[5];
    int sum_heapdown[5];

    for(int k=0;k<5;++k)
    {
        sum_heapup[k]= 0;
        sum_heapdown[k] = 0;
    }

    for(int i=0;i<num;++i)
    {
        cout<<endl;
        cout<<"delete part:"<<endl;
        for(int j=0;j<5;++j)
        {
            //delete的同時reheap down
            sum = 0;
            dataOut = heaparr[j]->heapAry[0];
            heapDelete(heaparr[j],(void**)dataOut,&sum);
            cout<<"compare of array "<<size[j]<<"="<<sum<<endl;
            sum_heapdown[j] += sum;
        }

        cout<<endl;
        cout<<"insert part:"<<endl;
        for(int j=0;j<5;++j)
        {
            sum = 0;
            inputdata = new int;
            *inputdata = rand()%5000+1;
            cout<<"input data "<<*inputdata<<endl;
            heapInsert(heaparr[j],inputdata,&sum);
            cout<<"compare of array "<<size[j]<<"="<<sum<<endl;
            sum_heapup[j] += sum;
        }
    }
    cout<<endl<<endl;

    for(int i=0;i<5;++i)
    {
        cout<<"average heapup compare of array "<<size[i]<<"="<<(float)sum_heapup[i]/num<<endl;
        cout<<"average heapdown compare of array "<<size[i]<<"="<<(float)sum_heapdown[i]/num<<endl;
    }


    /*

    討論:
    整體來說,n最小值100取log大約為6~7之間,而n的最大值2000取log為約11,
    比較兩個case的倍率關系約為1.429~1.666之間,此複雜度本身之增長情形本來就較為不明顯，
    如有誤差則影響較較高的複雜度劇烈
    reheap up 的 Big(O) is log n,tree平均比較之複雜度(高度最多log n),觀察結果也有此增長的趨勢
    reheap down 的 Big(O) is log n,tree平均比較之複雜度(高度最多log n),觀察結果因為輸入值random看不太出來,這個case
    的值大概都落在10以內,變化偏不明顯，如以上解釋所述,再n值不夠大的情況下，如果比較次數不多,誤差為蠻重的變因

    */


    return 0;
}
