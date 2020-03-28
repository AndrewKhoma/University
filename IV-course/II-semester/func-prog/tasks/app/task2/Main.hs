module Main where

import           NeuralNetwork
import           Text.Printf

-- Test network on XOR operation
main :: IO ()
main = do
  network <- solve
  printf "1 XOR 1 = %.4f\n" (head (snd (exec network [1, 1])))
  printf "0 XOR 1 = %.4f\n" (head (snd (exec network [0, 1])))
  printf "1 XOR 0 = %.4f\n" (head (snd (exec network [1, 0])))
  printf "0 XOR 0 = %.4f\n" (head (snd (exec network [0, 0])))
