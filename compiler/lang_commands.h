#ifdef OP_MATH

DEF_OP_MATH(разам з,   +, 13, 1);

DEF_OP_MATH(без,       -, 6,  2);

DEF_OP_MATH(прапалоць, *, 18, 3);

DEF_OP_MATH(скасіць,   /, 14, 4);

#undef OP_MATH
#endif





#ifdef OP_COND

DEF_OP_COND(як,              ==, 4,  5);

DEF_OP_COND(больш чым,       >,  17, 1);

DEF_OP_COND(меньш чым,       <,  17, 2);

DEF_OP_COND(больш-равно чым, >=, 28, 3);

DEF_OP_COND(меньш-равно чым, <=, 28, 4);

#undef OP_COND
#endif






#ifdef FUNC_SYS

DEF_FUNC_SYS(ураджай,  put,  14);

DEF_FUNC_SYS(угнаенне, get , 16);

#undef FUNC_SYS
#endif






#ifdef FUNC_MATH


DEF_FUNC_MATH(клубень, sqrt, 14);

#undef FUNC_MATH
#endif