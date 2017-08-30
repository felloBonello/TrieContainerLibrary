/** @file ut_trie_03_forward_iter.cpp
	@author Garth Santor
	@date 2016-06-16
	@version 0.0.0
	@note C++ 11/vc14
	@brief trie<> unit test for forward iterators.
	*/

#include "ut_trie.hpp"
#include <boost/test/auto_unit_test.hpp>
#include <map>
#include <vector>
#include <boost/lexical_cast.hpp>



/** Test square_list<>::begin, end, empty constructor */
#if TEST_PHASE >= 13
BEGIN_PHASE(13, ut_forward_iterator_empty) {
	trie<int> di;
	BOOST_CHECK(di.size() == 0);
	BOOST_CHECK(di.empty());
	BOOST_CHECK(di.begin() == di.end());
} END_PHASE()
#endif



/** Test square_list<>::iterator single element */
#if TEST_PHASE >= 14
BEGIN_PHASE(14, ut_forward_iterator_one) {
	trie<int> di;
	di["1"] = 1;
	BOOST_CHECK(di.size() == 1);
	BOOST_CHECK(!di.empty());
	
	auto p = di.begin();
	BOOST_CHECK(p != di.end());
	BOOST_CHECK_EQUAL(p->second, 1);
} END_PHASE()
#endif



/** Test square_list<>::iterator for forward iteration */
#if TEST_PHASE >= 15
BEGIN_PHASE(15, ut_forward_iterator_loop) {
	std::size_t limit = 33;
	trie<std::size_t> t;
	using kt = decltype(t)::key_type;
	std::map<kt,std::size_t> m;


	BOOST_CHECK(t.empty());
	for (std::size_t i = 0; i < limit; ++i) {
		auto k = boost::lexical_cast<kt>(i);
		m[k] = i;
		t[k] = i;
		BOOST_CHECK_EQUAL(m.size(), t.size());

		// check the full list using post-increment
		auto tp = t.begin();
		auto mp = m.begin();
		while (tp != t.end()) {
			BOOST_CHECK(mp != m.end());
			BOOST_CHECK_EQUAL(tp++->second,mp++->second);
		}
		BOOST_CHECK(tp == t.end());

		tp = t.begin();
		mp = m.begin();
		for (size_t i = 1; i < m.size(); ++i)
			BOOST_CHECK_EQUAL((++tp)->second, (++mp)->second);

		BOOST_CHECK(++tp == t.end());
	}
} END_PHASE()
#endif


#if TEST_PHASE >= 16
BEGIN_PHASE(16, ut_forward_iterator_loop_mutating) {
	std::vector<int> v{ 1,2,3,4,5 }, v2{ 2,4,6,8,10 };
	trie<std::size_t> t;
	using kt = decltype(t)::key_type;

	for (auto e : v)
		t[boost::lexical_cast<kt>(e)] = e;

	for (auto& e : t)
		e.second *= 2;

	auto tp = t.begin();
	for (auto e : v2) {
		BOOST_CHECK_EQUAL(e, tp->second);
		++tp;
	}

} END_PHASE()
#endif

/*============================================================================

Revision History

Version 0.0.0: 2016-06-16

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