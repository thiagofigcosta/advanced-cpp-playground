#pragma once

// The three ways a function can be handed an `int*` and the one thing that
// separates them: which of them can retarget the CALLER's pointer.
//
// Taking `int*` by value copies the pointer, so reassigning it is invisible to
// the caller. To move the caller's pointer you need its address (`int**`) or an
// alias for it (`int*&`). This is the whole answer to "what does & do in front
// of a pointer": `&p` on an `int*` yields an `int**`.

namespace pr {

// Reassigns only the local copy. Kept because being able to show that it does
// nothing is the point of the other two.
inline void retarget_by_value([[maybe_unused]] int *p, int *to) { p = to; }

inline void retarget_via_pointer_to_pointer(int **pp, int *to) { *pp = to; }

inline void retarget_via_reference_to_pointer(int *&pr, int *to) { pr = to; }

inline int **address_of(int *&p) { return &p; }

inline int deref_once(int **pp) { return *(*pp); }

inline void write_through(int **pp, int value) { **pp = value; }

inline void swap_targets(int **a, int **b) {
    int *tmp = *a;
    *a = *b;
    *b = tmp;
}

}  // namespace pr
