module Main where

import Data.List

data BTree a = Empty | Branch a (BTree a) (BTree a)

getEvenNodes :: (Integral a) => BTree a -> [a]
getEvenNodes = evenNodesHelper []

evenNodesHelper :: (Integral a) => [a] -> BTree a -> [a]
evenNodesHelper xs Empty = xs
evenNodesHelper xs (Branch x l r) =
  let left = evenNodesHelper xs l
      children = evenNodesHelper left r
   in if even x then x : children else children

numbers1 = 1 : map (+ 1) numbers1

main = do
  -- task 1
  print "Task 1"
  let tree =
        Branch
          2
          (Branch 3 Empty (Branch 1 (Branch 6 Empty Empty) Empty))
          (Branch 4 (Branch 2 Empty Empty) Empty)
  let evenNodes = getEvenNodes tree
  print evenNodes
  -- task 2
  print "Task 2"
  print (take 100 numbers1)
  let cum_sum = scanl1 (+) numbers1
  print (take 20 cum_sum)
