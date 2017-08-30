#if !defined(GUARD_ut_trie_header)
#define GUARD_ut_trie_header

/** @file ut_trie.hpp
	@author Garth Santor
	@date 2016-05-09
	@version 1.0.0
	@note C++ 11/vc14
	@brief trie<> unit test common elements headers.
	*/


#define UT_VERSION "1.0.0"

#define TEST_PHASE 79


#include <gats/trie.hpp>
#include <gats/unit_test_phase_list.hpp>

#define BEGIN_PHASE(num,name) BOOST_AUTO_TEST_CASE(name) { auto phaseNumber = num;
#define END_PHASE() PhaseList<>::implements(phaseNumber); }


/*============================================================================

Revision History

Version 1.0.0: 2016-05-09

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
#endif // GUARD_ut_trie_header