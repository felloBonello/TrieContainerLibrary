/** @file ut_trie_02_capacity.cpp
	@author Garth Santor
	@date 2016-06-13
	@version 0.0.0
	@note C++ 11/vc14
	@brief trie<> unit test for capacity methods.
	*/

#include "ut_trie.hpp"
#include <boost/test/auto_unit_test.hpp>
#include <boost/lexical_cast.hpp>



/** Test trie<>::size_type */
#if TEST_PHASE >= 9
BEGIN_PHASE(9, concept_size_type) {

	using DST = trie<double>::size_type;
	BOOST_CHECK(!std::is_floating_point<DST>());
	BOOST_CHECK(std::is_unsigned<DST>());
	BOOST_CHECK(std::is_integral<DST>());

	using SST = trie<std::string>::size_type;
	BOOST_CHECK(!std::is_floating_point<SST>());
	BOOST_CHECK(std::is_unsigned<SST>());
	BOOST_CHECK(std::is_integral<SST>());
} END_PHASE()
#endif



/** Test trie<>::empty */
#if TEST_PHASE >= 10
BEGIN_PHASE(10, capacity_empty) {

	trie<int> di;
	BOOST_CHECK(di.empty());
	di["aa"] = 42;
	BOOST_CHECK(!di.empty());

	trie<double> dd;
	BOOST_CHECK(dd.empty());
	dd["bb"] = 42.1;
	BOOST_CHECK(!dd.empty());
} END_PHASE()
#endif



/** Test trie<>::size */
#if TEST_PHASE >= 11
BEGIN_PHASE(11, capacity_size) {
	using key_type = trie<int>::key_type;
	trie<int>::size_type limit = 100;
	trie<int> di;
	for (decltype(limit) i = 0; i < limit; ++i) {
		BOOST_CHECK_EQUAL(di.size(), i);
		di[boost::lexical_cast<key_type>(i)] = (int)i;
	}
	BOOST_CHECK_EQUAL(di.size(), limit);

	trie<double> dd;
	for (decltype(limit) i = 0; i < limit; ++i) {
		BOOST_CHECK_EQUAL(dd.size(), i);
		dd[boost::lexical_cast<key_type>(i)] = (double)i;
	}
	BOOST_CHECK_EQUAL(dd.size(), limit);


	trie<std::string> ds;
	for (decltype(limit) i = 0; i < limit; ++i) {
		BOOST_CHECK_EQUAL(ds.size(), i);
		ds[boost::lexical_cast<key_type>(i)] = std::string(i, 'a');
	}
	BOOST_CHECK_EQUAL(ds.size(), limit);
} END_PHASE()
#endif
				


/** Test trie<>::max_size */
#if TEST_PHASE >= 12
BEGIN_PHASE(12, capacity_max_size) {
	
	trie<int> di;
	BOOST_CHECK(di.max_size() == std::numeric_limits<decltype(di)::size_type>::max());

	trie<double> dd;
	BOOST_CHECK(dd.max_size() == std::numeric_limits<decltype(dd)::size_type>::max());

	trie<float> df;
	BOOST_CHECK(df.max_size() == std::numeric_limits<decltype(df)::size_type>::max());

	trie<std::string> ds;
	BOOST_CHECK(ds.max_size() == std::numeric_limits<decltype(ds)::size_type>::max());
} END_PHASE()
#endif



/*============================================================================

Revision History

Version 0.0.0: 2016-06-13

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