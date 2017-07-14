#include <catch.hpp>

#include "cop.hpp"
#include "cop_test.hpp"


using namespace cop;
using namespace test;

struct struct_with_equalcomp_relation{
	int a;
	friend bool operator==(const struct_with_equalcomp_relation& lhs, const struct_with_equalcomp_relation& rhs){
		return lhs.a == rhs.a;
	}
};


TEST_CASE("verify_equalcomp_relation"){
	struct_with_equalcomp_relation s1a = {1};
	struct_with_equalcomp_relation s1b = {1};
	struct_with_equalcomp_relation s2 = {2};

	test_eq_reflexivity(s1a);
	test_eq_symmetry(s1a, s1b);
	test_eq_symmetry(s1a, s2);
}

// generate operator!= through CRTP, therefore we need to add a constructor to our class
struct struct_with_unequalcomp_relation : private cop::equal_comparable<struct_with_unequalcomp_relation>
{
	int a;
	friend bool operator==(const struct_with_unequalcomp_relation& lhs, const struct_with_unequalcomp_relation& rhs){
		return lhs.a == rhs.a;
	}
	struct_with_unequalcomp_relation(int a_) :a(a_){}
};

TEST_CASE("verify_equalcomp_and_uneq_relation"){
	struct_with_unequalcomp_relation s1a = {1};
	struct_with_unequalcomp_relation s1b = {1};
	struct_with_unequalcomp_relation s2 = {2};

	test_eq_reflexivity(s1a);
	test_uneq_irreflexivity(s1a);

	test_eq_symmetry(s1a, s1b);
	test_uneq_symmetry(s1a, s2);

	test_uneq_impl_from_eq(s1a, s2);
}
