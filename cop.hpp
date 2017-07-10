#ifndef cop_hpp_QWJR44CITWPF1YLD9C9B6JAZ5462UQ
#define cop_hpp_QWJR44CITWPF1YLD9C9B6JAZ5462UQ

//          Copyright Federico Kircheis 2017
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)




/// This macros and structures helps to avoid writing boilerplate code for defining
/// operator>, operator<=,  operator>=,, operator== and operator!=
/// if operator== or operator< are already defined

// Ideally, those operators are automatically(!) marked constexpr if the called operator is constexpr too
// This may be doable with some template magic, but for now the process is manual


// All the macros in the form "cop_gen_<op>_from_<op>" have two parameters; 
// the first one is the type that needs to be passed to the operator, the second is the inline/friend/constexpr function modifier.
// You can define in C++ the comparison operator in 3 different ways:
// - as free   functions. Those should be marked inline or inline constexpr
// - as friend functions. Those should be marked friend or friend constexpr (inline can be omitted).
// - as member functions. Those should be avoided (prefer friend functions) and cannot be generated with the provided macros
//    notice that operator< and operator== used for genereting the other functions can be member functions
// Since all generate operators use the < operator (or ==), there is no reason not to generate the other operators as free functions.
//
// The macros in the form "cop_gen_<op>_from_<op>_2" take three parameters.
// The first two parameters are the types to be passed to the defined functions, the third parameter is the function modifier.
//
// If you prefer to avoid macros in your code base, you can generate the comparison operators using CRTP.
// The class "less_comparable" and "less_comparable_constexpr" implements all other operators based on <, whereas 
// "equal_comparable" and "equal_comparable_constexpr". In this case all operators are defined as friend functions.
namespace cop{

	// All macros ending with "_i" are for internal usage, you should not need to use them directly
	#if defined(cop_gen_greaterthan_op_fromlessthan_i) || defined(cop_gen_lesseqthan_op_fromlessthan_i) || \
	    defined(cop_gen_gretaereqthan_op_fromlessthan_i) || defined(cop_gen_eq_op_fromlessthan_i) || \
	    defined(cop_gen_uneq_op_fromlessthan_i) || defined(cop_gen_uneq_op_fromeq_i)
		#error "internal macro already defined"
	#endif
	#define cop_gen_greaterthan_op_fromlessthan_i(t1, t2, m)   m bool operator> (const t1& lhs, const t2& rhs)noexcept(noexcept(rhs < lhs)){return  (rhs < lhs);}
	#define cop_gen_lesseqthan_op_fromlessthan_i(t1, t2, m)    m bool operator<=(const t1& lhs, const t2& rhs)noexcept(noexcept(rhs < lhs)){return !(rhs < lhs);}
	#define cop_gen_gretaereqthan_op_fromlessthan_i(t1, t2, m) m bool operator>=(const t1& lhs, const t2& rhs)noexcept(noexcept(lhs < rhs)){return !(lhs < rhs);}
	#define cop_gen_eq_op_fromlessthan_i(t1, t2, m)            m bool operator==(const t1& lhs, const t2& rhs)noexcept(noexcept(rhs < lhs) && noexcept(lhs < rhs)){return !(rhs < lhs) && !(lhs < rhs);}
	#define cop_gen_uneq_op_fromlessthan_i(t1, t2, m)          m bool operator!=(const t1& lhs, const t2& rhs)noexcept(noexcept(rhs < lhs) && noexcept(lhs < rhs)){return  (lhs < rhs) ||  (rhs < lhs);}

	#define cop_gen_uneq_op_fromeq_i(t1, t2, m)	m bool operator!=(const t1& lhs, const t2& rhs) noexcept(noexcept(rhs == lhs)) {return !(rhs == lhs);}


