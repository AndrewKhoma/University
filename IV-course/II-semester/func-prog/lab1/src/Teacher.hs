module Teacher where

import           Common
import qualified Data.ByteString.Char8    as BS
import           Data.List
import           Database.HDBC
import           Database.HDBC.PostgreSQL
import           Prelude                  hiding (read)

type Id = Integer

type Name = String

type Surname = String

unpack [SqlInteger uid, SqlByteString name, SqlByteString surname] = (uid, BS.unpack name, BS.unpack surname)
unpack x = error $ "Unexpected result: " ++ show x

createTeacher :: IConnection a => Name -> Surname -> a -> IO Integer
createTeacher name surname conn = withTransaction conn (create' name surname)

create' name surname conn = do
  changed <- run conn query [SqlString name, SqlString surname]
  result <- quickQuery' conn lastId []
  let rows = map Common.convRow result
  return $ last rows
  where
    query = "insert into lab1_teacher (name, surname) values (?, ?)"
    lastId = "select max(id) from lab1_teacher"

readTeacher :: IConnection a => a -> Id -> IO (Id, Name, Surname)
readTeacher conn id = do
  result <- quickQuery' conn query [SqlInteger id]
  let rows = map unpack result
  if null rows
    then return (-1, "", "")
    else return $ last rows
  where
    query = "select * from lab1_teacher where id = ?"

readAllTeachers :: IConnection a => a -> IO [(Id, Name, Surname)]
readAllTeachers conn = do
  result <- quickQuery' conn query []
  return $ map unpack result
  where
    query = "select * from lab1_teacher order by id"

updateTeacher :: IConnection a => Id -> Name -> Surname -> a -> IO (Id, Name, Surname)
updateTeacher uid name surname conn = withTransaction conn (update' uid name surname)

update' uid name surname conn = do
  changed <- run conn query [SqlString name, SqlString surname, SqlInteger uid]
  result <- quickQuery' conn newValue [SqlInteger uid]
  let rows = map unpack result
  return $ last rows
  where
    query = "update lab1_teacher set name = ?, surname = ? where id = ?"
    newValue = "select id, name, surname from lab1_teacher where id = ?"

deleteTeacher :: IConnection a => Id -> a -> IO Bool
deleteTeacher id conn = withTransaction conn (delete' id)

delete' id conn = do
  changed <- run conn query [SqlInteger id]
  return $ changed == 1
  where
    query = "delete from lab1_teacher where id = ?"

deleteAllTeachers :: IConnection a => a -> IO Bool
deleteAllTeachers conn = withTransaction conn deleteAll'

deleteAll' conn = do
  changed <- run conn query []
  return $ changed == 1
  where
    query = "delete from lab1_teacher"
