/**	@file ut_trie_23_initializer_assignment.cpp
	@date 2016-06-27
	@version 1.0.0
	@note C++ 11/vc14
	@brief trie<> unit test for assignment.
	*/


#include "ut_trie.hpp"
#include <boost/test/auto_unit_test.hpp>
#include <boost/lexical_cast.hpp>



#if TEST_PHASE >= 64
using mapped_t = int;
using vector_t = std::vector<mapped_t>;
using trie_t = trie<mapped_t>;
using value_t = trie_t::value_type;
using key_t = trie_t::key_type;
using map_t = std::map<key_t, mapped_t>;


static auto kt = [](mapped_t k)->key_t { return boost::lexical_cast<key_t>(k); };
static auto mv = [&](mapped_t x)->value_t { return std::make_pair(kt(x), x); };



/** Test trie<T>::operator=(std::initializer) */
BEGIN_PHASE(64, ut_assignment_initializer_empty ) {
	trie_t t;
	t = {};
	BOOST_CHECK_EQUAL(t.empty(), true);
} END_PHASE()
#endif



#if TEST_PHASE >= 65
BEGIN_PHASE(65, ut_assignment_initializer_empty_to_populated ) {
	trie_t s;
	s["11123"] = 3333;
	BOOST_CHECK_EQUAL(s.empty(), false);

	s = {};

	BOOST_CHECK_EQUAL(s.empty(), true);
} END_PHASE()
#endif



#if TEST_PHASE >= 66
BEGIN_PHASE(66, ut_assignment_initializer_populated_to_empty ) {
	trie_t t;

	t = { mv(1), mv(2), mv(3) };
	BOOST_CHECK_EQUAL(t.empty(), false);
	BOOST_CHECK_EQUAL(t.size(), 3);
} END_PHASE()
#endif



#if TEST_PHASE >= 67
BEGIN_PHASE(67, ut_assignment_initializer_populated_to_populated ) {
	trie_t a{ mv(1), mv(2), mv(3), mv(4), mv(5) };

	a = { mv(6), mv(7), mv(8), mv(9) };

	BOOST_CHECK_EQUAL(a.size(), 4);
	map_t t{ mv(6), mv(7), mv(8), mv(9) };
	BOOST_CHECK(std::equal(a.begin(), a.end(), t.begin()));
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