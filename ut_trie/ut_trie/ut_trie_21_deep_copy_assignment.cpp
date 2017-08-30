/**	@file ut_trie_21_deep_copy_assignment.cpp
	@date 2016-06-27
	@version 1.0.0
	@note C++ 11/vc14
	@brief trie<> unit test for assignment.
	*/

#define _SCL_SECURE_NO_WARNINGS
#include "ut_trie.hpp"
#include <boost/test/auto_unit_test.hpp>
#include <boost/lexical_cast.hpp>
#include <map>



#if TEST_PHASE >= 56
using mapped_t = int;
using vector_t = std::vector<mapped_t>;
using trie_t = trie<mapped_t>;
using value_t = trie_t::value_type;
using key_t = trie_t::key_type;
using map_t = std::map<key_t, mapped_t>;


static auto kt = [](mapped_t k)->key_t { return boost::lexical_cast<key_t>(k); };
static auto mv = [&](mapped_t x)->value_t { return std::make_pair(kt(x), x); };



/** Test trie<T>::operator=() */
BEGIN_PHASE(56, ut_copy_assignment_empty ) {
	trie<double> s, t;
	t = s;
	BOOST_CHECK(std::equal(s.begin(), s.end(), t.begin()));
	BOOST_CHECK_EQUAL(t.empty(), true);
	BOOST_CHECK_EQUAL(t.size(), s.size());
} END_PHASE()
#endif



#if TEST_PHASE >= 57
BEGIN_PHASE(57, ut_copy_assignment_singleton ) {
	trie<double> s, t;
	s["3.14"] = 3.14;
	t = s;

	s.erase(s.begin());
	BOOST_CHECK(s.empty());
	BOOST_CHECK_EQUAL(t.empty(), false);
	BOOST_CHECK_EQUAL(t.size(), 1);
	BOOST_CHECK_EQUAL(t.begin()->second, 3.14);

} END_PHASE()
#endif



#if TEST_PHASE >= 58
BEGIN_PHASE(58, ut_copy_assignment_small ) {
	trie<double> s, t;
	for (int i = 0; i < 10; ++i)
		s[kt(i)] = i;

	t = s;
	s.clear();
	BOOST_CHECK(s.empty());
	BOOST_CHECK_EQUAL(t.empty(), false);
	BOOST_CHECK_EQUAL(t.size(), 10);

	// this should crash if you didn't write your copy constructor properly
	while (!t.empty())
		t.erase(t.begin());
} END_PHASE()
#endif



#if TEST_PHASE >= 59
BEGIN_PHASE(59, ut_copy_assignment_populated_to_populated) {

	vector_t a{ 2, 4, 5, 3 };
	vector_t b{ 1, 6 };
	map_t ma, mb;
	trie_t ta, tb;

	for (auto e : a) {
		auto k = boost::lexical_cast<key_t>(e);
		ma[k] = e;
		ta[k] = e;
	}

	for (auto e : b) {
		auto k = boost::lexical_cast<key_t>(e);
		mb[k] = e;
		tb[k] = e;
	}


	BOOST_CHECK_EQUAL(ma.size(), ta.size());
	BOOST_CHECK(std::equal(ta.begin(), ta.end(), ma.begin()));

	BOOST_CHECK_EQUAL(mb.size(), tb.size());
	BOOST_CHECK(std::equal(tb.begin(), tb.end(), mb.begin()));

	ta = tb;

	BOOST_CHECK_EQUAL(ta.size(), mb.size());
	BOOST_CHECK(std::equal(ta.begin(), ta.end(), mb.begin()));

	BOOST_CHECK_EQUAL(tb.size(), mb.size());
	BOOST_CHECK(std::equal(tb.begin(), tb.end(), mb.begin()));
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