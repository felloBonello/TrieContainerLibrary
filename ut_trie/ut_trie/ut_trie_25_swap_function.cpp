/**	@file ut_trie_25_swap_function.cpp
	@date 2016-06-27
	@version 1.0.0
	@note C++ 11/vc14
	@brief trie<> unit test for swap method.
	*/

#include "ut_trie.hpp"
#include <boost/test/auto_unit_test.hpp>
#include <boost/lexical_cast.hpp>
#include <map>



#if TEST_PHASE >= 71
using mapped_t = int;
using trie_t = trie<mapped_t>;
using value_t = trie_t::value_type;
using key_t = trie_t::key_type;
using map_t = std::map<key_t, mapped_t>;


static auto kt = [](mapped_t k)->key_t { return boost::lexical_cast<key_t>(k); };
static auto mv = [&](mapped_t x)->value_t { return std::make_pair(kt(x), x); };
static auto vt = [&](mapped_t k, mapped_t v)->value_t { return std::make_pair(kt(k), v); };



/** Test trie<T>::swap() */
BEGIN_PHASE(71, ut_swapf_empty_to_empty ) {
	trie_t a, b;

	BOOST_CHECK( a.empty() );
	BOOST_CHECK( b.empty() );

	std::swap(a, b);

	BOOST_CHECK( a.empty() );
	BOOST_CHECK( b.empty() );
} END_PHASE()
#endif



#if TEST_PHASE >= 72
BEGIN_PHASE(72, ut_swapf_pop_to_empty ) {
	trie_t a{ mv(1),mv(2),mv(3) }, b;
	map_t m(a.begin(), a.end());

	BOOST_CHECK_EQUAL(a.size(), 3);
	BOOST_CHECK(std::equal(a.begin(), a.end(), m.begin()));

	BOOST_CHECK(b.empty());

	std::swap(a, b);

	BOOST_CHECK(a.empty());
	BOOST_CHECK_EQUAL(b.size(), m.size());
	BOOST_CHECK(std::equal(b.begin(), b.end(), m.begin()));
} END_PHASE()
#endif

//
//
//#if TEST_PHASE >= 73
//BEGIN_PHASE(73, ut_swapf_empty_to_populated ) {
//	trie_t a{ mv(1),mv(2),mv(3) }, b;
//	map_t m(a.begin(), a.end());
//
//	BOOST_CHECK_EQUAL(a.size(), m.size());
//	BOOST_CHECK(std::equal(a.begin(), a.end(), m.begin()));
//
//	BOOST_CHECK(b.empty());
//
//	std::swap(b, a);
//
//	BOOST_CHECK(a.empty());
//	BOOST_CHECK_EQUAL(b.size(), m.size());
//	BOOST_CHECK(std::equal(b.begin(), b.end(), m.begin()));
//} END_PHASE()
//#endif
//
//
//
//#if TEST_PHASE >= 74
//BEGIN_PHASE(74, ut_swapf_populated_to_populated ) {
//	trie_t a{ mv(1),mv(2),mv(3) }, b{ mv(4),mv(5) };
//	map_t ma(a.begin(), a.end()), mb(b.begin(), b.end());
//
//	BOOST_CHECK(a.size() == ma.size());
//	BOOST_CHECK(std::equal(a.begin(), a.end(), ma.begin()));
//
//	BOOST_CHECK(b.size() == mb.size());
//	BOOST_CHECK(std::equal(b.begin(), b.end(), mb.begin()));
//
//	std::swap(a, b);
//
//	BOOST_CHECK(a.size() == mb.size());
//	BOOST_CHECK(std::equal(a.begin(), a.end(), mb.begin()));
//
//	BOOST_CHECK(b.size() == ma.size());
//	BOOST_CHECK(std::equal(b.begin(), b.end(), ma.begin()));
//} END_PHASE()
//#endif



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