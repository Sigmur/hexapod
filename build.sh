echo "1 - Cleanup ... "
rm hexapod
echo "2 - Build  ... "
cd src
make
echo "3 - Deploy  ... "
make install
echo "Done ! run './hexapod'"