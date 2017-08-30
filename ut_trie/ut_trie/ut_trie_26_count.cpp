/**	@file ut_trie_26_count.cpp
	@date 2016-06-27
	@version 1.0.0
	@note C++ 11/vc14
	@brief trie<> unit test for swap method.
	*/

#include "ut_trie.hpp"
#include <boost/test/auto_unit_test.hpp>
#include <boost/lexical_cast.hpp>



#if TEST_PHASE >= 75
using mapped_t = int;
using trie_t = trie<mapped_t>;
using value_t = trie_t::value_type;
using key_t = trie_t::key_type;
using map_t = std::map<key_t, mapped_t>;


static auto kt = [](mapped_t k)->key_t { return boost::lexical_cast<key_t>(k); };
static auto mv = [&](mapped_t x)->value_t { return std::make_pair(kt(x), x); };
static auto vt = [&](mapped_t k, mapped_t v)->value_t { return std::make_pair(kt(k), v); };



/** Test trie<T>::count() */
BEGIN_PHASE(75, ut_count_empty ) {
	trie_t a;

	BOOST_CHECK(a.count("a") == 0);
} END_PHASE()
#endif



#if TEST_PHASE >= 76
BEGIN_PHASE(76, ut_count_singleton) {
	trie_t t{ mv(1) };
	BOOST_CHECK(t.count("1") == 1);
	BOOST_CHECK(t.count("2") == 0);
} END_PHASE()
#endif



#if TEST_PHASE >= 77
BEGIN_PHASE(77, ut_count_all_same) {
	trie_t t{ mv(2), mv(22), mv(23), mv(333) };
	BOOST_CHECK(t.count("2") == 3);
	BOOST_CHECK(t.count("333") == 1);
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