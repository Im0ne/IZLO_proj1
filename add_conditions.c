#include <stddef.h>
#include "cnf.h"

//
// LOGIN: <xonufr00>
//

void example_condition(CNF *formula, unsigned num_of_subjects, unsigned num_of_semesters) {
    assert(formula != NULL);
    assert(num_of_subjects > 0);
    assert(num_of_semesters > 0);

    for (unsigned subject_i = 0; subject_i < num_of_subjects; ++subject_i) {
        for (unsigned semester_j = 0; semester_j < num_of_semesters; ++semester_j) {
            Clause *example_clause = create_new_clause(num_of_subjects, num_of_semesters);
            add_literal_to_clause(example_clause, true, subject_i, semester_j);
            add_literal_to_clause(example_clause, false, subject_i, semester_j);
            add_clause_to_formula(example_clause, formula);
        }
    }
}

void each_subject_enrolled_at_least_once(CNF *formula, unsigned num_of_subjects, unsigned num_of_semesters) {
    assert(formula != NULL);
    assert(num_of_subjects > 0);
    assert(num_of_semesters > 0);
    
    for (unsigned o = 0; o < num_of_subjects; o++) {
        Clause *clause = create_new_clause(num_of_subjects, num_of_semesters);
        for (unsigned n = 0; n < num_of_semesters; n++) {
            add_literal_to_clause(clause, true, o, n);
        }
        add_clause_to_formula(clause, formula);
    }

}

void each_subject_enrolled_at_most_once(CNF *formula, unsigned num_of_subjects, unsigned num_of_semesters) {
    assert(formula != NULL);
    assert(num_of_subjects > 0);
    assert(num_of_semesters > 0);
    
    for (unsigned o = 0; o < num_of_subjects; o++) {
        for (unsigned n = 0; n < num_of_semesters; n++) {
            for (unsigned u = n + 1; u < num_of_semesters; u++) {
                Clause *clause = create_new_clause(num_of_subjects, num_of_semesters);
                add_literal_to_clause(clause, false, o, n);
                add_literal_to_clause(clause, false, o, u);
                add_clause_to_formula(clause, formula);
            }
        }
    }
}

void add_prerequisities_to_formula(CNF *formula, Prerequisity* prerequisities, unsigned num_of_prerequisities, unsigned num_of_subjects, unsigned num_of_semesters) {
    assert(formula != NULL);
    assert(prerequisities != NULL);
    assert(num_of_subjects > 0);
    assert(num_of_semesters > 0);

    for (unsigned o = 0; o < num_of_prerequisities; o++) {        
        for (int n = num_of_semesters - 1; n >= 0; n--) {
            Clause *clause = create_new_clause(num_of_subjects, num_of_semesters);                      
            add_literal_to_clause(clause, false, prerequisities[o].later_subject, n);             
            for (int u = n - 1; u >= 0; u--) {
            add_literal_to_clause(clause, true, prerequisities[o].earlier_subject, u);}                        
            add_clause_to_formula(clause, formula);            
        }
    }
}
