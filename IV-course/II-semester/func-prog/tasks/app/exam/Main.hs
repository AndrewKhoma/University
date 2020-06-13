module Main where

import Data.List

data BTree a = Empty | Branch a (BTree a) (BTree a) deriving (Show)

bft :: [a] -> BTree a
bft xs = head nodes -- Breadth First Tree
  where
    nodes =
      zipWith
        g
        (map Just xs ++ repeat Nothing)
        -- true length of Empty leaves: |xs| + 1
        (pairs $ tail nodes)
    g (Just x) (lt, rt) = Branch x lt rt
    g Nothing _ = Empty
    pairs ~(a : ~(b : c)) = (a, b) : pairs c

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
  let tree = bft [1 .. 10]
  print tree
  let evenNodes = getEvenNodes tree
  print evenNodes
  -- task 2
  print "Task 2"
  print (take 100 numbers1)
  let cum_sum = scanl1 (+) numbers1
  print (take 20 cum_sum)
