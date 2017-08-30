/**	@file ut_trie_24_relational.cpp
	@date 2016-06-27
	@version 1.0.0
	@note C++ 11/vc14
	@brief trie<> unit test for typedefs.
	*/


#define _SCL_SECURE_NO_WARNINGS
#include "ut_trie.hpp"
#include <boost/test/auto_unit_test.hpp>
#include <boost/lexical_cast.hpp>



#if TEST_PHASE >= 68
using mapped_t = int;
using trie_t = trie<mapped_t>;
using value_t = trie_t::value_type;
using key_t = trie_t::key_type;


static auto kt = [](mapped_t k)->key_t { return boost::lexical_cast<key_t>(k); };
static auto mv = [&](mapped_t x)->value_t { return std::make_pair(kt(x), x); };
static auto vt = [&](mapped_t k, mapped_t v)->value_t { return std::make_pair(kt(k), v); };



BEGIN_PHASE(68, test_compare_equal ) {
	trie_t lhs{ mv(1), mv(2), mv(3), mv(4), mv(5), mv(6), mv(7), mv(8), mv(9) };
	auto rhs(lhs);

	BOOST_CHECK(lhs == rhs);
	BOOST_CHECK(lhs <= rhs);
	BOOST_CHECK(lhs >= rhs);
} END_PHASE()
#endif



#if TEST_PHASE >= 69
BEGIN_PHASE(69, test_compare_not_equal ) {
	trie_t lhs{ mv(1), mv(2), mv(3), mv(4), mv(5), mv(6), mv(7), mv(8) };
	trie_t rhs{ mv(1), mv(2), mv(3), mv(4), mv(5), mv(6), mv(7), mv(8), mv(9) };

	BOOST_CHECK(lhs != rhs);
	lhs.insert(mv(9));
	BOOST_CHECK(lhs == rhs);
	lhs.insert(mv(10));
	BOOST_CHECK(lhs != rhs);

	rhs.insert(mv(10));
	BOOST_CHECK(lhs == rhs);

	rhs.erase(kt(5));
	rhs.insert(mv(55));
	BOOST_CHECK(lhs != rhs);
} END_PHASE()
#endif



#if TEST_PHASE >= 70
BEGIN_PHASE(70, test_compare_ordered) {
	trie_t lhs{ mv(1), mv(2), mv(3), mv(4), mv(55), mv(6), mv(7), mv(8), mv(9) };
	trie_t rhs{ mv(1), mv(22), mv(3), mv(4), mv(54), mv(6), mv(7), mv(8), mv(9) };

	BOOST_CHECK(lhs < rhs);
	BOOST_CHECK(lhs <= rhs);
	BOOST_CHECK(!(lhs > rhs));
	BOOST_CHECK(!(lhs >= rhs));

	BOOST_CHECK(!(rhs < lhs));
	BOOST_CHECK(!(rhs <= lhs));
	BOOST_CHECK(rhs > lhs);
	BOOST_CHECK(rhs >= lhs);
} END_PHASE()
#endif



/*============================================================================

Revision History

Version 1.0.0: 2016-06-27

==============================================================================
Copyright Garth Santor, 2016

The copyright to the computer program(s) herein
is the property of Garth Santor, Canada.
The program(s) may be used and/or copied only with
the written permission of Garth Santor
or in accordance with the terms and conditions
stipulated in the agreement/contract under which
the program(s) have been supplied.
============================================================================*/