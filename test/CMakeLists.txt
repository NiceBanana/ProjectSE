cmake_minimum_required(VERSION 3.5)

set(CMAKE_EXE_LINKER_FLAGS -pthread)

set(ProjectFiles
        ../VerkeersSituatie.cpp
        ../VerkeersSituatie.h
        ../Baan.cpp
        ../Baan.h
        ../Verkeerslicht.cpp
        ../Verkeerslicht.h
        ../Voertuig.cpp
        ../Voertuig.h
        ../VoertuigGenerator.cpp
        ../VoertuigGenerator.h
        ../SituatieExceptions.cpp
        ../SituatieExceptions.h
        ../VerkeersElement.cpp
        ../VerkeersElement.h
        ../Bushalte.cpp
        ../Bushalte.h
        ../Kruispunt.cpp
        ../Kruispunt.h
        ../Bus.cpp
        ../Bus.h
        ../Prioriteitsvoertuig.cpp
        ../Prioriteitsvoertuig.h)

add_executable(Test Test.cpp BaanTest.cpp VoertuigTest.cpp VoertuigGeneratorTest.cpp ${ProjectFiles} VerkeersSituatieTest.cpp utils.cpp utils.h VerkeersElementTest.cpp)
target_link_libraries(Test gtest)
target_link_libraries(Test tinyxml)
target_link_libraries(Test DesignByContract)

