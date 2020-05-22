//SHIT----------------------------------------------------------------------------------------------

/*//size_t i_all_var = 0;

size_t CountTree_Var(tree* tree_lang)
{
    auto all_var = (var_t*)calloc(MAX_AMOUNT_FUNCS * MAX_AMOUNT_VARS, sizeof(var_t));
    var_t* begin_all_var = all_var;

    Fill_AllVar(tree_lang->head, all_var);
    all_var = begin_all_var;

    size_t count_var = Count_AllVar(all_var);
    return count_var;
}



void Fill_AllVar(tree_elem* pos, var_t* all_var)
{
    if (!pos) return;

    Fill_AllVar(L, all_var);

    if(pos->data.mode == MODE_VAR)
    {
        if(is_ExistVar)
            all_var = Add_AllVar(all_var, pos->data.word)
    }

    Fill_AllVar(R, all_var);

}*/



/*case MODE_OP_COND:
            buffer.PrintHexCommand(pop_rbx, pop_rbx_size);
            buffer.PrintHexCommand(pop_rax, pop_rax_size);
            buffer.PrintHexCommand(cmp_rax_rbx, cmp_rax_rbx_size);

            switch(Which_ModeOpCond(pos->data.word))
            {
                case OP_COND_JA :   buffer.PrintHexCommand(jbe_long, jbe_long_size);
                                    break;

                case OP_COND_JB :   buffer.PrintHexCommand(jae_long, jae_long_size);
                                    break;

                case OP_COND_JAE:   buffer.PrintHexCommand(jb_long, jb_long_size);
                                    break;

                case OP_COND_JBE:   buffer.PrintHexCommand(ja_long, ja_long_size);
                                    break;

                case OP_COND_JE :   buffer.PrintHexCommand(jne_long, jne_long_size);
                                    break;

                default: fprintf(stderr, "Error front_end OP_COND\n");
                            abort();
            }
            break;*/


/*switch(Which_ModeOpCond(pos->data.word))
            {
                case OP_COND_JE :   buffer.PrintHexCommand(pop_rbx, pop_rbx_size);
                                    buffer.PrintHexCommand(pop_rax, pop_rax_size);
                                    buffer.PrintHexCommand(cmp_rax_rbx, cmp_rax_rbx_size);
                                    buffer.PrintHexCommand(jne_long, jne_long_size);
                                    return;
            }*//*


            */
/*buffer.PrintHexCommand(pop_rbx, pop_rbx_size);
            buffer.PrintHexCommand(pop_rax, pop_rax_size);
            buffer.PrintHexCommand(cmp_rax_rbx, cmp_rax_rbx_size);
            buffer.PrintHexCommand(je_long, je_long_size);
            buffer.PrintHexNumber(27);*//*


            buffer.PrintHexCommand(xor_rax_rax, xor_rax_rax_size);
            buffer.PrintHexCommand(fninit, fninit_size);
            buffer.PrintHexCommand(fild_lrspl, fild_lrspl_size);
            buffer.PrintHexSmallNumber(SIZE_VAR);
            buffer.PrintHexCommand(fild_lrspl, fild_lrspl_size);
            buffer.PrintHexSmallNumber(zero);
            buffer.PrintHexCommand(fcom, fcom_size);
            buffer.PrintHexCommand(fnstsw_ax, fnstsw_ax_size);
            buffer.PrintHexCommand(add_rsp, add_rsp_size);
            buffer.PrintHexSmallNumber(2 * SIZE_VAR);
            */
