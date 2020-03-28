module Main where

import           Data.Ord
import           Data.Sort
import           System.Random
import           System.Random.Shuffle

distances = [[0, 7, 8], [9, 0, 5], [10, 3, 0]]

generateNShuffle :: Int -> Int -> IO [[Int]]
generateNShuffle 0 m = return []
generateNShuffle n m = do
  g <- newStdGen
  let n1 = shuffle' [0 .. (m - 1)] m g
  rest <- generateNShuffle (n - 1) m
  return (n1 : rest)

mutate :: [Int] -> IO [Int]
mutate gen = do
  g <- newStdGen
  let [a, b] = take 2 $ randomRs (0, length gen - 1) g
  return $
    map
      (\x ->
         if x == a
           then b
           else if x == b
                  then a
                  else x)
      gen

mutateStage :: [[Int]] -> IO [[Int]]
mutateStage population = do
  gen <- newStdGen
  let rand_nums = take (length population `div` 4) $ randomRs (0, length population - 1) gen
  mapM
    (\(i, x) ->
       if i `elem` rand_nums
         then mutate x
         else return x) $
    zip [1 ..] population

crossover :: [Int] -> [Int] -> IO ([Int], [Int])
crossover a b = do
  g <- newStdGen
  let (pivot, _) = randomR (0, length a - 1) g
  let leftB = filter (<= pivot) b
  let leftA = filter (<= pivot) a
  let rightA = filter (> pivot) a
  let rightB = filter (> pivot) b
  return (leftA ++ rightB, rightA ++ leftB)

crossoverStage :: [[Int]] -> Int -> IO [[Int]]
crossoverStage population pSize = do
  g <- newStdGen
  let a = take (pSize `div` 2) $ randomRs (0, length population - 1) g
  g <- newStdGen
  let b = take (pSize `div` 2) $ randomRs (0, length population - 1) g
  newGens <-
    foldl
      (\arr (x, y) -> do
         r_arr <- arr
         (new1, new2) <- crossover (population !! x) (population !! y)
         return (new1 : new2 : r_arr))
      (return [])
      (zip a b)
  return (population ++ newGens)

epoch n pSize distances = do
  population <- generateNShuffle pSize (length distances)
  endPopulation <- epochSim population n pSize distances
  return (head endPopulation)

epochSim :: [[Int]] -> Int -> Int -> [[Int]] -> IO [[Int]]
epochSim population 0 pSize distances = return population
epochSim population n pSize distances = do
  mutatePop <- mutateStage population
  crossoverPop <- crossoverStage mutatePop pSize
  let best = take pSize (sortOn (fitness distances) crossoverPop)
  epochSim best (n - 1) pSize distances

fitness distances a =
  snd $
  foldl
    (\(prev, dist) cur ->
       if prev == -1
         then (cur, 0)
         else (cur, dist + ((distances !! prev) !! cur)))
    (-1, -1)
    a

main :: IO ()
main = do
  nums <- generateNShuffle 5 10
  b <- crossover (head nums) (nums !! 1)
  a <- mutate [1 .. 10]
  print $ fitness distances [0 .. 2]
  print b
  print nums
  res <- epoch 15 5 distances
  print res
  print $ fitness distances res
