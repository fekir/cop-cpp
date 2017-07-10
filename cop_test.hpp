#ifndef cop_test_hpp_RTEL3TRJNXY204WYK7KZ0Q95KLSPVX
#define cop_test_hpp_RTEL3TRJNXY204WYK7KZ0Q95KLSPVX

//          Copyright Federico Kircheis 2017
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <catch.hpp>

/// Test cases that a class should pass in order to satisy the LessThanComparable or EqualityComparable concept

namespace cop {
namespace test{

template<class cl>
void test_less_irreflexivity(const cl& el){
	bool eq = (el < el);
	REQUIRE_FALSE(eq);
}

template<class cl1, class cl2>
void test_less_asymmetry(const cl1& a, const cl2& b){
	bool res1 = (a < b);
	bool res2 = (b < a);
	if(res1){
		REQUIRE_FALSE(res2);
	}
}

template<class cl1, class cl2, class cl3>
void test_less_transitivity(const cl1& a, const cl2& b, const cl3& c){
	bool res1 = (a < b);
	bool res2 = (b < c);
	if(!res1 || !res2){
		FAIL("need ordered elements");
	}
	REQUIRE(a < c);
}

// --------------------------------------------------
// if operator> is defined
template<class cl>
void test_greater_irreflexivity(const cl& el){
	bool eq = (el > el);
	REQUIRE_FALSE(eq);
}

template<class cl1, class cl2>
void test_greater_asymmetry(const cl1& a, const cl2& b){
	bool res1 = (a > b);
	bool res2 = (b > a);
	if(res1){
		REQUIRE_FALSE(res2);
	}
}

template<class cl1, class cl2, class cl3>
void test_greater_transitivity(const cl1& a, const cl2& b, const cl3& c){
	bool res1 = (a > b);
	bool res2 = (b > c);
	if(!res1 || !res2){
		FAIL("need ordered elements");
	}
	REQUIRE(a > c);
}

template<class cl1, class cl2>
void test_greater_impl_from_less(const cl1& lhs, const cl2& rhs){
	bool res1 = !(lhs < rhs);
	bool res2 = (lhs > rhs);
	REQUIRE(res1 == res2);

	res1 = !(lhs > rhs);
	res2 = (lhs < rhs);
	REQUIRE(res1 == res2);

	auto is_noex_greater = noexcept (lhs > rhs);
	auto is_noex_less = noexcept (lhs < rhs);
	REQUIRE(is_noex_less == is_noex_greater);
}

// --------------------------------------------------
// if operator<= is defined
template<class cl>
void test_lesseq_reflexivity(const cl& el){
	bool eq = (el <= el);
	REQUIRE(eq);
}

template<class cl>
void test_lesseq_totality(const cl& a, const cl& b){
	bool res1 = (a <= b);
	bool res2 = (b <= a);
	if(!res1){
		REQUIRE(res2);
	}
	if(!res2){
		REQUIRE(res1);
	}
}

template<class cl1, class cl2, class cl3>
void test_lesseq_transitivity(const cl1& a, const cl2& b, const cl3& c){
	bool res1 = (a <= b);
	bool res2 = (b <= c);
	if(!res1 || !res2){
		FAIL("need ordered elements");
	}
	REQUIRE(a <= c);
}


template<class cl>
void test_lesseq_impl_from_less(const cl& lhs, const cl& rhs){
	bool res1 = !(rhs < lhs);
	bool res2 = (lhs <= rhs);
	REQUIRE(res1 == res2);

	res1 = !(lhs < rhs);
	res2 = (rhs <= lhs);
	REQUIRE(res1 == res2);


	auto is_noex_lesseq = noexcept (lhs <= rhs);
	auto is_noex_less = noexcept (lhs < rhs);
	REQUIRE(is_noex_less == is_noex_lesseq);
}

// --------------------------------------------------
// if operator>= is defined
template<class cl>
void test_greateq_reflexivity(const cl& el){
	bool eq = (el >= el);
	REQUIRE(eq);
}

template<class cl1, class cl2>
void test_greateq_totality(const cl1& a, const cl2& b){
	bool res1 = (a >= b);
	bool res2 = (b >= a);
	if(!res1){
		REQUIRE(res2);
	}
	if(!res2){
		REQUIRE(res1);
	}
}

template<class cl1, class cl2, class cl3>
void test_greateq_transitivity(const cl1& a, const cl2& b, const cl3& c){
	bool res1 = (a >= b);
	bool res2 = (b >= c);
	if(!res1 || !res2){
		FAIL("need ordered elements");
	}
	REQUIRE(a >= c);
}

template<class cl1, class cl2>
void test_greateq_impl_from_less(const cl1& lhs, const cl2& rhs){
	bool res1 = !(lhs < rhs);
	bool res2 = (lhs >= rhs);
	REQUIRE(res1 == res2);

	res1 = !(rhs < lhs);
	res2 = (rhs >= lhs);
	REQUIRE(res1 == res2);

	auto is_noex_lesseq = noexcept (lhs >= rhs);
	auto is_noex_less = noexcept (lhs < rhs);
	REQUIRE(is_noex_less == is_noex_lesseq);
}

// --------------------------------------------------
// if operator== is defined
template<class cl>
void test_eq_reflexivity(const cl& el){
	bool eq = (el == el);
	REQUIRE(eq);
}

template<class cl1, class cl2>
void test_eq_symmetry(const cl1& lhs, const cl2& rhs){
	bool res1 = (lhs == rhs);
	bool res2 = (rhs == lhs);
	if(res1 != res2){
		FAIL("ordering of operation is relevant");
	}
}

template<class cl1, class cl2>
void test_eq_impl_from_less(const cl1& lhs, const cl2& rhs){
	bool res1 = (lhs == rhs);
	bool res2 = !(rhs < lhs) && !(lhs < rhs);
	REQUIRE(res1 == res2);

	res1 = (rhs == lhs);
	REQUIRE(res1 == res2);

	auto is_noex_lesseq = noexcept (lhs == rhs);
	auto is_noex_less = noexcept (lhs < rhs);
	REQUIRE(is_noex_less == is_noex_lesseq);
}

// --------------------------------------------------
// if operator== is defined
template<class cl>
void test_uneq_irreflexivity(const cl& el){
	bool eq = (el != el);
	REQUIRE_FALSE(eq);
}

template<class cl1, class cl2>
void test_uneq_symmetry(const cl1& lhs, const cl2& rhs){
	bool res1 = (lhs != rhs);
	bool res2 = (rhs != lhs);
	if(res1 != res2){
		FAIL("ordering of operation is relevant");
	}
}

template<class cl1, class cl2>
void test_uneq_impl_from_less(const cl1& lhs, const cl2& rhs){
	bool res1 = (lhs != rhs);
	bool res2 = (lhs < rhs) ||  (rhs < lhs);
	REQUIRE(res1 == res2);

	res1 = (rhs != lhs);
	res2 = (rhs < lhs) ||  (lhs < rhs);
	REQUIRE(res1 == res2);

	auto is_noex_uneq = noexcept (lhs != rhs);
	auto is_noex_less = noexcept (lhs < rhs);
	REQUIRE(is_noex_less == is_noex_uneq);
}

template<class cl1, class cl2>
void test_uneq_impl_from_eq(const cl1& lhs, const cl2& rhs){
	bool res1 = !(lhs == rhs);
	bool res2 = (lhs != rhs);
	REQUIRE(res1 == res2);

	auto is_noex_uneq = noexcept (lhs != rhs);
	auto is_noex_eq = noexcept (lhs == rhs);
	REQUIRE(is_noex_eq == is_noex_uneq);
}

} // namespace
} // namespace
#endif
