import           Common
import           Section
import           Student
import           Teacher

import           Test.Tasty               (defaultMain, testGroup)
import           Test.Tasty.HUnit         (assertEqual, assertFailure, testCase)

import           Database.HDBC
import           Database.HDBC.PostgreSQL (connectPostgreSQL)

main = defaultMain allTests

allTests = testGroup "All tests" [teacherTests, sectionTests, studentTests]

teacherTests = testGroup "Teacher tests" [createTeacherTest, updateTeacherTest]

sectionTests = testGroup "Section tests" [createSectionTest, updateSectionTest]

studentTests = testGroup "Student tests" [createStudentTest, updateStudentTest]

createTeacherTest =
  testCase "Create teacher" $ do
    c <- connectPostgreSQL "host=localhost dbname=ahoma user=ahoma password=password"
    newTeacherId <- createTeacher "New" "Teacher" c
    teacher <- readTeacher c newTeacherId
    assertEqual "Teacher ID equal" newTeacherId (Common.getTeacherId teacher)
    assertEqual "Teacher Name equal" "New" (Common.getTeacherName teacher)
    assertEqual "Teacher Surname equal" "Teacher" (Common.getTeacherSurname teacher)
    removed <- deleteTeacher newTeacherId c
    assertEqual "Teacher removed" True removed

updateTeacherTest =
  testCase "Update teacher" $ do
    c <- connectPostgreSQL "host=localhost dbname=ahoma user=ahoma password=password"
    newTeacherId <- createTeacher "New" "Teacher" c
    teacher <- readTeacher c newTeacherId
    assertEqual "Teacher ID equal" newTeacherId (Common.getTeacherId teacher)
    assertEqual "Teacher Name equal" "New" (Common.getTeacherName teacher)
    assertEqual "Teacher Surname equal" "Teacher" (Common.getTeacherSurname teacher)
    teacher <- updateTeacher newTeacherId "Super" "Boxer" c
    assertEqual "Teacher ID equal" newTeacherId (Common.getTeacherId teacher)
    assertEqual "Teacher Name equal" "Super" (Common.getTeacherName teacher)
    assertEqual "Teacher Surname equal" "Boxer" (Common.getTeacherSurname teacher)
    removed <- deleteTeacher newTeacherId c
    assertEqual "Teacher removed" True removed

createSectionTest =
  testCase "Create section" $ do
    c <- connectPostgreSQL "host=localhost dbname=ahoma user=ahoma password=password"
    newTeacherId <- createTeacher "New" "Teacher" c
    newSectionId <- createSection "Neur_new" newTeacherId c
    section <- readSection c newSectionId
    assertEqual "Section ID equal" newSectionId (Common.getSectionId section)
    assertEqual "Section Name equal" "Neur_new" (Common.getSectionName section)
    assertEqual "Section TeacherID equal" newTeacherId (Common.getSectionTeacherId section)
    removed <- deleteSection newSectionId c
    assertEqual "Section removed" True removed
    removed <- deleteTeacher newTeacherId c
    assertEqual "Teacher removed" True removed

updateSectionTest =
  testCase "Update section" $ do
    c <- connectPostgreSQL "host=localhost dbname=ahoma user=ahoma password=password"
    newTeacherId <- createTeacher "New" "Teacher" c
    newSectionId <- createSection "Neur_new" newTeacherId c
    section <- readSection c newSectionId
    assertEqual "Section ID equal" newSectionId (Common.getSectionId section)
    assertEqual "Section Name equal" "Neur_new" (Common.getSectionName section)
    assertEqual "Section TeacherID equal" newTeacherId (Common.getSectionTeacherId section)
    section <- updateSection newSectionId "Neurons" newTeacherId c
    assertEqual "Section ID equal" newSectionId (Common.getSectionId section)
    assertEqual "Section Name equal" "Neurons" (Common.getSectionName section)
    assertEqual "Section TeacherID equal" newTeacherId (Common.getSectionTeacherId section)
    removed <- deleteSection newSectionId c
    assertEqual "Section removed" True removed
    removed <- deleteTeacher newTeacherId c
    assertEqual "Teacher removed" True removed

createStudentTest =
  testCase "Create student" $ do
    c <- connectPostgreSQL "host=localhost dbname=ahoma user=ahoma password=password"
    newTeacherId <- createTeacher "New" "Teacher" c
    newSectionId <- createSection "Neur_new" newTeacherId c
    newStudentId <- createStudent "Bambito" "Liderito" newSectionId c
    student <- readStudent c newStudentId
    assertEqual "Student ID equal" newStudentId (Common.getStudentId student)
    assertEqual "Student Name equal" "Bambito" (Common.getStudentName student)
    assertEqual "Student Surname equal" "Liderito" (Common.getStudentSurname student)
    assertEqual "Student SectionID equal" newSectionId (Common.getStudentSection student)
    removed <- deleteStudent newStudentId c
    assertEqual "Student removed" True removed
    removed <- deleteSection newSectionId c
    assertEqual "Section removed" True removed
    removed <- deleteTeacher newTeacherId c
    assertEqual "Teacher removed" True removed

updateStudentTest =
  testCase "Update student" $ do
    c <- connectPostgreSQL "host=localhost dbname=ahoma user=ahoma password=password"
    newTeacherId <- createTeacher "New" "Teacher" c
    newSectionId <- createSection "Neur_new" newTeacherId c
    newStudentId <- createStudent "Bambito" "Liderito" newSectionId c
    student <- readStudent c newStudentId
    assertEqual "Student ID equal" newStudentId (Common.getStudentId student)
    assertEqual "Student Name equal" "Bambito" (Common.getStudentName student)
    assertEqual "Student Surname equal" "Liderito" (Common.getStudentSurname student)
    assertEqual "Student SectionID equal" newSectionId (Common.getStudentSection student)
    student <- updateStudent newStudentId "Lolipop" "Kekovich" newSectionId c
    assertEqual "Student ID equal" newStudentId (Common.getStudentId student)
    assertEqual "Student Name equal" "Lolipop" (Common.getStudentName student)
    assertEqual "Student Surname equal" "Kekovich" (Common.getStudentSurname student)
    assertEqual "Student SectionID equal" newSectionId (Common.getStudentSection student)
    removed <- deleteStudent newStudentId c
    assertEqual "Student removed" True removed
    removed <- deleteSection newSectionId c
    assertEqual "Section removed" True removed
    removed <- deleteTeacher newTeacherId c
    assertEqual "Teacher removed" True removed
