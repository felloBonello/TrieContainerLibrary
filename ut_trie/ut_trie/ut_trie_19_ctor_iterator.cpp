/**	@file ut_trie_19_ctor_iterator.cpp
	@date 2016-06-27
	@version 1.0.0
	@note C++ 11/vc14
	@brief trie<> unit test for iterator constructor.
	*/

#include "ut_trie.hpp"
#include <boost/test/auto_unit_test.hpp>
#include <boost/lexical_cast.hpp>



#if TEST_PHASE >= 52
using mapped_t = int;
using vector_t = std::vector<mapped_t>;
using trie_t = trie<mapped_t>;
using value_t = trie_t::value_type;
using key_t = trie_t::key_type;
using map_t = std::map<key_t, mapped_t>;

static auto kt = [](mapped_t k)->key_t { return boost::lexical_cast<key_t>(k); };
static auto mv = [&](mapped_t x)->value_t { return std::make_pair(kt(x), x); };



/** Test trie<T>::trie(iter,iter) */
BEGIN_PHASE(52, ut_ctor_iterator_empty) {
	map_t m;
	trie_t s(m.begin(), m.end());

	BOOST_CHECK(std::equal(s.begin(), s.end(), m.begin()));
	BOOST_CHECK(s.empty());
	BOOST_CHECK(s.size() == m.size());
} END_PHASE()
#endif



/** Test trie<T>::trie(iter,iter) */
#if TEST_PHASE >= 53
BEGIN_PHASE(53, ut_ctor_iterator_iterator) {
	std::vector<int> data{ 1, 9, 2, 10, 3, 12, 4, 11, 5, 6, 7, 8 };
	map_t m;
	for (auto datum : data)
		m.insert(mv(datum));

	trie_t s(m.begin(), m.end());

	BOOST_CHECK(std::equal(s.begin(), s.end(), m.begin()));
	BOOST_CHECK(!s.empty());
	BOOST_CHECK(s.size() == m.size());
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