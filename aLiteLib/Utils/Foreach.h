//
// Created by Bryan on 11/08/2024.
//

#ifndef ALITE_FOREACH_H
#define ALITE_FOREACH_H


#define Foreach(l, r, f) __for_each(l, r, f)

template<class Iter_t, class Func_t>
Func_t __for_each (Iter_t l_it, Iter_t r_it, Func_t func) {
    while (l_it != r_it) {
        func(*l_it);
        ++ l_it;
    }
    return func;
}

#endif //ALITE_FOREACH_H
