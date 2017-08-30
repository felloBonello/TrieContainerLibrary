/**	@file ut_trie_14_erase_range.cpp
	@date 2016-06-27
	@version 1.0.0
	@note C++ 11/vc14
	@brief trie<> unit test for erase a range of elements.
	*/

#include "ut_trie.hpp"
#include <boost/test/auto_unit_test.hpp>
#include <boost/lexical_cast.hpp>



/** Test trie<int>::erase() of a list of scrambled integers. */
#if TEST_PHASE >= 39
BEGIN_PHASE(39, test_erase_range ) {

	using mapped_t = int;
	using vector_t = std::vector<mapped_t>;
	using trie_t = trie<mapped_t>;
	using value_t = trie_t::value_type;
	using key_t = trie_t::key_type;
	using map_t = std::map<key_t, mapped_t>;

	vector_t data{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	vector_t nextData{ 1, 2, 9, 10 };

	map_t mData, mNextData;
	for (auto datum : data)
		mData.insert(value_t(boost::lexical_cast<key_t>(datum), datum));
	for (auto datum : nextData)
		mNextData.insert(value_t(boost::lexical_cast<key_t>(datum), datum));

	trie_t t;
	for (auto datum : mData)
		t.insert(datum);

	auto b = std::find(t.begin(), t.end(), value_t(boost::lexical_cast<key_t>(3), 3));
	auto e = std::find(t.begin(), t.end(), value_t(boost::lexical_cast<key_t>(9), 9));
	auto r = t.erase(b, e);
	BOOST_CHECK(std::equal(t.begin(), t.end(), mNextData.begin()));
	BOOST_CHECK(r->second == 9);
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