/*buffer.PrintHexCommand(sahf, sahf_size);

            switch(Which_ModeOpCond(pos->data.word))
            {
                case OP_COND_JA :   buffer.PrintHexCommand(ja_long, ja_long_size);
                                    break;

                case OP_COND_JB :   buffer.PrintHexCommand(jb_long, jb_long_size);
                                    break;

                case OP_COND_JAE:   buffer.PrintHexCommand(jae_long, jae_long_size);
                                    break;

                case OP_COND_JBE:   buffer.PrintHexCommand(jbe_long, jbe_long_size);
                                    break;

                default: fprintf(stderr, "Error front_end OP_COND\n");
                            abort();
            }
            break;*//*


            switch(Which_ModeOpCond(pos->data.word))
            {
                case OP_COND_JE :   buffer.PrintHexCommand(mov_rbx, mov_rbx_size);
                                    buffer.PrintHexNumber(je_mask);
                                    buffer.PrintHexCommand(cmp_rax_rbx, cmp_rax_rbx_size);
                                    buffer.PrintHexCommand(jne_long, jne_long_size);
                                    break;

                case OP_COND_JA :   buffer.PrintHexCommand(mov_rbx, mov_rbx_size);
                                    buffer.PrintHexNumber(ja_mask);
                                    buffer.PrintHexCommand(cmp_rax_rbx, cmp_rax_rbx_size);
                                    buffer.PrintHexCommand(jne_long, jne_long_size);
                                    //buffer.PrintHexCommand(ja_long, ja_long_size);
                                    break;

                case OP_COND_JB :   buffer.PrintHexCommand(mov_rbx, mov_rbx_size);
                                    buffer.PrintHexNumber(jb_mask);
                                    buffer.PrintHexCommand(cmp_rax_rbx, cmp_rax_rbx_size);
                                    buffer.PrintHexCommand(jne_long, jne_long_size);
                                    break;

                */