	/// Macros for defining the <, >=, <=, == and != operators using the < operator
	#if defined(cop_gen_greaterthan_op_fromlessthan) || defined(cop_gen_lesseqthan_op_fromlessthan) || \
	    defined(cop_gen_gretaereqthan_op_fromlessthan) || defined(cop_gen_eq_op_fromlessthan) || \
	    defined(cop_gen_uneq_op_fromlessthan)
		#error "one of the cop macro has already been defined"
	#endif
	#define cop_gen_greaterthan_op_fromlessthan(t, m)   cop_gen_greaterthan_op_fromlessthan_i(t,t,m)
	#define cop_gen_lesseqthan_op_fromlessthan(t, m)    cop_gen_lesseqthan_op_fromlessthan_i(t,t,m)
	#define cop_gen_gretaereqthan_op_fromlessthan(t, m) cop_gen_gretaereqthan_op_fromlessthan_i(t,t,m)
	#define cop_gen_eq_op_fromlessthan(t, m)            cop_gen_eq_op_fromlessthan_i(t,t,m)
	#define cop_gen_uneq_op_fromlessthan(t, m)          cop_gen_uneq_op_fromlessthan_i(t,t,m)

	#if defined(cop_gen_ordering_ops_fromlessthan)
		#error "one of the cop macro has already been defined"
	#endif
	#define cop_gen_ordering_ops_fromlessthan(t,m)\
		cop_gen_greaterthan_op_fromlessthan(t,m)\
		cop_gen_lesseqthan_op_fromlessthan(t,m)\
		cop_gen_gretaereqthan_op_fromlessthan(t,m)\
		cop_gen_eq_op_fromlessthan(t,m)\
		cop_gen_uneq_op_fromlessthan(t,m)

	// operators for comparing different types are also supported
	#if defined(cop_gen_greaterthan_op_fromlessthan_2) || defined(cop_gen_lesseqthan_op_fromlessthan_2) || \
	    defined(cop_gen_gretaereqthan_op_fromlessthan_2) || defined(cop_gen_eq_op_fromlessthan_2) || \
	    defined(cop_gen_uneq_op_fromlessthan_2)
		#error "one of the cop macro has already been defined"
	#endif
	#define cop_gen_greaterthan_op_fromlessthan_2(t1, t2, m)   cop_gen_greaterthan_op_fromlessthan_i(t1,t2,m) cop_gen_greaterthan_op_fromlessthan_i(t2,t1,m)
	#define cop_gen_lesseqthan_op_fromlessthan_2(t1, t2, m)    cop_gen_lesseqthan_op_fromlessthan_i(t1,t2,m) cop_gen_lesseqthan_op_fromlessthan_i(t2,t1,m)
	#define cop_gen_gretaereqthan_op_fromlessthan_2(t1, t2, m) cop_gen_gretaereqthan_op_fromlessthan_i(t1,t2,m) cop_gen_gretaereqthan_op_fromlessthan_i(t2,t1,m)
	#define cop_gen_eq_op_fromlessthan_2(t1, t2, m)            cop_gen_eq_op_fromlessthan_i(t1,t2,m) cop_gen_eq_op_fromlessthan_i(t2,t1,m)
	#define cop_gen_uneq_op_fromlessthan_2(t1, t2, m)          cop_gen_uneq_op_fromlessthan_i(t1,t2,m) cop_gen_uneq_op_fromlessthan_i(t2,t1,m)


	template<typename T> class less_comparable {
		cop_gen_ordering_ops_fromlessthan(T, friend)
	};
	template<typename T> class less_comparable_constexpr {
		cop_gen_ordering_ops_fromlessthan(T, friend constexpr)
	};

	/// Macros for defining the != operator using the == operator
	#if defined(cop_gen_uneq_op_fromeq) || defined(cop_gen_uneq_op_fromeq_2)
		#error "one of the macro generator has already been defined"
	#endif
	#define cop_gen_uneq_op_fromeq(t, m) cop_gen_uneq_op_fromeq_i(t,t,m)
	#define cop_gen_uneq_op_fromeq_2(t1, t2, m) cop_gen_uneq_op_fromeq_i(t1,t2,m) cop_gen_uneq_op_fromeq_i(t2,t1,m)

	// CRTP has the advantage that no macros are required, but:
	//  - T cannot be POD since it needs to extend this class
	//  - sizeof(T) may increase.
	//    Notice thath in most cases of single inheritance the compiler is able to reduce the size since those classes are empty/have no state.
	template<typename T> class equal_comparable {
		cop_gen_uneq_op_fromeq(T, friend)
	};
	template<typename T> class equal_comparable_constexpr {
		cop_gen_uneq_op_fromeq(T, friend constexpr)
	};

}

#endif
