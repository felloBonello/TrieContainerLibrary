/**	@file ut_trie_12_insert_initializer_list.cpp
	@date 2016-06-27
	@version 1.0.0
	@note C++ 11/vc14
	@brief trie<> unit test for inserting an initializer list.
	*/

#include "ut_trie.hpp"
#include <boost/test/auto_unit_test.hpp>
#include <boost/lexical_cast.hpp>
	
	

/** Test trie<int>::insert() of an initializer list to an empty square list. */
#if TEST_PHASE >= 36
BEGIN_PHASE(36, test_insert_initializer_to_empty ) {
	using mapped_t = int;
	using trie_t = trie<mapped_t>;
	using value_t = trie_t::value_type;
	using key_t = trie_t::key_type;
	using map_t = std::map<key_t, mapped_t>;

#define LIST { value_t("9",9), value_t("10",10), value_t("7",7), value_t("8",8), value_t("5",5), value_t("6",6), value_t("3",3), value_t("4",4), value_t("1",1), value_t("2",2) }
	map_t m = LIST;
	trie_t t;

	t.insert(LIST);

	BOOST_CHECK( t.size() == m.size() );
	BOOST_CHECK( std::equal( t.begin(), t.end(), m.begin() ) );
#undef LIST
} END_PHASE()
#endif



/** Test trie<int>::insert() of an initializer list to a populated square list. */
#if TEST_PHASE >= 37
BEGIN_PHASE(37, test_insert_initializer_to_populated ) {

	using mapped_t = int;
	using trie_t = trie<mapped_t>;
	using value_t = trie_t::value_type;
	using key_t = trie_t::key_type;
	using map_t = std::map<key_t, mapped_t>;

#define LISTA { value_t("aa",1), value_t("ac",2), value_t("ae",3), value_t("aef",4), value_t("aeh",5), value_t("zz",6) }
#define LISTB { value_t("a",7), value_t("ab",84), value_t("aea",9), value_t("zza",10) }

	map_t m = LISTA;
	m.insert(LISTB);

	trie_t t;

	t.insert(LISTA);
	t.insert(LISTB);

	BOOST_CHECK( t.size() == m.size() );
	BOOST_CHECK( std::equal( t.begin(), t.end(), m.begin() ) );

#undef LISTA
#undef LISTB
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