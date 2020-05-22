#include <cstdio>

extern "C" void _printfx(const char* , ...);

int main()
{
        char a    = 'I';
        char b[5] = "pam";
        int c = 16;
        //_printfx("str %c", a);
        _printfx("str%%str %c %s %d %o %x\n I %s %x %d %% %c %b", a, b, c, c, c, "LOVE", 3802, 100, 'I', 127);
        return 0;
}
