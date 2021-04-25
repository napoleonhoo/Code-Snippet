set -x
g++ -o quick_sort.o -c quick_sort.cc
g++ -o quick_sort_debug.o -c quick_sort_debug.cc
# g++ -o util.o -c ../util/util.cc
g++ -o quick_sort_debug quick_sort.o quick_sort_debug.o # util.o
