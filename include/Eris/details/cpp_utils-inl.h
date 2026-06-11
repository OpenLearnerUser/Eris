#pragma once

namespace Eris{
    template <class ForwardIt, class T, class Compare>
    ForwardIt binaryFind(ForwardIt first, ForwardIt last, const T& value,
                         Compare comp) {
                            first = std::lower_bound(first, last, value, comp);
                            if (first != last && !comp(*first, value) && !comp(value, *first)) {
                                return first;
                            }
                            return last;
                         }

}
