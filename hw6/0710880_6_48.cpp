#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>
#include<sstream>

using namespace std;

typedef struct tree
{
    char c;
    string binary_code; //0 or 1
    int weight; //比大小用的
    struct tree* left_tree;
    struct tree* right_tree;
}tree_node;

tree_node* createNode(char c_input,int weight_input)
{
    tree_node* new_node = new tree_node;
    new_node->c = c_input;
    new_node->binary_code ="";
    new_node->weight = weight_input;
    new_node->left_tree = NULL;
    new_node->right_tree= NULL;
    return new_node;
}
tree_node* create_newNode(char c_input,int weight_input,string bcode)
{
    tree_node* new_node = new tree_node;
    new_node->c = c_input;
    new_node->binary_code =bcode;
    new_node->weight = weight_input;
    new_node->left_tree = NULL;
    new_node->right_tree= NULL;
    return new_node;
}


tree_node* copy_node(tree_node* copy1)
{
    tree_node* new_node = new tree_node;
    new_node = copy1;
    new_node->c = copy1->c;
    new_node->weight = copy1->weight;
    new_node->binary_code = copy1->binary_code;
    new_node->left_tree = copy1->left_tree;
    new_node->right_tree = copy1->right_tree;

    return new_node;
}

void huff_tree(vector<tree_node*> &list1,int index1,int index2)
{
    tree_node* new_node = new tree_node;
    tree_node* left_node = new tree_node; //min
    tree_node* right_node = new tree_node;// second min

    left_node = copy_node(list1[index1]);
    right_node = copy_node(list1[index2]);

    //weight相加
    new_node->weight = left_node->weight + right_node->weight;

    new_node->left_tree = left_node;
    new_node->right_tree = right_node;

    //家完新增回去
    list1.push_back(new_node);

    if(index1 > index2){
        list1.erase(list1.begin()+index1);
        list1.erase(list1.begin()+index2);
    }
    else{
        list1.erase(list1.begin()+index2);
        list1.erase(list1.begin()+index1);
    }

}

void build_tree(vector<tree_node*> &list1)
{
    //find two min num
    int min_num;
    int index1,index2;

    while(list1.size()>1)
    {
        min_num = list1[0]->weight;
        index1 = 0;
        index2 = 1;

        for(int i=1;i<list1.size();++i)
        {
            if(list1[i]->weight < min_num)
            {
                index2 = index1;
                min_num = list1[i]->weight;
                index1 = i;
            }
            else if(list1[i]->weight<list1[index2]->weight)
            {
                index2 = i;
            }
        }
        //把最小兩個node丟到huff_tree
        huff_tree(list1,index1,index2);
    }
}

//recursive
void huff_encode(tree_node* root)
{
    if(root->left_tree!=NULL)
    {
        root->left_tree->binary_code = root->binary_code+"0";
        huff_encode(root->left_tree);
    }
    if(root->right_tree!=NULL)
    {
        root->right_tree->binary_code = root->binary_code+"1";
        huff_encode(root->right_tree);
    }
    if(root->left_tree == NULL && root->right_tree == NULL)
    {
        //cout<<root->c<<"\t"<<root->weight<<"\t"<<root->binary_code<<endl;
    }
}
int i = 0;
void build_new_vec(tree_node* root,vector<tree_node*> &order1)
{
    if(root->left_tree!=NULL)
    {
        build_new_vec(root->left_tree,order1);
    }
    if(root->right_tree!=NULL)
    {
         build_new_vec(root->right_tree,order1);
    }
    if(root->left_tree == NULL && root->right_tree == NULL)
    {
        order1.push_back(create_newNode(root->c,root->weight,root->binary_code));
        //cout<<order1[i]->c<<"\t"<<order1[i]->weight<<"\t"<<order1[i]->binary_code<<endl;
        ++i;
    }
}

