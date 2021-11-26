gcc source/adj-graph/*.c source/*.c -o main

./main < in/01.in >out/01.out
./main < in/02.in >out/02.out
./main < in/03.in >out/03.out
#DIFF

printf "\n\nDIFF 01:\n"
diff -u out/01.out out/_01.out


printf "\n\nDIFF 02:\n"
diff -u out/02.out out/_02.out

printf "\n\nDIFF 03:\n"
diff -u out/03.out out/_03.out
