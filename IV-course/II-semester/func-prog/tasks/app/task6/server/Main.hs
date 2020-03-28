module Main where

import           Control.Applicative
import           Control.Concurrent
import           Control.Monad

import           Data.List           (delete)
import           Data.Maybe
import           Data.Word

import           Network

import           System.Environment
import           System.IO

import           Text.Printf

defaultPort = 4711 :: Word16

data Client =
  Client
    { clientHandle :: Handle
    , clientHost   :: HostName
    , clientPort   :: PortNumber
    }

instance Eq Client where
  a == b = clientHandle a == clientHandle b

instance Show Client where
  show client = printf "%s:%s" (clientHost client) (show $ clientPort client)

data Action
  = Send Client String
  | Register Client
  | Unregister Client

mkClient :: (Handle, HostName, PortNumber) -> Client
mkClient (conn, host, port) = Client conn host port

main =
  withSocketsDo $ do
    port <- maybe defaultPort read . listToMaybe <$> getArgs
    socket <- listenOn (PortNumber (fromIntegral port))
    control <- newChan
    forkIO $ dispatcher control []
    forever $ do
      client <- mkClient <$> accept socket
      writeChan control (Register client)
      forkIO $ serve control client

serve ctrl client = do
  let conn = clientHandle client
  isEOF <- hIsEOF conn
  if isEOF
    then writeChan ctrl (Unregister client) >> hClose conn
    else hGetLine conn >>= writeChan ctrl . Send client >> serve ctrl client

dispatcher ctrl clients = do
  action <- readChan ctrl
  clients' <-
    case action of
      Send from str -> do
        printf "%s says: %s\n" (show from) (show str)
        mapM_ (send str) (delete from clients)
        return clients
      Register client -> do
        printf "%s entered the chat\n" (show client)
        return $ client : clients
      Unregister client -> do
        printf "%s left the chat\n" (show client)
        return $ delete client clients
  dispatcher ctrl clients'

send message client = do
  let conn = clientHandle client
  hPutStrLn conn message
  hFlush conn
