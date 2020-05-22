#include "lang_header.h"

void print_mode(tree_elem* pos, FILE* dot_out)
{
    assert(pos);
    assert(dot_out);

    switch ((pos->data).mode)
    {
        case MODE_FUNC_MAIN:     fprintf(dot_out, "[label = \"%s\", shape = \"box\", "
                                           "color=\"#ffe4c4\", style=\"filled\", "
                                           "fillcolor = \"#32CD32\"]", (pos->data).word);
                          break;

        case MODE_FUNC_OWN:      fprintf(dot_out, "[label = \"%s\", shape = \"box\", "
                                           "color=\"#ffe4c4\", style=\"filled\", "
                                           "fillcolor = \"#32CD32\"]", (pos->data).word);
                          break;

        case MODE_FUNC_OWN_DEF:   fprintf(dot_out, "[label = \"%s\", shape = \"box\", "
                                           "color=\"#ffe4c4\", style=\"filled\", "
                                           "fillcolor = \"#32CD32\"]", (pos->data).word);
                          break;

        case MODE_FUNC_SYS:      fprintf(dot_out, "[label = \"%s\", shape = \"septagon\", "
                                           "color=\"#ffffff\", style=\"filled\", "
                                           "fillcolor = \"#F0E68C\"]", (pos->data).word);
                          break;

        case MODE_FUNC_SYS_IN:    fprintf(dot_out, "[label = \"%s\", shape = \"septagon\", "
                                           "color=\"#ffffff\", style=\"filled\", "
                                           "fillcolor = \"#F0E68C\"]", (pos->data).word);
                          break;

        case MODE_FUNC_SYS_OUT:    fprintf(dot_out, "[label = \"%s\", shape = \"septagon\", "
                                           "color=\"#ffffff\", style=\"filled\", "
                                           "fillcolor = \"#F0E68C\"]", (pos->data).word);
                          break;

        case MODE_FUNC_SYS_RET:  fprintf(dot_out, "[label = \"%s\", shape = \"septagon\", "
                                           "color=\"#ffffff\", style=\"filled\", "
                                           "fillcolor = \"#F0E68C\"]", (pos->data).word);
                          break;

        case MODE_VAR:           fprintf(dot_out, "[label = \"%s\", shape = \"egg\", "
                                           "color=\"#caff70\", style=\"filled\", "
                                           "fillcolor = \"#9932CC\"]", (pos->data).word);
                          break;

        case MODE_NUM:           fprintf(dot_out, "[label = \"%d\", shape = \"egg\", "
                                           "color=\"#556b2f \", style=\"filled\", "
                                           "fillcolor = \"#FFA07A\"]", (pos->data).number);
                          break;

        case MODE_OP_ASS:        fprintf(dot_out, "[label = \"%s\", shape = \"larrow\", "
                                           "color=\"#ffffff\", style=\"filled\", "
                                           "fillcolor = \"#F0E68C\"]", (pos->data).word);
                          break;

        case MODE_OP_COND:       fprintf(dot_out, "[label = \"%s\", shape = \"parallelogram\", "
                                           "color=\"#c3beb4 \", style=\"filled\", "
                                           "fillcolor = \"#F0E68C\"]", (pos->data).word);
                          break;

        case MODE_OP_MATH:
            switch(*pos->data.word)
            {
                case '+': fprintf(dot_out, "[label = \"%s\", shape = \"diamond\", "
                                           "color=\"#ffd700\", style=\"filled\", "
                                           "fillcolor = \"#F0E68C\"]", (pos->data).word);
                          break;

                case '-': fprintf(dot_out, "[label = \"%s\", shape = \"diamond\", "
                                           "color=\"#da70d6\", style=\"filled\", "
                                           "fillcolor = \"#F0E68C\"]", (pos->data).word);
                          break;

                case '*': fprintf(dot_out, "[label = \"%s\", shape = \"diamond\", "
                                           "color=\"#ffc0cb\", style=\"filled\", "
                                           "fillcolor = \"#F0E68C\"]", (pos->data).word);
                          break;

                case '/': fprintf(dot_out, "[label = \"%s\", shape = \"diamond\", "
                                           "color=\"#fffff0\", style=\"filled\", "
                                           "fillcolor = \"#F0E68C\"]", (pos->data).word);
                          break;

                default:          fprintf(stderr, "DOT OP_MATH ERROR!!!");
                          break;
            }
                          break;

        case MODE_FUNC_MATH: fprintf(dot_out, "[label = \"%s\", shape = \"diamond\", "
                                           "color=\"#ffffff\", style=\"filled\", "
                                           "fillcolor = \"#F0E68C\"]", (pos->data).word);
                          break;


        case MODE_OP_OP_COMMA:    fprintf(dot_out, "[label = \"%s\", shape = \"circle\", "
                                           "color=\"#ffffff\", style=\"filled\", "
                                           "fillcolor = \"#F0E68C\"]", (pos->data).word);
                          break;

        case MODE_FUNC_SYS_IF:    fprintf(dot_out, "[label = \"%s\", shape = \"hexagon\", "
                                           "color=\"#ffffff\", style=\"filled\", "
                                           "fillcolor = \"#F0E68C\"]", (pos->data).word);
                          break;

        case MODE_FUNC_SYS_IFE:   fprintf(dot_out, "[label = \"%s\", shape = \"hexagon\", "
                                           "color=\"#ffffff\", style=\"filled\", "
                                           "fillcolor = \"#F0E68C\"]", (pos->data).word);
                          break;

        case MODE_FUNC_SYS_WH:    fprintf(dot_out, "[label = \"%s\", shape = \"hexagon\", "
                                           "color=\"#ffffff\", style=\"filled\", "
                                           "fillcolor = \"#F0E68C\"]", (pos->data).word);
                          break;

        case MODE_OP:             fprintf(dot_out, "[label = \"%s\", shape = \"circle\", "
                                           "color=\"#ffffff\", style=\"filled\", "
                                           "fillcolor = \"#F0E68C\"]", (pos->data).word);
                          break;

        case MODE_PUNC_SEMI_GL:   fprintf(dot_out, "[label = \"%s\", shape = \"circle\", "
                                           "color=\"#ffffff\", style=\"filled\", "
                                           "fillcolor = \"#F0E68C\"]", (pos->data).word);
                          break;

        case MODE_EMPTY:          fprintf(dot_out, "[label = \"%s\", shape = \"circle\", "
                                           "color=\"#ffffff\", style=\"filled\", "
                                           "fillcolor = \"#F0E68C\"]", (pos->data).word);
                          break;

        default:                  fprintf(dot_out, "\"error\"");
                          break;
    }

    assert(pos);
    assert(dot_out);
}


