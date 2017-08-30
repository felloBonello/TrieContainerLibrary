/** @file ut_trie_10_insert_rvalue.cpp
	@author Garth Santor
	@date 2016-06-25
	@version 1.0.0
	@note C++ 11/vc14
	@brief trie<> unit test for R-value insert method.
	*/

#include "ut_trie.hpp"
#include <boost/test/auto_unit_test.hpp>
#include <boost/lexical_cast.hpp>
#include <vector>



/** Test trie<int>::insert() using an R-value parameter. */
#if TEST_PHASE >= 33
BEGIN_PHASE(33, ut_Rvalue_insert_scrambled_int) {
	using mapped_t = std::unique_ptr<int>;
	using trie_t = trie<mapped_t>;
	std::vector<int> data{ 9, 10, 7, 8, 5, 6, 3, 4, 1, 2 };
	trie_t t;
	for (auto datum : data) {
		auto k = boost::lexical_cast<trie_t::key_type>(datum);
		t.insert(std::make_pair(k, mapped_t(new int(datum))));
	}

	std::sort(data.begin(), data.end());
	std::vector<int> dup;
	for (auto& e : t) {
		dup.push_back(*e.second);
	}

	std::sort(data.begin(), data.end());
	std::sort(dup.begin(), dup.end());
	BOOST_CHECK(dup.size() == data.size());
	BOOST_CHECK_EQUAL_COLLECTIONS(dup.begin(), dup.end(), data.begin(), data.end());
} END_PHASE()
#endif



/*============================================================================

Revision History

Version 1.0.0: 2016-06-25

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