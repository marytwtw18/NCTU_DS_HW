# include <iostream>
using namespace std;

typedef struct bst
{
    int data;
    int lth,rth;
    struct bst *left,*right;
} node;

class thread
{
private:

    node *dummy;
    node *New,*root,*temp,*parent;
public:
    thread(); //constructor
    void create(int data);
    void output();
};

thread::thread()
{
    root=NULL;
}

void thread::create(int data)
{
    void insert(node *,node *);
    New=new node;
    New->left=NULL;
    New->right=NULL;
    New->lth=0;
    New->rth=0;
    New->data = data;

    if(root==NULL)
    {
        // Tree is not Created
        root=New;
        dummy=new node;
        dummy->data=-99;
        dummy->left=root;
        root->left=dummy;
        root->right=dummy;
    }
    else
    {
        if(!(data > 99 || data < 0)) insert(root,New);
    }
}

void thread::output()
{
    void inorder(node *,node *dummy);
    if(root==NULL)
        cout<<"Tree is not created";
    else
    {
        inorder(root,dummy);
    }
}

//function is for creating a binary search tree
void insert(node *root,node *New)
{
    if(New->data<root->data)
    {
        if(root->lth==0)
        {
           // New->left=root->left; //null
            New->right=root;
            root->left=New;
            root->lth=1;
        }
        else
            insert(root->left,New);
    }
    else
    {
        if(root->rth==0)
        {
            New->right=root->right; //important point
            root->rth=1;
            root->right=New;
        }
        else
            insert(root->right,New);
    }
}

//inorder function
void inorder(node *temp,node *dummy)
{
    FILE* fout;
    fout = fopen("7_24_output.txt","w");
    while(temp!=dummy)
    {
        while(temp->lth==1)
            temp=temp->left;
        //cout<<"  "<<temp->data;
        fprintf(fout,"%d\n",temp->data);
        while(temp->rth==0)
        {
            temp=temp->right;
            if(temp==dummy)
                return;
            //cout<<"  "<<temp->data;
            fprintf(fout,"%d\n",temp->data);
        }
        temp=temp->right;
    }
    fclose(fout);
}

int main()
{
    FILE* fin;

    fin = fopen("7_24_input.txt","r");


    if(!fin)
    {
        cout<<"file open fail"<<endl;
    }

    int num;

    thread th1;

    while( fscanf(fin,"%d",&num)!= EOF)
    {
        th1.create(num);
    }

    th1.output();

    fclose(fin);
    return 0;
}
