/** @file ut_trie_00_main.cpp
	@author Garth Santor
	@date 2016-05-04
	@version 0.0.0
	@note C++ 11/vc14
	@brief trie<> unit test main module.
	*/

#define BOOST_TEST_MODULE trie_unit_test
#include <boost/test/auto_unit_test.hpp>
#include <iostream>
#include <iomanip>
using namespace std;
#include "ut_trie.hpp"
#include <gats/compiler.hpp>
#include <gats/unit_test_phase_list.hpp>


/** Unit test build info. */
BOOST_AUTO_TEST_CASE(ut_build_info) {
	double mscVersion = _MSC_VER / 100.0;
	cout << "ut-square_list<> version " UT_VERSION "\n"
		"TEST PHASE = " << TEST_PHASE << "\n"
		"MSC Version: " << fixed << setprecision(2) << mscVersion << " -> " __GATS_BUILD_TYPE__ "\n"
		"Last Build: " __DATE__ " - " __TIME__ "\n" << endl;

	PhaseList<>::set_phases(TEST_PHASE);
}


/*============================================================================

Revision History

Version 0.0.0: 2016-05-04

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