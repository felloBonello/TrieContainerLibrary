/**	@file ut_trie_13_find.cpp
	@date 2016-06-27
	@version 1.0.0
	@note C++ 11/vc14
	@brief trie<> unit test for swap method.
	*/

#include "ut_trie.hpp"
#include <boost/test/auto_unit_test.hpp>
#include <boost/lexical_cast.hpp>



#if TEST_PHASE >= 38
using mapped_t = int;
using vector_t = std::vector<mapped_t>;
using trie_t = trie<mapped_t>;
using value_t = trie_t::value_type;
using key_t = trie_t::key_type;
using map_t = std::map<key_t, mapped_t>;

static auto kt = [](mapped_t k)->key_t { return boost::lexical_cast<key_t>(k); };
static auto mv = [&](mapped_t x)->value_t { return std::make_pair(kt(x), x); };



/** Test trie<T>::find() */
BEGIN_PHASE(38, ut_find) {

	map_t data{ value_t("",-1), mv(1), mv(11), mv(12), mv(20), mv(21), mv(22), mv(333), mv(4444), mv(3434) };
	trie_t t;

	for (auto datum : data)
		t.insert(datum);

	for (auto datum : data) {
		auto tPos = t.find(datum.first);
		auto mPos = data.find(datum.first);

		BOOST_CHECK_EQUAL(tPos->second, mPos->second);
		BOOST_CHECK_EQUAL(std::distance(t.begin(), tPos), std::distance(data.begin(), mPos));
	}

	auto bad = t.find(key_t("a"));
	BOOST_CHECK(t.end() == bad);
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