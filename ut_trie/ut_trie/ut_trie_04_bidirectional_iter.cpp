/** @file ut_square_list_04_bidirectional_iter.cpp
	@author Garth Santor
	@date 2016-06-18
	@version 1.0.0
	@note C++ 11/vc14
	@brief trie<> unit test for bidirectional iterators.
	*/

#include "ut_trie.hpp"
#include <boost/test/auto_unit_test.hpp>
#include <map>
#include <boost/lexical_cast.hpp>



/** Test trie<>::difference_type */
#if TEST_PHASE >= 17
BEGIN_PHASE(17, ut_types_difference_type) {
	BOOST_CHECK(typeid(trie<double>::difference_type) == typeid(std::ptrdiff_t));
	BOOST_CHECK(typeid(trie<std::string>::difference_type) == typeid(std::ptrdiff_t));
} END_PHASE()
#endif



/** Test bidirectional iterators */
#if TEST_PHASE >= 18
BEGIN_PHASE(18, ut_bidirectional_iterator) {
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
		auto tp = t.end();
		auto mp = m.end();
		while (tp != t.begin()) {
			BOOST_CHECK(mp != m.begin());
			auto lhs = (--tp)->second;
			auto rhs = (--mp)->second;
			BOOST_CHECK_EQUAL(lhs, rhs);
		}
		BOOST_CHECK(tp == t.begin());

		tp = --t.end();
		mp = --m.end();
		while (tp != t.begin()) {
			BOOST_CHECK_EQUAL((tp--)->second, (mp--)->second);
		}
		BOOST_CHECK(tp == t.begin());
		BOOST_CHECK(std::distance(t.begin(), t.end()) == t.size());
	}
} END_PHASE()
#endif







/*============================================================================

Revision History

Version 1.0.0: 2016-06-18

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