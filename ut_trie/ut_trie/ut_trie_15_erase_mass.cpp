/**	@file ut_trie_15_erase_mass.cpp
	@date 2016-06-27
	@version 1.0.0
	@note C++ 11/vc14
	@brief trie<> unit test for erase a range of elements.
	*/



#include "ut_trie.hpp"
#include <boost/test/auto_unit_test.hpp>
#include <boost/lexical_cast.hpp>
#include <map>


/** Test trie<int>::erase(key) of a list of integers. */
#if TEST_PHASE >= 40
BEGIN_PHASE(40, test_erase_mass ) {
	using mapped_t = int;
	using vector_t = std::vector<mapped_t>;
	using trie_t = trie<mapped_t>;
	using value_t = trie_t::value_type;
	using key_t = trie_t::key_type;
	using map_t = std::map<key_t, mapped_t>;

	auto kt = [](mapped_t k)->key_t { return boost::lexical_cast<key_t>(k); };
	auto mv = [&](mapped_t x)->value_t { return std::make_pair(kt(x), x); };
	

	map_t data{ mv(1), mv(2), mv(3), mv(4), mv(5), mv(6), mv(7), mv(8), mv(9), mv(10) };

	trie<int> s;
	for (auto datum : data)
		s.insert(datum);

	auto nListErased = s.erase(kt(1));
	auto nSetErased = data.erase(kt(1));
	BOOST_CHECK_EQUAL(nListErased, nSetErased);
	BOOST_CHECK(std::equal(s.begin(), s.end(), data.begin()));

	nListErased = s.erase(kt(4));
	nSetErased = data.erase(kt(4));
	BOOST_CHECK_EQUAL(nListErased, nSetErased);
	BOOST_CHECK(std::equal(s.begin(), s.end(), data.begin()));

	nListErased = s.erase(kt(10));
	nSetErased = data.erase(kt(10));
	BOOST_CHECK_EQUAL(nListErased, nSetErased);
	BOOST_CHECK(std::equal(s.begin(), s.end(), data.begin()));

	nListErased = s.erase(kt(11));
	nSetErased = data.erase(kt(11));
	BOOST_CHECK_EQUAL(nListErased, nSetErased);
	BOOST_CHECK(std::equal(s.begin(), s.end(), data.begin()));
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