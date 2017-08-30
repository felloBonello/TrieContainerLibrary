/**	@file ut_trie_11_insert_range.cpp
	@date 2016-06-27
	@version 1.0.0
	@note C++ 11/vc14
	@brief trie<> unit test for inserting a range of elements.
	*/

#include "ut_trie.hpp"
#include <boost/test/auto_unit_test.hpp>
#include <boost/lexical_cast.hpp>
#include <vector>
#include <map>


#if TEST_PHASE >= 34
using mapped_t = int;
using vector_t = std::vector<mapped_t>;
using trie_t = trie<mapped_t>;
using key_t = trie_t::key_type;
using map_t = std::map<key_t, mapped_t>;



/** Test trie<int>::insert() of a iterator defined range. */
BEGIN_PHASE(34, ut_insert_range_to_empty ) {

	vector_t a{ 9, 10, 7, 8, 5, 6, 3, 4, 1, 2 };
	map_t m;
	for (auto e : a)
		m[boost::lexical_cast<key_t>(e)] = e;

	trie_t t;
	t.insert( m.begin(), m.end() );

	BOOST_CHECK( t.size() == m.size() );
	BOOST_CHECK( std::equal( t.begin(), t.end(), m.begin() ) );
} END_PHASE()
#endif




#if TEST_PHASE >= 35
BEGIN_PHASE(35, test_insert_range_to_populated ) {

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


	ma.insert(mb.begin(), mb.end());
	ta.insert(tb.begin(), tb.end());

	BOOST_CHECK(ma.size() == ta.size());
	BOOST_CHECK(std::equal(ta.begin(), ta.end(), ma.begin()));
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