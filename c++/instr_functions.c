#include <stdio.h>
#include <string.h>

#define SZ      (3 * 100)

char ind_enter[SZ] = ">|";

void __cyg_profile_func_enter(void *this_fn, void *dummy) {
    fprintf(stderr, "%s %p\n", ind_enter, this_fn);
    int pos = strlen(ind_enter) % SZ;

    ind_enter[pos] = ind_enter[pos + 1] = ind_enter[pos + 2] = '>';
    ind_enter[pos + 3] = '|';
    ind_enter[pos + 4] = '\0';
}

void __cyg_profile_func_exit(void *this_fn, void *dummy) {
    ind_enter[strlen(ind_enter) - 4] = '\0';
}