/*case OP_COND_JAE:   buffer.PrintHexCommand(jae_long, jae_long_size);
                                    break;

                case OP_COND_JBE:   buffer.PrintHexCommand(jbe_long, jbe_long_size);
                                    break;*//*


                default: fprintf(stderr, "Error front_end OP_COND\n");
                            abort();
            }*/



         /*                       case MODE_OP_COND:

        buffer.PrintHexCommand    (xor_rax_rax, xor_rax_rax_size);
        //buffer.PrintHexCommand    (fninit, fninit_size);
        buffer.PrintHexCommand    (fild_lrspl, fild_lrspl_size);
        buffer.PrintHexSmallNumber(SIZE_VAR);
        buffer.PrintHexCommand    (fild_lrspl, fild_lrspl_size);
        buffer.PrintHexSmallNumber(zero);
        buffer.PrintHexCommand    (fcom, fcom_size);
        buffer.PrintHexCommand    (fnstsw_ax, fnstsw_ax_size);
        buffer.PrintHexCommand    (add_rsp, add_rsp_size);
        buffer.PrintHexSmallNumber(2 * SIZE_VAR);
        buffer.PrintHexCommand    (mov_rbx, mov_rbx_size);

        switch(Which_ModeOpCond(pos->data.word))
        {
            case OP_COND_JE :   buffer.PrintHexNumber(je_mask);
                                break;

            case OP_COND_JA :   buffer.PrintHexNumber(ja_mask);
                                break;

            case OP_COND_JB :   buffer.PrintHexNumber(jb_mask);
                                break;

            default: fprintf(stderr, "Error front_end OP_COND\n");
                        abort();
        }
        buffer.PrintHexCommand(cmp_rax_rbx, cmp_rax_rbx_size);
        buffer.PrintHexCommand(jne_long, jne_long_size);
        break;*/



     /*void Do_BackEnd(tree* tree_lang, FILE* elf)
{
    assert(tree_lang);
    assert(elf);

    PrintTree_BinInBuf(tree_lang->head);

    var_Func = nullptr;
    Print_NOP(5);
    PrintLibF_BinInBuf();
    PrintMark_BinInBuf();

    size_t code_size = buffer.GetSize();
    char* elf_header = Create_ElfHeader(code_size);

    *//*for(int i_char = 0; i_char < SIZE_HEADER; i_char++)
        fprintf(elf, "%c", elf_header[i_char]);*//*

    *//*for(int i_char = 0; i_char < code_size; i_char++)
        fprintf(elf, "%c", buffer.GetBufferi(i_char));*//*

    fwrite(elf_header,         sizeof(char), SIZE_HEADER, elf);
    fwrite(buffer.GetBuffer(), sizeof(char), code_size,   elf);

    free(elf_header);
}*/



        /*char* Create_ElfHeader(size_t P_FILESZ, size_t P_MEMSZ)
{
    if(P_MEMSZ == 0)
        P_MEMSZ = P_FILESZ;

    auto header = (char*)calloc(SIZE_HEADER, sizeof(char));

    header = Print_FieldHeader(header, EI_MAG,      4);
    header = Print_FieldHeader(header, I_CLASS,     1);
    header = Print_FieldHeader(header, EI_DATA,     1);
    header = Print_FieldHeader(header, EI_VERSION,  1);
    header = Print_FieldHeader(header, EI_OSABI,    1);
    header = Print_FieldHeader(header, EI_OSABIVER, 8);
    header = Print_FieldHeader(header, E_TYPE,      2);
    header = Print_FieldHeader(header, E_MACHINE,   2);
    header = Print_FieldHeader(header, E_VERSION,   4);
    header = Print_FieldHeader(header, E_ENTRY,     8);
    header = Print_FieldHeader(header, E_PHOFF,     8);
    header = Print_FieldHeader(header, E_SHOFF,     8);
    header = Print_FieldHeader(header, E_FLAGS,     4);
    header = Print_FieldHeader(header, E_EHSIZE,    2);
    header = Print_FieldHeader(header, E_PHENTSIZE, 2);
    header = Print_FieldHeader(header, E_PHNUM,     2);
    header = Print_FieldHeader(header, E_SHENTSIZE, 2);
    header = Print_FieldHeader(header, E_SHNUM,     2);
    header = Print_FieldHeader(header, E_SHSTRNDX,  2);

    header = Print_FieldHeader(header, P_TYPE,   4);
    header = Print_FieldHeader(header, P_FLAGS,  4);
    header = Print_FieldHeader(header, P_OFFSET, 8);
    header = Print_FieldHeader(header, P_VADDR,  8);
    header = Print_FieldHeader(header, P_PADDR,  8);
    header = Print_FieldHeader(header, P_MEMSZ,  8);
    header = Print_FieldHeader(header, P_FILESZ, 8);
    header = Print_FieldHeader(header, P_ALIGN,  8);
    header = Print_FieldHeader(header, P_SPACE,  8);

    header -= SIZE_HEADER;
    return header;
}

char* Print_FieldHeader(char* pos, size_t field, int size_field)
{
    assert(pos);

    for(int i_pos = 0; i_pos < size_field; i_pos++)
    {
        size_t copy_field = field;
        copy_field = copy_field >> 8 * i_pos;
        pos[i_pos] = copy_field;
    }
    pos += size_field;

    assert(pos);

    return pos;
}*/



        /*case MODE_OP_COND:

            buffer.PrintHexCommand    (xor_rax_rax, xor_rax_rax_size);
            //buffer.PrintHexCommand    (fninit, fninit_size);
            buffer.PrintHexCommand    (fild_lrspl, fild_lrspl_size);
            buffer.PrintHexSmallNumber(SIZE_VAR);
            buffer.PrintHexCommand    (fild_lrspl, fild_lrspl_size);
            buffer.PrintHexSmallNumber(zero);
            buffer.PrintHexCommand    (fcom, fcom_size);
            buffer.PrintHexCommand    (fnstsw_ax, fnstsw_ax_size);
            buffer.PrintHexCommand    (add_rsp, add_rsp_size);
            buffer.PrintHexSmallNumber(2 * SIZE_VAR);
            buffer.PrintHexCommand    (mov_rbx, mov_rbx_size);

            switch(Which_ModeOpCond(pos->data.word))
            {
                case OP_COND_JE :   buffer.PrintHexNumber(je_mask);
                                    break;

                case OP_COND_JA :   buffer.PrintHexNumber(ja_mask);
                                    break;

                case OP_COND_JB :   buffer.PrintHexNumber(jb_mask);
                                    break;

                default: fprintf(stderr, "Error front_end OP_COND\n");
                            abort();
            }
            buffer.PrintHexCommand(cmp_rax_rbx, cmp_rax_rbx_size);
            buffer.PrintHexCommand(jne_long, jne_long_size);
            break;*/