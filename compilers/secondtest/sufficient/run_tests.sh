make
echo "****************"
echo "error checking:"
echo "****************"
./while tests/example_notdeclared.while
./while tests/example_notinteger.while
echo "****************"
echo "execution"
echo "****************"
./README tests/example.while 