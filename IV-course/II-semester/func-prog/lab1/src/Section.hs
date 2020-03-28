module Section where

import           Common
import qualified Data.ByteString.Char8    as BS
import           Database.HDBC
import           Database.HDBC.PostgreSQL
import           Prelude                  hiding (read)

type Id = Integer

type Name = String

unpack [SqlInteger uid, SqlByteString name, SqlInteger tid] = (uid, BS.unpack name, tid)
unpack x = error $ "Unexpected result: " ++ show x

createSection :: IConnection a => Name -> Id -> a -> IO Integer
createSection name tid conn = withTransaction conn (create' name tid)

create' name tid conn = do
  changed <- run conn query [SqlString name, SqlInteger tid]
  result <- quickQuery' conn lastId []
  let rows = map Common.convRow result
  return $ last rows
  where
    query = "insert into lab1_section (name, teacherId) values (?, ?)"
    lastId = "select max(id) from lab1_section"

readSection :: IConnection a => a -> Id -> IO (Id, Name, Id)
readSection conn id = do
  result <- quickQuery' conn query [SqlInteger id]
  let rows = map unpack result
  if null rows
    then return (-1, "", -1)
    else return $ last rows
  where
    query = "select * from lab1_section where id = ?"

readAllSections :: IConnection a => a -> IO [(Id, Name, Id)]
readAllSections conn = do
  result <- quickQuery' conn query []
  return $ map unpack result
  where
    query = "select * from lab1_section order by id"

updateSection :: IConnection a => Id -> Name -> Id -> a -> IO (Id, Name, Id)
updateSection uid name tid conn = withTransaction conn (update' uid name tid)

update' uid name tid conn = do
  changed <- run conn query [SqlString name, SqlInteger tid, SqlInteger uid]
  result <- quickQuery' conn newValue [SqlInteger uid]
  let rows = map unpack result
  return $ last rows
  where
    query = "update lab1_section set name = ?, teacherId = ? " ++ " where id = ?"
    newValue = "select id, name, teacherId from lab1_section where id = ?"

deleteSection :: IConnection a => Id -> a -> IO Bool
deleteSection id conn = withTransaction conn (delete' id)

delete' id conn = do
  changed <- run conn query [SqlInteger id]
  return $ changed == 1
  where
    query = "delete from lab1_section where id = ?"

deleteAllSections :: IConnection a => a -> IO Bool
deleteAllSections conn = withTransaction conn deleteAll'

deleteAll' conn = do
  changed <- run conn query []
  return $ changed == 1
  where
    query = "delete from lab1_section"
