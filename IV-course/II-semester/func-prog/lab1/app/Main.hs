module Main where

import           Control.Exception
import           Database.HDBC
import           Database.HDBC.PostgreSQL (connectPostgreSQL)

import           Section
import           Student
import           Teacher

main = do
  c <- connectPostgreSQL "host=localhost dbname=ahoma user=ahoma password=password"
  putStrLn " -- TEACHERS -- "
  --
  allTeachers <- readAllTeachers c
  print allTeachers
  newTeacherId <- createTeacher "Kyle_new" "Superuser_new" c
  print newTeacherId
  newTeacher <- readTeacher c newTeacherId
  print newTeacher
  updateTeacher newTeacherId "Super" "Boxer" c
  updatedTeacher <- readTeacher c newTeacherId
  print updatedTeacher
  successfullyDeletedTeacher <- deleteTeacher newTeacherId c
  print successfullyDeletedTeacher
  emptyTeacher <- readTeacher c newTeacherId
  print emptyTeacher
  -- create teacher
  newTeacherId <- createTeacher "Kyle_new" "Superuser_new" c
  ---
  putStrLn " -- SECTIONS -- "
  ---
  allSections <- readAllSections c
  print allSections
  newSectionId <- createSection "Neur_new" newTeacherId c
  print newSectionId
  newSection <- readSection c newSectionId
  print newSection
  updateSection newSectionId "Neurons" newTeacherId c
  updatedSection <- readSection c newSectionId
  print updatedSection
  successfullyDeletedSection <- deleteSection newSectionId c
  print successfullyDeletedSection
  emptySection <- readSection c newSectionId
  print emptySection
  -- create section
  newSectionId <- createSection "Neurons" newTeacherId c
  --
  putStrLn " -- STUDENTS -- "
  --
  allStudents <- readAllStudents c
  print allStudents
  newStudentId <- createStudent "Bambito" "Liderito" newSectionId c
  print newStudentId
  newStudent <- readStudent c newStudentId
  print newStudent
  updateStudent newStudentId "Lolipop" "Kekovich" newSectionId c
  updatedStudent <- readStudent c newStudentId
  print updatedStudent
  successfullyDeletedStudent <- deleteStudent newStudentId c
  print successfullyDeletedStudent
  emptyStudent <- readStudent c newStudentId
  print emptyStudent
