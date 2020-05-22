#ifndef LANGUAGE_TREE_HEADER_H
#define LANGUAGE_TREE_HEADER_H

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cassert>
#include <sys/stat.h>
#include <cmath>
#include <cstdarg>
#include <ctime>

//const data_t DATA_POISON = nullptr;
const int POISON = -666;
const size_t MAXSIZE_DATA = 100;

enum error_tree
{
    NO_ERR =        100000,
    PTR_ERR =       100001,
    HEAD_ERR =      100010,
    ERR_ERR =       110000,
    SIZE_NULL_ERR = 100011,
    SIZE_ERR =      100012,
};



struct tree_data
{
    int mode   = POISON ;
    int number = POISON ;
    char* word = nullptr;
};

typedef tree_data data_t;


struct tree_elem
{
    data_t data       = {}     ;
    tree_elem* parent = nullptr;
    tree_elem* left   = nullptr;
    tree_elem* right  = nullptr;
};


struct tree
{
    tree_elem* head = nullptr;
    size_t size = POISON;
    size_t err = POISON;
};




bool Create_Tree(tree* tree_name);

tree_elem* Add_TreeElem(tree* tree_name, data_t value, char branch, tree_elem* pos);
tree_elem* Create_TreeHead(tree* tree_name, tree_elem* new_elem);
tree_elem* Create_New_TreeElem(tree_elem* new_elem);

bool Destroy_Tree     (tree* tree_name);
void Destroy_TreeElems(tree_elem* pos );


bool TreeOK     (tree* tree_name);
void TreeElemsOK(tree_elem* pos, size_t* i_size);
void Print_PreorderTree(tree_elem* pos, FILE* tree_preorder);
void Print_InorderTree (tree_elem* pos, FILE* tree_inorder );
//bool TreeDump (tree* tree_name);
void Akinator_Dot (tree* tree_name);
void Create_Tree_Dot (tree_elem* pos, FILE* file_dot);


//Graphwiz-------
void print_mode (tree_elem* pos, FILE* dot_out);
void create_tree(tree_elem* pos, FILE* dot_out);
void tree_dot   (tree_elem* nameTree);

#define DED

#define dump(tree_name) \
{\
    fprintf(stderr, "Error file     %s\n", __FILE__           ); \
    fprintf(stderr, "Error function %s\n", __PRETTY_FUNCTION__); \
    fprintf(stderr, "Error line     %d\n", __LINE__           ); \
    /*TreeDump(tree_name);*/ \
}


#ifdef DED
#define assert_tree(tree_name) \
{\
    if(!TreeOK(tree_name)) \
    {  dump(tree_name); fprintf(stderr, "Error code %zu\n\n\n", tree_name->err);  abort(); }\
}
#else
#define assert_tree ;
#endif


#endif //LANGUAGE_TREE_HEADER_H