void find_code(tree_node* root,string& result,char target)
{
    if(root->left_tree == nullptr && root->right_tree == nullptr)
    {
        //大小寫都可以 -32->小寫轉大寫
        if(root->c == target||root->c==(char)(target-32))
        {
            result = result + root->binary_code;
        }
    }
    else if(root !=nullptr)
    {
        find_code(root->left_tree,result,target);
        //cout<<root->c<<"\t"<<root->weight<<"\t"<<root->binary_code<<endl;
        find_code(root->right_tree,result,target);
    }

}
string encode(tree_node* root,string &input)
{
    string result = "";
    int pos = 0;
    while(input[pos]!='\0')
    {
        find_code(root,result,input[pos]);
        ++pos;
    }
    return result;
}

string decode(tree_node* root,string &result)
{
    string result_decode = "";
    int pos = 0;
    tree_node* temp = new tree_node;
    temp = root;
    while(result[pos]!='\0')
    {
        if(result[pos] == '0')
        {
            temp = temp->left_tree;
            //if(temp->left_tree==nullptr) cout<<"Transformation failed"<<endl;
        }
        else if(result[pos]=='1')
        {
            temp = temp->right_tree;
            //if(temp->right_tree==nullptr) cout<<"Transformation failed"<<endl;
        }
        if(temp->left_tree == NULL &&temp->right_tree == NULL)
        {
            result_decode += temp->c;
            temp = root;    //  回到root繼續讀
        }
        ++pos;
    }
    if(temp!=root) cout<<"error input"<<endl;

    result_decode+='\0';    //最後結束記得家\0
    delete temp;
    return result_decode;
}

void printlist(vector<tree_node*> &list1)
{
    for(int i=0;i<26;++i)
    {
        cout<<list1[i]->c<<"\t"<<list1[i]->weight<<"\t"<<list1[i]->binary_code<<endl;
        //cout<<(int)list1[i]->c<<endl;
    }
}

void reorder(vector<tree_node*> &list1)
{
    tree_node* temp = new tree_node;
    for(int i =0;i<25;++i)
    {
        for(int j = i;j<26;++j)
        {
            if((int)list1[i]->c>(int)list1[j]->c)
            {
                //cout<<(int)list1[i]->c<<endl;
                temp = copy_node(list1[i]);
                list1[i] = copy_node(list1[j]);
                list1[j] = copy_node(temp);
            }
        }
    }
}

int main()
{
    //file input output
    ifstream infile;
    infile.open("Hw6.txt");
    char in_char;
    int in_int;

    if(!infile)
    {
        cout<<"file open fail"<<endl;
    }

    string input_encode;
    string input_decode;
    string result_code ="";
    string result_decode = "";
    vector <tree_node*> list_tree;
    vector <tree_node*> in_ABCD_order;
    //initial(list_tree);
    //printlist(list_tree);

    while(!infile.eof())
    {
        infile>>in_char>>in_int;
        list_tree.push_back(createNode(in_char,in_int));
    }
    //printlist(list_tree);
    //cout<<endl;

    build_tree(list_tree);
    tree_node* root = new tree_node;
    root = list_tree[0];
    huff_encode(root);
    //root = list_tree[0];
    build_new_vec(root,in_ABCD_order);
    //printlist(in_ABCD_order);

    reorder(in_ABCD_order);
    printlist(in_ABCD_order);


    //encode
    cout<<"---------------------------------------------"<<endl;
    cout<<"Enter any word you want to encode:"<<endl;
    cin>>input_encode;
    //cout<<input_encode<<endl;
    //cout<<(char)(input_encode[0]-32)<<endl;
    result_code = encode(root,input_encode);
    cout<<"Encode result = "<<result_code<<endl<<endl;

    //decode
    cout<<"Enter any word you want to decode:"<<endl;
    cin>>input_decode;
    result_decode = decode(root,input_decode);
    cout<<"Decode result = "<<result_decode<<endl<<endl;

    delete root;

    return 0;
}
