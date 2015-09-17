# compile
g++ -c hitaivo.cpp -o hitaivo
g++ -c first.cpp -o first

# link
g++ first hitaivo -o final

# run
./final


# or equivalent to the compile and link steps above
# g++ first.cpp hitaivo.cpp -o final
