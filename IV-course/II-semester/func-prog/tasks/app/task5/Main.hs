module Main where

getNewPath :: [[Int]] -> [Int] -> [[Int]]
getNewPath graph path = map (\x -> path ++ [x]) (graph !! (path !! (length path - 1)))

bfsStep :: [[Int]] -> [[Int]] -> Int -> [[Int]] -> [[Int]]
bfsStep [] _ _ res = res
bfsStep stack graph vertex res = bfsStep newStack graph vertex newRes
  where
    newStack =
      foldl
        (\res path ->
           let newPath = getNewPath graph path
            in if newPath /= []
                 then res ++ newPath
                 else res)
        []
        stack
    newRes = res ++ filter (\p -> p !! (length p - 1) == vertex) newStack

main :: IO ()
main = do
  let graph = [[1, 2], [2], [3], []]
  print $ bfsStep [[0]] graph 3 []
