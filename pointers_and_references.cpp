#include <iostream>

#include "pointers_and_references.hpp"

using std::cout;

namespace {

void rule(const char *title) { cout << "\n== " << title << " ==\n"; }

}  // namespace

int main() {
    // The example from good_way_to_understand_pointer_and_references.png.
    int i = 5, j = 6, k = 7;
    int *ip1 = &i, *ip2 = &j;
    int **ipp = &ip1;

    rule("the two meanings of &");
    cout << "&i  is the address-of operator: an int*   -> " << *(&i) << "\n";
    cout << "&j  applied to an int gives int*          -> " << *(&j) << "\n";
    cout << "int &r = k declares a reference, not an address\n";
    int &r = k;
    r = 70;
    cout << "  r = 70 wrote through to k               -> k = " << k << "\n";
    k = 7;

    rule("ipp = &ip1");
    cout << "ipp holds the address of ip1, so ipp is an int**\n";
    cout << "  *ipp  == ip1 (a pointer)      : " << (*ipp == ip1 ? "true" : "false") << "\n";
    cout << "  **ipp == i   (the value)      : " << pr::deref_once(ipp) << "\n";
    cout << "  address_of(ip1) == ipp        : "
         << (pr::address_of(ip1) == ipp ? "true" : "false") << "\n";

    rule("who can retarget the caller's pointer");
    cout << "ip1 currently points at i (" << *ip1 << ")\n";

    pr::retarget_by_value(ip1, ip2);
    cout << "  by value  int*   -> ip1 still points at " << *ip1
         << "  (the copy moved, ip1 did not)\n";

    pr::retarget_via_pointer_to_pointer(&ip1, ip2);
    cout << "  via int**        -> ip1 now points at   " << *ip1 << "\n";

    pr::retarget_via_reference_to_pointer(ip1, &i);
    cout << "  via int*&        -> ip1 back to         " << *ip1 << "\n";

    rule("writing through two levels");
    pr::write_through(ipp, 50);
    cout << "  write_through(ipp, 50) set i to " << i << "\n";
    i = 5;

    rule("swapping what two pointers point at");
    cout << "  before: *ip1 = " << *ip1 << ", *ip2 = " << *ip2 << "\n";
    pr::swap_targets(&ip1, &ip2);
    cout << "  after : *ip1 = " << *ip1 << ", *ip2 = " << *ip2
         << "   (i and j themselves are untouched: " << i << ", " << j << ")\n";

    rule("a reference is not a pointer");
    cout << "  a reference cannot be null, cannot be reseated, has no arithmetic\n";
    cout << "  int &r = k binds once; r = <value> always writes to k\n";
    cout << "  k is still " << k << "\n";

    return 0;
}
