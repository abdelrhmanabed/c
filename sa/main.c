#include <stdio.h>
#include <stdlib.h>

int main() { int n = 23, a = 5, b = 4; a==b++? (n%=4):(n%=3); printf("%d", n); return 0; }
