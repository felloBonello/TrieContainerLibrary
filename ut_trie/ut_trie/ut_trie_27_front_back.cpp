/**	@file ut_trie_27_front_back.cpp
	@date 2016-06-27
	@version 1.0.0
	@note C++ 11/vc14
	@brief trie<> unit test for swap method.
	*/

#include "ut_trie.hpp"
#include <boost/test/auto_unit_test.hpp>
#include <boost/lexical_cast.hpp>



#if TEST_PHASE >= 78
using mapped_t = int;
using trie_t = trie<mapped_t>;
using value_t = trie_t::value_type;
using key_t = trie_t::key_type;
using map_t = std::map<key_t, mapped_t>;


static auto kt = [](mapped_t k)->key_t { return boost::lexical_cast<key_t>(k); };
static auto mv = [&](mapped_t x)->value_t { return std::make_pair(kt(x), x); };
static auto vt = [&](mapped_t k, mapped_t v)->value_t { return std::make_pair(kt(k), v); };



/** Test trie<T>::front() */
BEGIN_PHASE(78, ut_front_back_singleton) {
	trie_t t{ mv(1) };
	BOOST_CHECK_EQUAL(t.front().second, 1);
	BOOST_CHECK_EQUAL(t.back().second, 1);
} END_PHASE()
#endif



#if TEST_PHASE >= 79
BEGIN_PHASE(79, ut_front_back_multi) {
	trie_t t{ mv(1), mv(2), mv(3) };
	BOOST_CHECK_EQUAL(t.front().second, 1);
	BOOST_CHECK_EQUAL(t.back().second, 3);
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