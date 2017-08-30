/** @file ut_trie_07_erase_concept.cpp
	@author Garth Santor
	@date 2016-06-22
	@version 1.0.0
	@note C++ 11/vc14
	@brief trie<> unit test for reverse iterators.
	*/

#include "ut_trie.hpp"
#include <boost/test/auto_unit_test.hpp>
#include <vector>
#include <boost/lexical_cast.hpp>



/** Test trie<int>::erase() of a list of scrambled integers. */
#if TEST_PHASE >= 27
BEGIN_PHASE(27, ut_erase_scrambled_int) {
	using mapped_t = int;
	using vector_t = std::vector<mapped_t>;
	using trie_t = trie<mapped_t>;
	using key_t = trie_t::key_type;
	using map_t = std::map<key_t, mapped_t>;

	vector_t data{ 9, 10, 7, 8, 5, 6, 3, 4, 1, 2 };
	map_t m;


	trie_t t;
	for (auto datum : data) {
		auto k = boost::lexical_cast<key_t>(datum);
		t[k] = datum;
		m[k] = datum;
	}


	// remove the data from the list in the scrambled order of the first vector.
	while (!t.empty() && !m.empty()) {
		size_t idx = rand() % t.size();
		auto mLoc = m.begin();
		std::advance(mLoc, idx);
		auto tLoc = t.begin();
		std::advance(tLoc, idx);

		m.erase(mLoc);
		t.erase(tLoc);

		BOOST_CHECK(std::equal(t.cbegin(), t.cend(), m.cbegin()));
		BOOST_CHECK(t.size() == m.size());
	}
	BOOST_CHECK(t.empty());
	BOOST_CHECK(m.empty());
} END_PHASE()
#endif



//** Test square_list<int>::erase() front to back */
#if TEST_PHASE >= 28
BEGIN_PHASE(28, ut_erase_ramped_int) {
	using mapped_t = std::size_t;
	using vector_t = std::vector<mapped_t>;
	using trie_t = trie<mapped_t>;
	using key_t = trie_t::key_type;
	using map_t = std::map<key_t, mapped_t>;

	trie_t t;
	map_t m;

	size_t limit = 1000;
	for (size_t i = 0; i < limit; ++i) {
		auto k = boost::lexical_cast<key_t>(i);
		t[k] = i;
		m[k] = i;
	}

	do {
		BOOST_CHECK(std::equal(t.begin(), t.end(), m.begin()));
		BOOST_CHECK(t.size() == m.size());
		t.erase(t.begin());
		m.erase(m.begin());
	} while (!t.empty() && !m.empty());
} END_PHASE()
#endif


/** Test square_list<int>::erase() back to front. */
#if TEST_PHASE >= 29
BEGIN_PHASE(29, ut_erase_reversed_int) {
	using mapped_t = std::size_t;
	using vector_t = std::vector<mapped_t>;
	using trie_t = trie<mapped_t>;
	using key_t = trie_t::key_type;
	using map_t = std::map<key_t, mapped_t>;

	trie_t t;
	map_t m;

	size_t limit = 1000;
	for (size_t i = 0; i < limit; ++i) {
		auto k = boost::lexical_cast<key_t>(i);
		t[k] = i;
		m[k] = i;
	}

	do {
		BOOST_CHECK(std::equal(t.begin(), t.end(), m.begin()));
		BOOST_CHECK(t.size() == m.size());
		auto tLoc = t.end();
		auto mLoc = m.end();
		--tLoc;
		--mLoc;
		t.erase(tLoc);
		m.erase(mLoc);
	} while (!t.empty() && !m.empty());
} END_PHASE()
#endif


#if TEST_PHASE >= 30
BEGIN_PHASE(30, ut_erase_big_random_double) {
#if defined(NDEBUG)
	size_t limit = 10000;
#else
	size_t limit = 100;
#endif

	using mapped_t = double;
	using vector_t = std::vector<mapped_t>;
	using trie_t = trie<mapped_t>;
	using key_t = trie_t::key_type;
	using map_t = std::map<key_t, mapped_t>;

	map_t m;
	double x = -20.0;
	trie_t t;
	for (size_t i = 0; i < limit; ++i) {
		auto k = boost::lexical_cast<key_t>(x);
		m[k] = x;
		t[k] = x;
		x += 0.5;
	}

	// remove the data from the list in the scrambled order of the first vector.
	while (!t.empty() && !m.empty()) {
		size_t n = t.size();
		size_t idx = rand() % n;
		auto mLoc = m.begin();
		std::advance(mLoc, idx);
		auto tLoc = t.begin();
		std::advance(tLoc, idx);

#if defined(NDEBUG)
		if (t.size() % 1000 == 0)
			std::cout << "Size = " << t.size() << std::endl;
#endif

		m.erase(mLoc);
		t.erase(tLoc);
		BOOST_CHECK(std::equal(t.begin(), t.end(), m.begin()));
		BOOST_CHECK_EQUAL(t.size(), m.size());
	}
	BOOST_CHECK(t.empty());
	BOOST_CHECK(m.empty());
} END_PHASE()
#endif







/*============================================================================

Revision History

Version 1.0.0: 2016-06-22

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