#Bundle

Bundle bundles together a bundle of resources. It takes inspiration from MS resource files to compile resources into one binary.

###Usage

Say you want the data for your resource to be bundled with your binary file. Your data is (for example) called "example.dat". Now, if in your (for example) main.c you used a global variable EXAMPLE_DAT as your data, then you would have something like:
<pre>extern char *EXAMPLE_DATA;

int main()
{
    // Do something with EXAMPLE_DATA here
}</pre>

So, to use bundle to bundle your example data, you would partially compile you main.c:
<pre>gcc -c -o bin/main.o main.c</pre>
Then you would copy your example.dat to bin/EXAMPLE_DAT (the variable name you used in main.c). Then, in you bin folder, run bundle:
<pre>bundle EXAMPLE_DAT</pre>
and you will get a file called EXAMPLE_DAT.o. Link this with you main.o file:
<pre>gcc EXAMPLE_DAT.o main.o -o my_binary</pre>
and viola!

