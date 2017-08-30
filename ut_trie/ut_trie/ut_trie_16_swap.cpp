/**	@file ut_trie_16_swap.cpp
	@date 2016-06-27
	@version 1.0.0
	@note C++ 11/vc14
	@brief trie<> unit test for swap method.
	*/

#include "ut_trie.hpp"
#include <boost/test/auto_unit_test.hpp>
#include <boost/lexical_cast.hpp>



#if TEST_PHASE >= 41
using mapped_t = int;
using vector_t = std::vector<mapped_t>;
using trie_t = trie<mapped_t>;
using value_t = trie_t::value_type;
using key_t = trie_t::key_type;
using map_t = std::map<key_t, mapped_t>;

static auto kt = [](mapped_t k)->key_t { return boost::lexical_cast<key_t>(k); };
static auto mv = [&](mapped_t x)->value_t { return std::make_pair(kt(x), x); };



/** Test trie<T>::swap() */
BEGIN_PHASE(41, ut_swap_empty_to_empty ) {
	trie_t a, b;

	BOOST_CHECK( a.empty() );
	BOOST_CHECK( b.empty() );

	a.swap(b);

	BOOST_CHECK( a.empty() );
	BOOST_CHECK( b.empty() );
} END_PHASE()
#endif



#if TEST_PHASE >= 41
BEGIN_PHASE(41, ut_swap_pop_to_empty ) {
	map_t m;
	trie_t a, b;

	vector_t data{ 11,12,33,34,55,56,7777,7778 };
	for (auto datum : data) {
		a.insert(mv(datum));
		m.insert(mv(datum));
	}

	BOOST_CHECK(a.size() == data.size());
	BOOST_CHECK(std::equal(a.begin(), a.end(), m.begin()));

	BOOST_CHECK(b.empty());

	a.swap(b);

	BOOST_CHECK(a.empty());
	BOOST_CHECK(b.size() == m.size());
	BOOST_CHECK(std::equal(b.begin(), b.end(), m.begin()));
} END_PHASE()
#endif



#if TEST_PHASE >= 42
BEGIN_PHASE(42, ut_swap_empty_to_populated ) {
	map_t m;
	trie_t a, b;

	vector_t data{ 11,12,33,34,55,56,7777,7778 };
	for (auto datum : data) {
		a.insert(mv(datum));
		m.insert(mv(datum));
	}

	BOOST_CHECK(a.size() == m.size());
	BOOST_CHECK(std::equal(a.begin(), a.end(), m.begin()));

	BOOST_CHECK(b.empty());

	b.swap(a);

	BOOST_CHECK(a.empty());
	BOOST_CHECK(b.size() == m.size());
	BOOST_CHECK(std::equal(b.begin(), b.end(), m.begin()));
} END_PHASE()
#endif




#if TEST_PHASE >= 43
BEGIN_PHASE(43, ut_swap_populated_to_populated ) {
	map_t mA, mB;
	trie_t tA, tB;

	vector_t va{ 11,12,33,34,55,56,7777,7778 };
	vector_t vb{ 113,132,133,134,545,546,57777,57778 };

	for (auto a : va) {
		tA.insert(mv(a));
		mA.insert(mv(a));
	}

	for (auto b : vb) {
		mB.insert(mv(b));
		tB.insert(mv(b));
	}

	BOOST_CHECK(tA.size() == mA.size());
	BOOST_CHECK(std::equal(tA.begin(), tA.end(), mA.begin()));

	BOOST_CHECK(tB.size() == mB.size());
	BOOST_CHECK(std::equal(tB.begin(), tB.end(), mB.begin()));

	tA.swap(tB);

	BOOST_CHECK(tA.size() == mB.size());
	BOOST_CHECK(std::equal(tA.begin(), tA.end(), mB.begin()));

	BOOST_CHECK(tB.size() == mA.size());
	BOOST_CHECK(std::equal(tB.begin(), tB.end(), mA.begin()));
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