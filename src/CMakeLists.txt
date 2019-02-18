cmake_minimum_required(VERSION 3.6)
project(src)

set(CMAKE_CXX_STANDARD 11)

IF(CMAKE_COMPILER_IS_GNUCC)
    #  set(CMAKE_CXX_FLAGS_DEBUG "-O4") # no debug
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O4") # keep debug
ENDIF(CMAKE_COMPILER_IS_GNUCC)

set(SOURCE_FILES
    main.cpp
        Utils/Sequence.cpp Utils/Sequence.h
    NamedElement.cpp
    NamedElement.h
    Clock.cpp
    Clock.h
        Constraints/Relations/Precedes.cpp
        Constraints/Relations/Precedes.h
        Utils/QuantumBoolean.h
        Utils/TruthTable.cpp
        Utils/TruthTable.h
        Constraints/Expressions/Union.cpp
        Constraints/Expressions/Union.h Constraints/Constraint.cpp Constraints/Constraint.h Constraints/Relations/SubClock.cpp Constraints/Relations/SubClock.h Constraints/Relations/Exclusion.cpp Constraints/Relations/Exclusion.h Constraints/Expressions/Wait.cpp Constraints/Expressions/Wait.h Constraints/Expressions/Defer.cpp Constraints/Expressions/Defer.h Constraints/Expressions/Concatenation.cpp Constraints/Expressions/Concatenation.h Constraints/Relations/Causes.cpp Constraints/Relations/Causes.h Constraints/Expressions/Intersection.cpp Constraints/Expressions/Intersection.h Constraints/Expressions/SampledOn.cpp Constraints/Expressions/SampledOn.h Constraints/Expressions/UpTo.cpp Constraints/Expressions/UpTo.h Constraints/Expressions/Inf.cpp Constraints/Expressions/Inf.h Constraints/Expressions/Sup.cpp Constraints/Expressions/Sup.h Utils/QuantumBoolean.cpp)

add_executable(src ${SOURCE_FILES})