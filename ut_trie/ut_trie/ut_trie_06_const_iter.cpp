/** @file ut_trie_06_const_iter.cpp
	@author Garth Santor
	@date 2016-06-21
	@version 1.0.0
	@note C++ 11/vc14
	@brief trie<> unit test for constant iterators.
	*/

#include "ut_trie.hpp"
#include <boost/test/auto_unit_test.hpp>
#include <vector>
#include <boost/lexical_cast.hpp>



/** Test constant iterators */
#if TEST_PHASE >= 25
BEGIN_PHASE(25, ut_const_iterator) {
	using v_t = std::vector<int>;
	using t_t = trie<int>;
	using k_t = t_t::key_type;

	v_t v{ 1, 2, 3, 4, 5, 6, 7, 8 };
	t_t t;
	for (auto e : v)
		t[boost::lexical_cast<k_t>(e)] = e;

	auto ctp = ((t_t const&)t).begin();
	BOOST_CHECK(typeid(ctp) == typeid(trie<int>::const_iterator));
	for (auto e : v) {
		BOOST_CHECK_EQUAL(e, (ctp++)->second);
	}
	((t_t const&)t).end();
	BOOST_CHECK(ctp == ((t_t const&)t).end());

	auto actp = t.cbegin();
	BOOST_CHECK(typeid(actp) == typeid(t_t::const_iterator));
	for (auto e : v) {
		BOOST_CHECK_EQUAL(e, (actp++)->second);
	}
	BOOST_CHECK(actp == t.cend());
} END_PHASE()
#endif



/** Test constant iterators */
#if TEST_PHASE >= 26
BEGIN_PHASE(26, ut_const_reverse_iterator) {
	using v_t = std::vector<int>;
	using t_t = trie<int>;
	using k_t = t_t::key_type;

	v_t v{ 1, 2, 3, 4, 5, 6, 7, 8 };
	t_t t;
	for (auto e : v)
		t[boost::lexical_cast<k_t>(e)] = e;
	std::reverse(v.begin(), v.end());


	auto ctp = ((t_t const&)t).rbegin();
	BOOST_CHECK(typeid(ctp) == typeid(t_t::const_reverse_iterator));
	for (auto e : v) {
		BOOST_CHECK_EQUAL(e, (ctp++)->second);
	}
	BOOST_CHECK(ctp == ((t_t const&)t).rend());

	auto actp = t.crbegin();
	BOOST_CHECK(typeid(actp) == typeid(t_t::const_reverse_iterator));
	for (auto e : v) {
		BOOST_CHECK_EQUAL(e, (actp++)->second);
	}
	BOOST_CHECK(actp == t.crend());
} END_PHASE()
#endif



/*============================================================================

Revision History

Version 1.0.0: 2016-06-21

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