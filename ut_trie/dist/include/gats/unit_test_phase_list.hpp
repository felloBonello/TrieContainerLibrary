#if !defined(GUARD_unit_test_phase_list_header)
#define GUARD_unit_test_phase_list_header

/** @file unit_test_phase_list.hpp
	@author Garth Santor
	@date 2014-05-02
	@version 2.0.0
	@note C++ 11/vc14
	@brief Unit test phase reporting.
	*/

#include <set>
#include <memory>
#include <iostream>


/** PhaseList <<singleton>>

	Tracks which unit test phases have been attempted and reports the list of
	phases missing from the unit test.
	*/
template <typename SIZE_T = std::size_t>
class PhaseList {
	SIZE_T								nPhases_;
	std::set<SIZE_T>					phases_;
	static std::unique_ptr<PhaseList>	ptr_;


	/** <<constructor>> sets the phase list to [1..nPhases] */
	PhaseList(SIZE_T _nPhases) : nPhases_(_nPhases) {
		for (SIZE_T i = 1; i <= _nPhases; ++i)
			phases_.insert(i);
	}

public:
	/** <<destructor>> reports phase incompletions to stdout. */
	~PhaseList() {
		if (phases_.empty())
			std::cout << "\nAll "<< nPhases_ << " phases implemented." << std::endl;
		else {
			std::cout << "\nPhases not implemented: ";
			auto it = phases_.begin();
			std::cout << *it;
			while (++it != phases_.end())
				std::cout << ", " << *it;
			std::cout << std::endl;
		}
	}

	/** Set the total number of phases in the unit test. */
	static void set_phases(SIZE_T _nPhases) {
		if (!ptr_)
			ptr_.reset(new PhaseList(_nPhases));
	}


	/** Record that a phase has been implemented. */
	static void implements(SIZE_T _phase) {
		ptr_->phases_.erase(_phase);
	}
};


/** <<singleton>> member variable instance. */
template <typename SIZE_T = std::size_t>
std::unique_ptr<PhaseList<SIZE_T>> PhaseList<
	SIZE_T>::ptr_;

/*============================================================================

Revision History

Version 2.0.0: 2016-05-09
Changed to a template to remove the need of explicitly instantiating the static member.

Version 1.0.0: 2014-05-02
Initial version.

==============================================================================
Copyright Garth Santor, 2014

The copyright to the computer program(s) herein
is the property of Garth Santor, Canada.
The program(s) may be used and/or copied only with
the written permission of Garth Santor
or in accordance with the terms and conditions
stipulated in the agreement/contract under which
the program(s) have been supplied.
============================================================================*/
#endif // GUARD_unit_test_phase_list_header