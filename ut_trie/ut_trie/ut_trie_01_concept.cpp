/** @file ut_trie_01_concept.cpp
	@author Garth Santor
	@date 2016-05-09
	@version 0.0.0
	@note C++ 11/vc14
	@brief trie<> proof of concept unit test.
	*/

#include "ut_trie.hpp"
#include <boost/test/auto_unit_test.hpp>
#include <map>
#include <string>
using namespace std;


vector<string> words{ "this", "is", "the", "winter", "of", "our", "discontent", "made", "summer", "by", "the", "sons", "of", "York" };
vector<string> days{ "Sunna", "Mona", "Tiw", "Woden", "Thunor", "Frige", "Saturn" };



/** Test the concept of existance.
	The container should be empty and return.
	*/
#if TEST_PHASE >= 1
BEGIN_PHASE(1, concept_exists) {
	trie<std::string> t;
	BOOST_CHECK(t.empty());
	BOOST_CHECK(t.begin() == t.end());
} END_PHASE()
#endif



/** Test the insert interface.
	Insert few elements then checks the basic interface and size method.
	*/
#if TEST_PHASE>=2
BEGIN_PHASE(2, concept_insert_test_size) {
	trie<unsigned> t;
	BOOST_CHECK(t.empty());

	for (auto day : days)
		t[day];
	BOOST_CHECK_EQUAL(t.size(), days.size());
} END_PHASE()
#endif



/** Test the insert interface.
	Insert few elements then checks to see they are contained in the trie.
	*/
#if TEST_PHASE>=3
BEGIN_PHASE(3, concept_insert_test_contains) {
	trie<unsigned> t;
	BOOST_CHECK(t.empty());

	for (auto day : days)
		t[day];
	BOOST_CHECK_EQUAL(t.size(), days.size());

	for (auto day : days) {
		BOOST_CHECK_EQUAL(t.count(day), 1);
	}

	for (auto word : words) {
		BOOST_CHECK_EQUAL(t.count(word), 0);
	}

	BOOST_CHECK_EQUAL(t.count("T"), 2);
	BOOST_CHECK_EQUAL(t.count("S"), 2);
	BOOST_CHECK_EQUAL(t.count("Mo"), 1);
	BOOST_CHECK_EQUAL(t.count("Q"), 0);
} END_PHASE()
#endif



/**	Test insertion more deeply.
	Insert a list of words then check that they are contained in the trie.
	*/
#if TEST_PHASE>=4
BEGIN_PHASE(4, concept_insert_test_values) {
	trie<unsigned> t;
	map<std::string, unsigned> m;
	BOOST_CHECK(t.empty());


	unsigned c = 1;
	for (auto day : days) {
		t[day] = c;
		m[day] = c;
		++c;
	}
	BOOST_CHECK_EQUAL(t.size(), days.size());


	std::set<decltype(t)::key_type> sortedDays(begin(days), end(days));

	for (auto x : sortedDays)
		BOOST_CHECK_EQUAL(m[x], t[x]);

} END_PHASE()
#endif



/**	Test insertion more deeply.
	Insert a list of words then check that they are contained in sorted order.

	@note: requires iterator pre-increment, iterator ==, begin(), end().
	*/
#if TEST_PHASE>=5
BEGIN_PHASE(5, concept_iterator_begin_end) {
	trie<int> t;
	BOOST_CHECK(t.empty());
	BOOST_CHECK(t.begin() == t.end());

	t["ab"] = 42;
	BOOST_CHECK(t.begin() != t.end());
	BOOST_CHECK(t.begin()->first == trie<int>::key_type("ab"));
	BOOST_CHECK(t.begin()->second == 42);

	t["aa"] = 24;
	BOOST_CHECK(t.begin() != t.end());
	BOOST_CHECK(t.begin()->first == trie<int>::key_type("aa"));
	BOOST_CHECK(t.begin()->second == 24);

	t["a"] = 12;
	BOOST_CHECK(t.begin() != t.end());
	BOOST_CHECK(t.begin()->first == trie<int>::key_type("a"));
	BOOST_CHECK(t.begin()->second == 12);

	t[""] = 6;
	BOOST_CHECK(t.begin() != t.end());
	BOOST_CHECK(t.begin()->first == trie<int>::key_type(""));
	BOOST_CHECK(t.begin()->second == 6);
} END_PHASE()
#endif



/**	Test insertion more deeply.
	Insert a list of words then check that they are contained in sorted order.

	@note: requires iterator pre-increment, iterator ==, begin(), end().
	*/
#if TEST_PHASE>=6
BEGIN_PHASE(6, concept_iterator) {
	trie<std::string> t;
	BOOST_CHECK(t.empty());


	for (auto day : days)
		t[day] = day;
	BOOST_CHECK_EQUAL(t.size(), days.size());


	std::set<decltype(t)::key_type> sortedDays(begin(days), end(days));


	auto it = t.begin();
	for (auto x : sortedDays) {
		BOOST_CHECK_EQUAL(it->first, x);
		++it;
	}
	BOOST_CHECK(it == t.end());

} END_PHASE()
#endif



/** Test embedded types concept. */
#if TEST_PHASE>=7
BEGIN_PHASE(7, concept_embedded_type) {
	BOOST_CHECK(typeid(trie<float>::value_type) == typeid(std::pair<std::string const, float>));
	BOOST_CHECK(!std::is_const<trie<std::string>::value_type>());
	BOOST_CHECK(!std::is_reference<trie<std::string>::value_type>());
	BOOST_CHECK(std::is_class<trie<std::string>::value_type>());

	BOOST_CHECK(typeid(trie<std::wstring>::value_type) == typeid(std::pair<std::string const, std::wstring>));
	BOOST_CHECK(!std::is_const<trie<std::wstring>::value_type>());
	BOOST_CHECK(!std::is_reference<trie<std::wstring>::value_type>());
	BOOST_CHECK(std::is_class<trie<std::wstring>::value_type>());
} END_PHASE()
#endif



/** Test embedded iterator types concept. */
#if TEST_PHASE>=8
BEGIN_PHASE(8, concept_embedded_iterator_types) {
	BOOST_CHECK(typeid(trie<double>::iterator::value_type) == typeid(std::pair<std::string const, double>));
	BOOST_CHECK(typeid(trie<std::string>::iterator::value_type) == typeid(std::pair<std::string const, std::string>));
} END_PHASE()
#endif



/*============================================================================

Revision History

Version 0.0.0: 2016-05-09

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