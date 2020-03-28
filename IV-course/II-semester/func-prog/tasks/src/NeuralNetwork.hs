module NeuralNetwork where

import           Control.Monad
import           Data.List
import           System.Random
import           Text.Printf

-- Three layer perceptron which implements XOR
type Network = ([Neuron], [Neuron])

-- A neuron is made of its input weight and its threshold
type Neuron = ([Value], Value)

-- Keeps track of inputs and expected outputs
type TrainSet = ([Value], [Value])

type Value = Float

-- Sets default learning rate
defaultLearningRate :: Value
defaultLearningRate = 0.1

-- Repeat epoch till sum of squared errors for epoch is less than threshold for convergence
errorConvergence :: Value
errorConvergence = 0.001

-- Calculates output of neuron, given inputs, weight of each input and threshold value for that neuron
neuronOutput :: [Value] -> Neuron -> Value
neuronOutput inputs (weights, threshold) =
  let tot = sum (zipWith (*) inputs weights) - threshold
   in 1 / (1 + (2.7182 ** (-tot)))

-- Running whole network with input values
exec :: Network -> [Value] -> ([Value], [Value])
exec (hidden, output) inputs =
  let hiddenOutputs = map (neuronOutput inputs) hidden
      outputOutputs = map (neuronOutput hiddenOutputs) output
   in (hiddenOutputs, outputOutputs)

-- Calculates output of network and adapts weights accordingly, first for output layer then for hidden layer (backpropagation)
step :: (Network, Value) -> TrainSet -> (Network, Value)
step ((hidden, output), err) (inputs, expected) =
  let (hiddenOutputs, outputOutputs) = exec (hidden, output) inputs
      errorOutputs = zipWith (-) expected outputOutputs
      gradientOutputs = zipWith (\o d -> o * (1 - o) * d) outputOutputs errorOutputs
      newOutputs =
        zipWith
          (\(ws, t) g ->
             ( zipWith (\h w -> w + (defaultLearningRate * h * g)) hiddenOutputs ws
             , t + (defaultLearningRate * g * (-1))))
          output
          gradientOutputs
      weightsByHidden = transpose (map fst output)
      gradientHidden =
        zipWith (\o ws -> o * (1 - o) * sum (zipWith (*) ws gradientOutputs)) hiddenOutputs weightsByHidden
      newHidden =
        zipWith
          (\(ws, t) g ->
             (zipWith (\h w -> w + (defaultLearningRate * h * g)) inputs ws, t + (defaultLearningRate * g * (-1))))
          hidden
          gradientHidden
      newErr = err + sum (map (^ 2) errorOutputs)
   -- The result is new adapted network and sum of squared errors
   in ((newHidden, newOutputs), newErr)

-- Epoch is set of steps
epoch :: Network -> [TrainSet] -> (Network, Value)
epoch network = foldl step (network, 0)

-- Training is only launching epoch function repeatedly till delta is zero
train :: Network -> [TrainSet] -> Int -> (Network, Int, Value)
train network allInputs epochNb =
  let (newNetwork, delta) = epoch network allInputs
   in if delta <= errorConvergence || epochNb > 53999
        then (newNetwork, epochNb, delta)
        else train newNetwork allInputs (epochNb + 1)

-- Convert initial network to trained one
solve = do
  let n = ([([0.5, 0.4], 0.8), ([0.9, 1.0], -0.1)], [([-1.2, 1.1], 0.3)])
  let (n', e, err) = train n [([1, 1], [0]), ([0, 1], [1]), ([1, 0], [1]), ([0, 0], [0])] 1
  printf "\nNetwork: "
  print n'
  printf "Epochs: %d\n" e
  printf "Error: %.3f\n\n" err
  return n'
