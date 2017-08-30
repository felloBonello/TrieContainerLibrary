/**	@file ut_trie_18_ctor_Rvalue.cpp
	@date 2016-06-27
	@version 1.0.0
	@note C++ 11/vc14
	@brief trie<> unit test for an R-value constructor.
	*/


#define _SCL_SECURE_NO_WARNINGS
#include "ut_trie.hpp"
#include <boost/test/auto_unit_test.hpp>
#include <boost/lexical_cast.hpp>



/** Test trie<T>::trie(trie &&) */
#if TEST_PHASE >= 48
BEGIN_PHASE(48, ut_ctor_Rvalue_empty ) {
	trie<double> s;
	decltype(s) copy(std::move(s));
	BOOST_CHECK(s.empty());
	BOOST_CHECK(std::equal(s.begin(), s.end(), copy.begin()));
	BOOST_CHECK(copy.empty());
	BOOST_CHECK(copy.size() == s.size());
} END_PHASE()
#endif



#if TEST_PHASE >= 49
BEGIN_PHASE(49, ut_ctor_Rvalue_singleton ) {
	trie<double> s;
	s["3.14"] = 3.14;
	decltype(s) copy = std::move(s);				// this invokes copy construction

	BOOST_CHECK(s.empty());
	BOOST_CHECK(!copy.empty());
	BOOST_CHECK(copy.size() == 1);
	BOOST_CHECK(copy.begin()->second == 3.14);
} END_PHASE()
#endif



#if TEST_PHASE >= 50
BEGIN_PHASE(50, ut_ctor_Rvalue_small ) {
	trie<double> s;
	for (int i = 0; i < 10; ++i)
		s[boost::lexical_cast<decltype(s)::key_type>(i)] = i;

	decltype(s) copy(std::move(s));
	BOOST_CHECK(s.empty());
	BOOST_CHECK(!copy.empty());
	BOOST_CHECK(copy.size() == 10);

	// this should crash if you didn't write your copy constructor properly
	while (!copy.empty())
		copy.erase(copy.begin());
} END_PHASE()
#endif



#if TEST_PHASE >= 51
BEGIN_PHASE(51, ut_ctor_Rvalue_strings ) {
	std::vector<std::string> words{ "one", "two", "three", "four", "five" };
	trie<std::string> sorted;
	for (auto word : words)
		sorted[word] = word;

	std::sort(words.begin(), words.end());
	decltype(sorted) copy(std::move(sorted));
	BOOST_CHECK(sorted.empty());
	BOOST_CHECK(std::equal(sorted.begin(), sorted.end(), copy.begin()));
	BOOST_CHECK(!copy.empty());
	BOOST_CHECK(copy.size() == words.size());

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