/**	@file ut_trie_17_ctor_copy.cpp
	@date 2016-06-27
	@version 1.0.0
	@note C++ 11/vc14
	@brief trie<> unit test for a copy constructor.
	*/

#define _SCL_SECURE_NO_WARNINGS
#include "ut_trie.hpp"
#include <boost/test/auto_unit_test.hpp>
#include <boost/lexical_cast.hpp>



#if TEST_PHASE >= 44
using mapped_t = int;
using vector_t = std::vector<mapped_t>;
using trie_t = trie<mapped_t>;
using value_t = trie_t::value_type;
using key_t = trie_t::key_type;
using map_t = std::map<key_t, mapped_t>;

static auto kt = [](mapped_t k)->key_t { return boost::lexical_cast<key_t>(k); };
static auto mv = [&](mapped_t x)->value_t { return std::make_pair(kt(x), x); };



/** Test trie<T>::trie(trie const&) */
BEGIN_PHASE(44, ut_ctor_copy_empty ) {
	trie<double> s;
	decltype(s) copy( s );

	BOOST_CHECK(std::equal(s.begin(), s.end(), copy.begin()));
	BOOST_CHECK(copy.empty());
	BOOST_CHECK(copy.size() == s.size());
} END_PHASE()
#endif



#if TEST_PHASE >= 45
BEGIN_PHASE(45, ut_ctor_copy_singleton ) {
	trie<double> s;
	s["3.14"] = 3.14;
	decltype(s) copy = s;				// this invokes copy construction

	s.erase(s.begin());
	BOOST_CHECK(s.empty());
	BOOST_CHECK(!copy.empty());
	BOOST_CHECK(copy.size() == 1);
	BOOST_CHECK(copy.begin()->second == 3.14);
} END_PHASE()
#endif



#if TEST_PHASE >= 46
BEGIN_PHASE(46, ut_ctor_copy_small ) {
	trie<double> s;
	for (int i = 0; i < 10; ++i)
		s[boost::lexical_cast<key_t>(i)] = i;

	decltype(s) copy(s);
	s.clear();
	BOOST_CHECK(s.empty());
	BOOST_CHECK(!copy.empty());
	BOOST_CHECK(copy.size() == 10);

	// this should crash if you didn't write your copy constructor properly
	while (!copy.empty())
		copy.erase(copy.begin());
} END_PHASE()
#endif



#if TEST_PHASE >= 47
BEGIN_PHASE(47, ut_ctor_copy_strings ) {
	std::vector<std::string> words{ "one", "two", "three", "four", "five" };
	trie<std::string> sorted;
	for (auto word : words)
		sorted[word] = word;

	decltype(sorted) copy(sorted);
	BOOST_CHECK(std::equal(sorted.begin(), sorted.end(), copy.begin()));
	BOOST_CHECK(!copy.empty());
	BOOST_CHECK(copy.size() == sorted.size());

	// this should crash if you didn't write your copy constructor properly
	while (!copy.empty())
		copy.erase(copy.begin());
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