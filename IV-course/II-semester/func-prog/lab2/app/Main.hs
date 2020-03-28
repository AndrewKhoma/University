module Main where

import qualified Data.ByteString      as S
import qualified Data.ByteString.Lazy as B
import           Data.List            (foldl', insertBy, sortBy)
import qualified Data.Map             as M
import           Data.Ord             (comparing)
import           Huffman

main :: IO ()
main = do
  contents <- readFile "resources/file.txt"
  contents2 <- readFile "resources/file2.txt"
  contents3 <- readFile "resources/file3.txt"
  let l = lines contents ++ lines contents2 ++ lines contents3
  let frequencies = histogram (concat l)
  putStrLn "occurrences"
  mapM_ print frequencies
  let sortedFrequencies = sortBy (comparing swap) frequencies
  putStrLn "sorted by number of occurrences"
  mapM_ print sortedFrequencies
  let huffmanTree = sortedHuffman sortedFrequencies
  putStrLn "huffman tree"
  print huffmanTree
  putStrLn "codes"
  let encoding = codes huffmanTree
  let showCode (s, bits) = show s ++ " -> " ++ showBits bits
  mapM_ (putStrLn . showCode) (M.toList encoding)
  putStrLn "encoded"
  let encoded = map (encode encoding) l
  mapM_ (print . showBits) encoded
  putStrLn "writing encoded bits to 'huffman.bin'"
  let encBits0 = padToEight (concat encoded)
  let bits = bitpack encBits0
  B.writeFile "huffman.bin" bits
  let Right encBits1 = bitunpack . S.pack . B.unpack $ bits
  print (encBits0 == encBits1)
  putStrLn "decoded"
  let decoded = map (decode huffmanTree) encoded
  print (decoded == l)
  mapM_ print decoded
