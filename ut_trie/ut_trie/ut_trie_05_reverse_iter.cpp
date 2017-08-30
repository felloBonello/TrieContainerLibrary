/** @file ut_trie_05_reverse_iter.cpp
	@author Garth Santor
	@date 2016-06-20
	@version 1.0.0
	@note C++ 11/vc14
	@brief trie<> unit test for reverse iterators.
	*/

#include "ut_trie.hpp"
#include <boost/test/auto_unit_test.hpp>
#include <map>
#include <boost/lexical_cast.hpp>



/** Test square_list<>::reverse_iterator */
#if TEST_PHASE >= 19
BEGIN_PHASE(19, ut_types_reverse_iterator_type) {
	BOOST_CHECK(typeid(trie<double>::reverse_iterator::value_type) == typeid(std::pair<std::string const, double>));
	BOOST_CHECK(typeid(trie<std::string>::reverse_iterator::value_type) == typeid(std::pair<std::string const, std::string>));
} END_PHASE()
#endif



#if TEST_PHASE >= 20
BEGIN_PHASE(20, ut_reverse_iterator_category) {
	BOOST_CHECK(typeid(std::iterator_traits<trie<double>::reverse_iterator>::iterator_category) == typeid(std::bidirectional_iterator_tag));
	BOOST_CHECK(typeid(std::iterator_traits<trie<long>::reverse_iterator>::iterator_category) == typeid(std::bidirectional_iterator_tag));
} END_PHASE()
#endif



/** Test trie<>::rbegin, rend */
#if TEST_PHASE >= 21
BEGIN_PHASE(21, ut_reverse_iterator_empty) {
	trie<int> t;
	BOOST_CHECK(t.size() == 0);
	BOOST_CHECK(t.empty());
	BOOST_CHECK(t.rbegin() == t.rend());
} END_PHASE()
#endif



/** Test trie<>::reverse_iterator single element */
#if TEST_PHASE >= 22
BEGIN_PHASE(22, ut_reverse_iterator_one) {
	trie<int> t;
	t["1"] = 1;
	BOOST_CHECK(t.size() == 1);
	BOOST_CHECK(!t.empty());

	auto p = t.rbegin();
	BOOST_CHECK(p != t.rend());
	BOOST_CHECK_EQUAL(p->second, 1);
} END_PHASE()
#endif



/** Test trie<>::reverse_iterator using increment operators */
#if TEST_PHASE >= 23
BEGIN_PHASE(23, ut_reverse_iterator_increment) {
	std::size_t limit = 33;
	trie<std::size_t> t;
	using kt = decltype(t)::key_type;
	std::map<kt, std::size_t> m;

	BOOST_CHECK(t.empty());
	for (std::size_t i = 0; i < limit; ++i) {
		auto k = boost::lexical_cast<kt>(i);
		m[k] = i;
		t[k] = i;
		BOOST_CHECK_EQUAL(m.size(), t.size());

		// check the full list using post-increment
		auto tp = t.rbegin();
		auto mp = m.rbegin();
		while (tp != t.rend()) {
			BOOST_CHECK(mp != m.rend());
			BOOST_CHECK_EQUAL(tp++->second, mp++->second);
		}
		BOOST_CHECK(tp == t.rend());

		tp = t.rbegin();
		mp = m.rbegin();
		for (size_t i = 1; i < m.size(); ++i)
			BOOST_CHECK_EQUAL((++tp)->second, (++mp)->second);

		BOOST_CHECK(++tp == t.rend());
		BOOST_CHECK(std::distance(t.rbegin(), t.rend()) == t.size());
	}
} END_PHASE()
#endif



/** Test square_list<>::reverse_iterator using decrement operators */
#if TEST_PHASE >= 24
BEGIN_PHASE(24, ut_reverse_iterator_decrement) {
	std::size_t limit = 33;
	trie<std::size_t> t;
	using kt = decltype(t)::key_type;
	std::map<kt, std::size_t> m;


	BOOST_CHECK(t.empty());
	for (size_t i = 0; i < limit; ++i) {
		auto k = boost::lexical_cast<kt>(i);
		m[k] = i;
		t[k] = i;
		BOOST_CHECK_EQUAL(m.size(), t.size());

		// check the full list using post-increment
		auto tp = t.rend();
		auto mp = m.rend();
		while (tp != t.rbegin()) {
			BOOST_CHECK(mp != m.rbegin());
			auto lhs = (--tp)->second;
			auto rhs = (--mp)->second;
			BOOST_CHECK_EQUAL(lhs, rhs);
		}
		BOOST_CHECK(tp == t.rbegin());

		tp = --t.rend();
		mp = --m.rend();
		while (tp != t.rbegin()) {
			BOOST_CHECK_EQUAL((tp--)->second, (mp--)->second);
		}
		BOOST_CHECK(tp == t.rbegin());
		BOOST_CHECK(std::distance(t.rbegin(), t.rend()) == t.size());
	}
} END_PHASE()
#endif




/*============================================================================

Revision History

Version 1.0.0: 2016-06-20

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