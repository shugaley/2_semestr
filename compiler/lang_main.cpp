#include "lang_back_end.h"

int main()
{
    FILE* lang_inp         = fopen(LANG_INPUT, "r");
    FILE* tree_lang_output = fopen(TREE_LANG_OUTPUT, "w");
    tree tree_lang = {};
    tree_lang.head = Create_TreeLang(&tree_lang, lang_inp, tree_lang_output);
    fclose(tree_lang_output);
    fclose(lang_inp);

    tree_dot(tree_lang.head);

    /*FILE* tree_lang_input = fopen(TREE_LANG_INPUT, "r");
    tree tree_lang_inp = {};
    tree_lang = *Read_TreeLang(&tree_lang_inp, tree_lang_input);
    fclose(tree_lang_input);

    tree_dot(tree_lang_inp.head);*/

    /*FILE* lang_output = fopen(LANG_OUTPUT, "w");
    Print_Lang(tree_lang_inp.head, lang_output);
    fclose(lang_output);*/

    /*FILE* asm_out = fopen(ASM_OUTPUT, "w");
    PrintAsm_TreeLang(tree_lang.head, asm_out);
    fclose(asm_out);*/

    FILE* elf = fopen(ELF, "w");
    Do_BackEnd(&tree_lang, elf);
    fclose(elf);

    return 0;
}