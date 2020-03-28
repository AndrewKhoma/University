module Common where

import           Database.HDBC
import           Database.HDBC.PostgreSQL

convRow :: [SqlValue] -> Integer
convRow [sqlId] = intId
  where
    intId = fromSql sqlId :: Integer
convRow x = error $ "Unexpected result: " ++ show x

getTeacherId :: (a, b, c) -> a
getTeacherId (x, _, _) = x

getTeacherName :: (a, b, c) -> b
getTeacherName (_, y, _) = y

getTeacherSurname :: (a, b, c) -> c
getTeacherSurname (_, _, z) = z

getSectionId :: (a, b, c) -> a
getSectionId (x, _, _) = x

getSectionName :: (a, b, c) -> b
getSectionName (_, y, _) = y

getSectionTeacherId :: (a, b, c) -> c
getSectionTeacherId (_, _, z) = z

getStudentId :: (a, b, c, d) -> a
getStudentId (x, _, _, _) = x

getStudentName :: (a, b, c, d) -> b
getStudentName (_, y, _, _) = y

getStudentSurname :: (a, b, c, d) -> c
getStudentSurname (_, _, z, _) = z

getStudentSection :: (a, b, c, d) -> d
getStudentSection (_, _, _, w) = w
