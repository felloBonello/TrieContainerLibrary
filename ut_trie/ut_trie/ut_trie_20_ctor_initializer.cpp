/**	@file ut_trie_20_ctor_initializer.cpp
	@date 2016-06-27
	@version 1.0.0
	@note C++ 11/vc14
	@brief trie<> unit test for iterator constructor.
	*/

#define _SCL_SECURE_NO_WARNINGS
#include "ut_trie.hpp"
#include <boost/test/auto_unit_test.hpp>
#include <boost/lexical_cast.hpp>
#include <map>



#if TEST_PHASE >= 54
using mapped_t = int;
using vector_t = std::vector<mapped_t>;
using trie_t = trie<mapped_t>;
using value_t = trie_t::value_type;
using key_t = trie_t::key_type;
using map_t = std::map<key_t, mapped_t>;



/** Test trie<T>::trie(iter,iter) */
BEGIN_PHASE(54, ut_ctor_initializer_int) {
	map_t a{ value_t("1",1), value_t("2",2), value_t("3",3) };
	trie_t s{ value_t("1",1), value_t("2",2), value_t("3",3) };

	BOOST_CHECK(std::equal(s.begin(), s.end(), a.begin()));

	BOOST_CHECK_EQUAL(s.empty(), false);
	BOOST_CHECK_EQUAL(s.size(), a.size());
} END_PHASE()
#endif



/** Test trie<T>::trie(iter,iter) */
#if TEST_PHASE >= 55
BEGIN_PHASE(55, ut_ctor_initializer_empty) {
	map_t a{};
	trie_t s{};

	BOOST_CHECK(std::equal(s.begin(), s.end(), a.begin()));

	BOOST_CHECK_EQUAL(s.empty(), true);
	BOOST_CHECK_EQUAL(s.size(), a.size());
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