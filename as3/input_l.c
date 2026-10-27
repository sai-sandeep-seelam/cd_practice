int main()
{
    int a = 10;
    int b = 20;

    // Addition

    if(a < b)
    {
        a = a + b;
    }

    return 0;
}
/*# 1. Move into the as3 directory
cd as3

# 2. Run flex using its full path (or add C:\msys64\usr\bin to your PATH)
C:\msys64\usr\bin\flex.exe lexical.l

# 3. Compile without -lfl
gcc lex.yy.c -o lexical.exe

# 4. Pipe the input into the executable
Get-Content input_l.c | .\lexical.exe
*/