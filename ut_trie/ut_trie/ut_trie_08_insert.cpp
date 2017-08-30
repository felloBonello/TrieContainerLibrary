/** @file ut_trie_08_insert.cpp
	@author Garth Santor
	@date 2016-06-24
	@version 1.0.0
	@note C++ 11/vc14
	@brief trie<> unit test for insert.
	*/

#include "ut_trie.hpp"
#include <boost/test/auto_unit_test.hpp>
#include <boost/lexical_cast.hpp>




/** Test trie<>::insert() of a list of scrambled words. */
#if TEST_PHASE >= 31
BEGIN_PHASE(31, ut_insert_scrambled_int) {
	using mapped_t = std::string;
	using vector_t = std::vector<mapped_t>;
	using trie_t = trie<mapped_t>;
	using key_t = trie_t::key_type;
	using map_t = std::map<key_t, mapped_t>;

	vector_t data{ "nine", "ten", "seven", "eight", "five", "six", "three", "four", "one", "two" };
	map_t m;
	trie_t t;
	for (auto datum : data) {
		t.insert(trie_t::value_type(datum, datum));
		m.insert(map_t::value_type(datum, datum));
	}

	BOOST_CHECK(std::equal(t.begin(), t.end(), m.begin()));
	BOOST_CHECK(t.size() == m.size());
} END_PHASE()
#endif



/** Test trie<>::insert() an existing element. */
#if TEST_PHASE >= 32
BEGIN_PHASE(32, ut_insert_existing_words) {
	using mapped_t = std::string;
	using vector_t = std::vector<mapped_t>;
	using trie_t = trie<mapped_t>;
	using key_t = trie_t::key_type;
	using map_t = std::map<key_t, mapped_t>;

	vector_t data{ "nine", "ten", "seven", "eight", "five", "six", "three", "four", "one", "two" };
	map_t m;
	trie_t t;
	for (auto datum : data) {
		t.insert(trie_t::value_type(datum, datum));
		m.insert(map_t::value_type(datum, datum));
}

	BOOST_CHECK(std::equal(t.begin(), t.end(), m.begin()));
	BOOST_CHECK(t.size() == m.size());

	for (auto datum : data) {
		auto dupLoc = t.insert(std::make_pair(datum, mapped_t("asdf")));
		BOOST_CHECK_EQUAL(dupLoc.second, false);
		BOOST_CHECK_EQUAL(dupLoc.first->first, datum);
		BOOST_CHECK_EQUAL(dupLoc.first->second, datum);
	}
} END_PHASE()
#endif



/*============================================================================

Revision History

Version 1.0.0: 2016-06-24

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