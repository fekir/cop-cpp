#include <catch.hpp>

#include "cop.hpp"
#include "cop_test.hpp"


using namespace cop;
using namespace test;
struct struct_with_lessthan_relation{
	int a;
	friend bool operator<(const struct_with_lessthan_relation& lhs, const struct_with_lessthan_relation& rhs){
		return lhs.a < rhs.a;
	}
};

TEST_CASE("test_lessthan_relation"){
	struct_with_lessthan_relation s1a = {1};
	struct_with_lessthan_relation s1b = {1};
	struct_with_lessthan_relation s2 = {2};
	struct_with_lessthan_relation s3 = {3};

	test_less_irreflexivity(s1a);
	test_less_asymmetry(s1a, s2);
	test_less_asymmetry(s1a, s1b);
	test_less_transitivity(s1a, s2, s3);
}

struct struct_with_all_relations{
	int a;
};
inline bool operator<(const struct_with_all_relations& lhs, const struct_with_all_relations& rhs){
	return lhs.a < rhs.a;
}
// generate comparison operator as free function
cop_gen_ordering_ops_fromlessthan(struct_with_all_relations,inline)

TEST_CASE("test_greaterthan_relation"){
	struct_with_all_relations s1a = {1};
	struct_with_all_relations s1b = {1};
	struct_with_all_relations s2 = {2};
	struct_with_all_relations s3 = {3};

	// test op<
	test_less_irreflexivity(s1a);
	test_less_asymmetry(s1a, s2);
	test_less_asymmetry(s1a, s1b);
	test_less_transitivity(s1a, s2, s3);

	// test op>
	test_greater_irreflexivity(s1a);
	test_greater_asymmetry(s1a, s2);
	test_greater_asymmetry(s1a, s1b);
	test_greater_transitivity(s3, s2, s1a);
	test_greater_impl_from_less(s1a, s2);

	// test op<=
	test_lesseq_reflexivity(s1a);
	test_lesseq_totality(s1a, s2);
	test_lesseq_transitivity(s1a, s1b, s2);
	test_lesseq_impl_from_less(s1a, s1b);

	// test op>=
	test_greateq_reflexivity(s1a);
	test_greateq_totality(s1a, s2);
	test_greateq_totality(s1a, s1b);
	test_greateq_transitivity(s2, s1b, s1a);
	test_greateq_impl_from_less(s1a, s1b);

	// test op==
	test_eq_reflexivity(s1a);
	test_eq_symmetry(s1a, s2);
	test_eq_impl_from_less(s1a, s2);

	// test op!=
	test_uneq_irreflexivity(s1a);
	test_uneq_symmetry(s1a, s2);
	test_uneq_impl_from_less(s1a, s2);
}

