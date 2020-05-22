#include "lang_header.h"

#define L pos->left
#define R pos->right

void Simplify_Tree(tree_elem* pos)
{
    if(!pos || is_end(pos)) return;

    Simplify_Tree(pos->left );
    Simplify_Tree(pos->right);

    if(pos->data.mode == MODE_OP_MATH)

        switch(*pos->data.word)
        {
            case '+' :
                if(is_zero(L))
                {
                    pos->data = R->data;
                    L = R->left;
                    R = R->right;
                    break;
                }

                if(is_zero(R))
                {
                    pos->data = L->data;
                    R = L->right;
                    L = L->left;
                    break;
                }

                if(is_num(R) && is_num(L))
                {
                    pos->data.mode   = MODE_NUM;
                    pos->data.number = L->data.number + R->data.number;
                    R = nullptr;
                    L = nullptr;
                    break;
                }

            case '*' :
                if(is_zero(L) || is_zero(R))
                {
                    if(is_zero(L))
                        pos->data = L->data;
                    else
                        pos->data = R->data;

                    L = nullptr;
                    R = nullptr;
                    break;
                }

                if(is_one(L))
                {
                    pos->data = R->data;
                    L = R->left;
                    R = R->right;
                    break;
                }

                if(is_one(R))
                {
                    pos->data = L->data;
                    R = L->right;
                    L = L->left;
                    break;
                }

                if(is_num(R) && is_num(L))
                {
                    pos->data.mode   = MODE_NUM;
                    pos->data.number = R->data.number * L->data.number;
                    R = nullptr;
                    L = nullptr;
                    break;
                }

            case '/' :
                if(is_zero(L))
                {
                    pos->data = L->data;
                    L = nullptr;
                    R = nullptr;
                    break;
                }

                if(is_one(R))
                {
                    pos->data = L->data;
                    R = L->right;
                    L = L->left;
                    break;
                }

                if(is_num(R) && is_num(L))
                {
                    pos->data.mode   = MODE_NUM;
                    pos->data.number = L->data.number / R->data.number;
                    R = nullptr;
                    L = nullptr;
                    break;
                }

            case '-' :
                if(is_zero(R))
                {
                    pos->data = L->data;
                    R = L->right;
                    L = L->left;
                    break;
                }

                if(is_num(R) && is_num(L))
                {
                    pos->data.mode   = MODE_NUM;
                    pos->data.number = L->data.number - R->data.number;
                    R = nullptr;
                    L = nullptr;
                    break;
                }
        }
}

#undef L
#undef R