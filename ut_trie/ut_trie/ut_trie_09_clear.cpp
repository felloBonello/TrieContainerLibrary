/**	@file ut_trie_09_clear.cpp
	@author Garth Santor
	@date 2016-06-25
	@version 1.0.0
	@note C++ 11/vc14
	@brief trie<> unit test for clear method.
	*/

#include "ut_trie.hpp"
#include <boost/test/auto_unit_test.hpp>
#include <boost/lexical_cast.hpp>



/** Test trie<T>::clear() */
#if TEST_PHASE >= 32
BEGIN_PHASE(32, ut_clear ) {
	trie<double> d;
	BOOST_CHECK( d.empty() );
	BOOST_CHECK( d.size() == 0 );
	BOOST_CHECK( d.begin() == d.end() );

	for (double x = 0; x < 10; ++x)
		d[boost::lexical_cast<decltype(d)::key_type>(x)] = x;

	BOOST_CHECK( !d.empty() );
	BOOST_CHECK( d.size() == 10 );
	BOOST_CHECK( d.begin() != d.end() );

	d.clear();
	BOOST_CHECK( d.empty() );
	BOOST_CHECK( d.size() == 0 );
	BOOST_CHECK( d.begin() == d.end() );
} END_PHASE()
#endif


/*============================================================================

Revision History

Version 1.0.0: 2016-06-25

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