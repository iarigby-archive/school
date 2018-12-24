echo " ### Compiling the While compiler..."
make clean && make
echo " ### Compiling While to ASM..."
./while example.while > example.asm
echo " ### Compiling ASM to Object code..."
nasm -felf example.asm
echo " ### Linking..."
gcc io.c example.o -m32 -oexample
echo " ### Executing the test..."
./example

