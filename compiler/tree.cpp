#include "tree_header.h"

const char* dot_output = "/home/shugaley/proga/projects/1_sem/tree/dot_out";
const size_t SIZE_NEW_ELEM = 1;

bool Create_Tree(tree* tree_name)
{
    assert(tree_name);

    tree_name->err = NO_ERR;
    tree_name->size = 0;

    assert     (tree_name);
    assert_tree(tree_name);

    return true;
}


tree_elem* Add_TreeElem(tree* tree_name, data_t value, char branch, tree_elem* pos)
{
    assert     (tree_name);
    assert_tree(tree_name);

    tree_elem* new_elem = (tree_elem*)calloc(SIZE_NEW_ELEM, sizeof(new_elem[0]));

    Create_New_TreeElem(new_elem);

    new_elem->data = value;

    if (tree_name->size == 0)
        return Create_TreeHead(tree_name, new_elem);

    new_elem->parent = pos;

    if (branch == 'L')
        pos->left = new_elem;

    if (branch == 'R')
        pos->right = new_elem;

    tree_name->size++;

    assert     (tree_name);
    assert_tree(tree_name);

    return new_elem;
}


tree_elem* Create_New_TreeElem(tree_elem* new_elem)
{
    assert(new_elem);

    new_elem->data   = {}     ; /*(data_t)calloc(MAXSIZE_DATA, sizeof(new_elem->data[0]));*/
    new_elem->parent = nullptr;
    new_elem->left   = nullptr;
    new_elem->right  = nullptr;

    assert(new_elem);

    return new_elem;
}


tree_elem* Create_TreeHead(tree* tree_name, tree_elem* new_elem)
{
    assert     (tree_name);
    assert_tree(tree_name);
    assert     (new_elem );

    new_elem->parent = nullptr;

    tree_name->head = new_elem;
    tree_name->size++;

    assert     (tree_name);
    assert_tree(tree_name);

    return new_elem;
}


tree_elem* Search_TreeElem(tree_elem* pos, data_t value)
{
    if (!pos) return nullptr;

//    if (strcmp(pos->data, value) == 0)
        return pos;

    tree_elem* pos_value = nullptr;

    return (pos_value = Search_TreeElem(pos->left, value)) ? (pos_value) : (Search_TreeElem(pos->right, value));
}


bool Destroy_Tree(tree* tree_name)
{
    assert     (tree_name);
    assert_tree(tree_name);

    Destroy_TreeElems(tree_name->head);

    tree_name->size = POISON;
    tree_name->err  = POISON;
    tree_name->head = nullptr;

    assert(tree_name);

    return true;
}


void Destroy_TreeElems(tree_elem* pos)
{
    if(!pos) return;

    Destroy_TreeElems(pos->left);
    Destroy_TreeElems(pos->right);

    pos->parent = nullptr;
    pos->left   = nullptr;
    pos->right  = nullptr;

   // free(pos->data);
    pos->data   = {};

    free(pos);
}


void Print_PreorderTree(tree_elem* pos, FILE* tree_preorder)
{
    assert(tree_preorder);
    assert(pos);

//    if(!pos) return;

    fprintf(tree_preorder, "{");

    fprintf(tree_preorder, " \"%s\" ", pos->data);
    if(pos->left) Print_PreorderTree(pos->left, tree_preorder);
//    Print_Tree(pos->left, tree_preorder);

    if(pos->right) Print_PreorderTree(pos->right, tree_preorder);

//    Print_Tree(pos->right, tree_preorder);

    fprintf(tree_preorder, "}");

    assert(tree_preorder);
}


void Print_InorderTree (tree_elem* pos, FILE* tree_inorder )
{
    assert(tree_inorder);
    assert(pos);

    fprintf(tree_inorder, "(");

    if(pos->left) Print_PreorderTree(pos->left, tree_inorder);

    fprintf(tree_inorder, " %s ", pos->data);

    if(pos->right) Print_PreorderTree(pos->right, tree_inorder);

    fprintf(tree_inorder, ")");

    assert(tree_inorder);
}


#define OK(what, code) \
    if(what) \
    { tree_name->err = code; return false;}

bool TreeOK(tree* tree_name)
{
    OK( tree_name->err != NO_ERR,           ERR_ERR );
    OK(!tree_name,                          PTR_ERR );
    OK(!tree_name->head && tree_name->size, HEAD_ERR);
    OK(!tree_name->size && tree_name->head, SIZE_NULL_ERR);


    size_t i_size = 0;
    TreeElemsOK(tree_name->head, &i_size);
 //   OK( i_size != tree_name->size,           SIZE_ERR);

    return true;
}


void TreeElemsOK(tree_elem* pos, size_t* i_size)
{
    if(!pos) return;

    TreeElemsOK(pos->left,  i_size);
    TreeElemsOK(pos->right, i_size);

    (*i_size)++;
}

#undef OK