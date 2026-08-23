#include <cstdio>

#include "pointers_and_references.hpp"

namespace {

int failures = 0;
int checks = 0;

void check(bool ok, const char *what) {
    ++checks;
    if (!ok) {
        ++failures;
        std::printf("  FAIL  %s\n", what);
    }
}

void by_value_cannot_retarget_the_caller() {
    int a = 1, b = 2;
    int *p = &a;
    pr::retarget_by_value(p, &b);
    check(p == &a, "by-value int* leaves the caller's pointer alone");
    check(*p == 1, "and it still reads the original target");
}

void pointer_to_pointer_retargets() {
    int a = 1, b = 2;
    int *p = &a;
    pr::retarget_via_pointer_to_pointer(&p, &b);
    check(p == &b, "int** retargets the caller's pointer");
    check(a == 1 && b == 2, "retargeting moves the pointer, not the values");
}

void reference_to_pointer_retargets() {
    int a = 1, b = 2;
    int *p = &a;
    pr::retarget_via_reference_to_pointer(p, &b);
    check(p == &b, "int*& retargets the caller's pointer");
}

void address_of_a_pointer_is_a_pointer_to_pointer() {
    int a = 1;
    int *p = &a;
    int **pp = pr::address_of(p);
    check(pp == &p, "&p yields the address of p itself");
    check(*pp == &a, "*pp is p, which points at a");
    check(**pp == 1, "**pp reaches the value");
}

void deref_and_write_through_two_levels() {
    int a = 1;
    int *p = &a;
    check(pr::deref_once(&p) == 1, "deref_once reads through both levels");
    pr::write_through(&p, 42);
    check(a == 42, "write_through assigns to the pointee");
}

void swap_targets_exchanges_pointers_not_values() {
    int a = 1, b = 2;
    int *p = &a, *q = &b;
    pr::swap_targets(&p, &q);
    check(p == &b && q == &a, "the pointers are exchanged");
    check(a == 1 && b == 2, "the pointed-to values are untouched");
}

void a_reference_is_an_alias() {
    int a = 1;
    int &r = a;
    r = 9;
    check(a == 9, "assigning through a reference writes to the referent");
    check(&r == &a, "a reference has the same address as its referent");
}

}  // namespace

int main() {
    by_value_cannot_retarget_the_caller();
    pointer_to_pointer_retargets();
    reference_to_pointer_retargets();
    address_of_a_pointer_is_a_pointer_to_pointer();
    deref_and_write_through_two_levels();
    swap_targets_exchanges_pointers_not_values();
    a_reference_is_an_alias();

    std::printf("%s  %d checks, %d failed\n", failures ? "FAILED" : "ok    ", checks, failures);
    return failures != 0;
}
