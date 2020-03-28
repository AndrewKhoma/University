import qualified Data.ByteString      as S
import qualified Data.ByteString.Lazy as B
import           Data.Ord             (comparing)
import           Test.Tasty           (defaultMain, testGroup)
import           Test.Tasty.HUnit     (assertEqual, assertFailure, testCase)

import           Data.List            (sortBy)

import           Huffman

main = defaultMain allTests

allTests = testGroup "Huffman tests" [huffmanWithoutEncryptionTest, huffmanWithEncryptionTest]

huffmanWithoutEncryptionTest =
  testCase "Huffman without encryption" $ do
    let frequencies = histogram "Check huffman without encryption"
    let sortedFrequencies = sortBy (comparing swap) frequencies
    let huffmanTree = sortedHuffman sortedFrequencies
    let encoding = codes huffmanTree
    let encoded = map (encode encoding) ["Check huffman without encryption"]
    assertEqual "Dectypted equals encrypted" ["Check huffman without encryption"] (map (decode huffmanTree) encoded)

huffmanWithEncryptionTest =
  testCase "Huffman with encryption" $ do
    let frequencies = histogram "Check huffman with encryption"
    let sortedFrequencies = sortBy (comparing swap) frequencies
    let huffmanTree = sortedHuffman sortedFrequencies
    let encoding = codes huffmanTree
    let encoded = map (encode encoding) ["Check huffman with encryption"]
    let encBits = padToEight (concat encoded)
    let bits = bitpack encBits
    let Right decBits = bitunpack . S.pack . B.unpack $ bits
    assertEqual "Dectypted bits equals encrypted" encBits decBits
    assertEqual "Dectypted string equals encrypted" ["Check huffman with encryption"] (map (decode huffmanTree) encoded)
