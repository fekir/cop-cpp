# cop - cpp
## Comparison Operators for C++

After polishing various completely different projects, I noticed that they had the following things in common: a lot of boilerplate code for defining, implementing and eventually testing comparison operators.

Unlike normal functions, there are a lot of expectations when using ``<,>,<=,>=,==`` or ``!=`` in C++, especially if you want to use some algorithm like ``std::find`` or ``std::sort``.

Most of the time defining those operators is trivial, nevertheless copy-and-paste errors slip too often between those functions, creating obscure error messages while compiling, or hard to find errors to debug.

Therefore I decided to group this code together and make it generic enough for most use cases. 
The result of this polishing is ``cop``, a simple  header file to help you implement your own comparison operators.

## How to use it
Simply import one header file, [cop.hpp](cop.hpp), and generate with it all comparison functions you want, with standard semantics, in order to be consistent with the [LessThanComparable](http://en.cppreference.com/w/cpp/concept/LessThanComparable) or [EqualityComparable](http://en.cppreference.com/w/cpp/concept/EqualityComparable) concept with minimum effort.

```cpp
#include "cop.hpp"
class myclass{
  ....
  friend bool operator<(const myclass& lhs, const myclass& rhs){
        ...
    }
}
// automatically define all other operators:
cop_gen_ordering_ops_fromlessthan(myclass,inline)
```

And if you hate macros, you can use [CRTP](https://en.wikipedia.org/wiki/Curiously_recurring_template_pattern) to generate all operators as member functions instead of free functions:
```cpp
#include "cop.hpp"
class myclass : private cop::less_comparable<myclass>{
  ....
  friend bool operator<(const myclass& lhs, const myclass& rhs){
        ...
    }
}
```

In the repository you can also find a [example](example), which shows you how you can define and tune your operators.

## Testing
In my experience, comparison operators are rarely tested.
It cannot harm to run at least some basic checks, since there are so many expectations that cannot be tested by the compiler.
``cop`` provides a second header, [cop_test.hpp](cop_test.hpp), with different basic test cases for all comparison operators.
The only dependency is the test framework [catch](https://github.com/philsquared/Catch).
Of course, you can test comparison operators that do not have been generated with ``cop``.
The two headers are completely independent.

```cpp
#include "cop_test.hpp"
TEST_CASE("basic test for op==/op!= of myclass"){
    myclass a = ...;
    myclass b = ...;

    test_eq_reflexivity(a);
    test_uneq_irreflexivity(a);

    test_eq_symmetry(a, b);
    test_uneq_symmetry(a, b);

    test_uneq_impl_from_eq(a, b);
}
```


## License
Source code is licensed under the [Boost Software License](LICENSE.txt)

## Contributing
``cop`` doesn't cover all possible use cases, but only those that, in my opinion, are the most common ones. 
It is probably not the ultimate tool for generating your comparison operators, but it aims to be easy to use, cover most use cases, and be interoperable with other tools.
If you think that
  - there are use cases that I did not consider,
  - some test cases are missing,
  - there are errors,

you can
  - open an issue,
  - make a pull request.