int tmp = 0;
void create_tree(tree_elem* pos, FILE* dot_out)
{
    assert(dot_out);
    assert(pos);

    fprintf(dot_out, "\t\they%d", tmp);
    print_mode(pos, dot_out);
    fprintf(dot_out, ";\n");

    int iskan = tmp;

    if (pos->left != nullptr) {
        fprintf(dot_out, "\t\they%d", iskan);

        fprintf(dot_out, "->");

        fprintf(dot_out, "hey%d;\n", ++tmp);

        create_tree(pos->left, dot_out);
    }

    if (pos->right != nullptr) {
        fprintf(dot_out, "\t\they%d", iskan);

        fprintf(dot_out, "->");

        fprintf(dot_out, "hey%d;\n", ++tmp);

        create_tree(pos->right, dot_out);
    }

    assert(pos);
    assert(dot_out);
}

void tree_dot(tree_elem* nameTree)
{

    FILE *file_dot = fopen(DOT, "wb");
    assert(file_dot);

    fprintf(file_dot, "digraph {\n");
    fprintf(file_dot, "\tnode[color = \"#000000\", fontsize = 20];\n"
                      "\tedge[color = \"#000000\", fontsize = 20];\n");

    create_tree(nameTree, file_dot);

    fprintf(file_dot, "}");

    assert(file_dot);
    fclose(file_dot);

    system("dot -Tjpg -o /home/shugaley/proga/projects/2_sem/asm/compiler/tree_1.jpg"
           " /home/shugaley/proga/projects/2_sem/asm/compiler/dot_out.dot");

}


