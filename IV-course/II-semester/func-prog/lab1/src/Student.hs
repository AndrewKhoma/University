module Student where

import           Common
import qualified Data.ByteString.Char8    as BS
import           Database.HDBC
import           Database.HDBC.PostgreSQL
import           Prelude                  hiding (read)

type Id = Integer

type Name = String

type Surname = String

unpack [SqlInteger uid, SqlByteString name, SqlByteString surname, SqlInteger sid] =
  (uid, BS.unpack name, BS.unpack surname, sid)
unpack x = error $ "Unexpected result: " ++ show x

createStudent :: IConnection a => Name -> Surname -> Id -> a -> IO Integer
createStudent name surname sectionId conn = withTransaction conn (create' name surname sectionId)

create' name surname sectionId conn = do
  changed <- run conn query [SqlString name, SqlString surname, SqlInteger sectionId]
  result <- quickQuery' conn lastId []
  let rows = map Common.convRow result
  return $ last rows
  where
    query = "insert into lab1_student (name, surname, sectionId) values (?, ?, ?)"
    lastId = "select max(id) from lab1_student"

readStudent :: IConnection a => a -> Id -> IO (Id, Name, Surname, Id)
readStudent conn id = do
  result <- quickQuery' conn query [SqlInteger id]
  let rows = map unpack result
  if null rows
    then return (-1, "", "", -1)
    else return $ last rows
  where
    query = "select * from lab1_student where id = ?"

readAllStudents :: IConnection a => a -> IO [(Id, Name, Surname, Id)]
readAllStudents conn = do
  result <- quickQuery' conn query []
  return $ map unpack result
  where
    query = "select * from lab1_student order by id"

updateStudent :: IConnection a => Id -> Name -> Surname -> Id -> a -> IO (Id, Name, Surname, Id)
updateStudent uid name surname sid conn = withTransaction conn (update' uid name surname sid)

update' uid name surname sid conn = do
  changed <- run conn query [SqlString name, SqlString surname, SqlInteger sid, SqlInteger uid]
  result <- quickQuery' conn newValue [SqlInteger uid]
  let rows = map unpack result
  return $ last rows
  where
    query = "update lab1_student set name = ?, surname = ?, sectionId = ? where id = ?"
    newValue = "select id, name, surname, sectionId from lab1_student where id = ?"

deleteStudent :: IConnection a => Id -> a -> IO Bool
deleteStudent id conn = withTransaction conn (delete' id)

delete' id conn = do
  changed <- run conn query [SqlInteger id]
  return $ changed == 1
  where
    query = "delete from lab1_student where id = ?"

deleteAllStudents :: IConnection a => a -> IO Bool
deleteAllStudents conn = withTransaction conn deleteAll'

deleteAll' conn = do
  changed <- run conn query []
  return $ changed == 1
  where
    query = "delete from lab1_student"
