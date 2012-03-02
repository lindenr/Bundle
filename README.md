#Bundle

Bundle bundles together a bundle of resources. It takes inspiration from MS resource files to compile resources into one binary.

##Usage

Say you want the data for your resource to be bundled with your binary file. Your data is (for example) called "example.dat". Now, if in your (for example) main.c you used a global variable EXAMPLE_DAT as your data, then you would have something like:
<pre>extern char *EXAMPLE_DATA;

int main()
{
    // Do something with EXAMPLE_DATA here
}</pre>

So, to use bundle to bundle your example data, you would partially compile you main.c:
<pre>gcc -c -o bin/main.o main.c</pre>
Then you would copy your example.dat to bin/EXAMPLE_DAT (the variable name you used in main.c). Then, in your bin folder, run bundle:
<pre>bundle EXAMPLE_DAT</pre>
and you will get a file called EXAMPLE_DAT.o. Link this with you main.o file:
<pre>gcc EXAMPLE_DAT.o main.o -o my_binary</pre>
and voila!

##Usage example

So, say my current directory looks like this:
<pre>bundle        EXAMPLE_DATA         main.c        main.o</pre>
In main.c I have:
<pre>#include <stdlib.h>
#include <stdio.h>
extern char *EXAMPLE_DATA;

int main()
{
    printf("%s\n", EXAMPLE_DATA);
    exit(0);
}</pre>
In EXAMPLE_DATA I have:
<pre>Hello, World!</pre>

Now I run bundle:
<pre>$ bundle EXAMPLE_DATA</pre>
Now I have a file EXAMPLE_DATA.o which I can link with main.o:
<pre>$ gcc main.o EXAMPLE_DATA.o -o main</pre>
And we are done. So I can try:
<pre>$ ./main
Hello, World!

$ </pre>

