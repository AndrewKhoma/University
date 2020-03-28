module Main where

import           Control.Monad
import           Data.IORef
import           GHC.Float
import           Graphics.UI.GLUT

myPoints :: Float -> Int -> [(GLfloat, GLfloat, GLfloat)]
myPoints r n = [(r * sin (2 * pi * k / n'), r * cos (2 * pi * k / n'), 0) | k <- [1 .. n']]
  where
    n' = fromIntegral n

dF = double2Float

display :: IORef Double -> IORef Double -> DisplayCallback
display x x1 = do
  clear [ColorBuffer]
  loadIdentity
  xm <- get x
  xm1 <- get x1
  preservingMatrix $ do
    color $ Color3 (dF 0.5) (dF 0.8) (dF 0.9)
    translate $ Vector3 (dF xm) (dF 0.0) (dF 0.0)
    renderPrimitive TriangleFan $ mapM_ (\(x, y, z) -> vertex $ Vertex3 x y z) (myPoints 0.1 60)
  preservingMatrix $ do
    color $ Color3 (dF 0.0) (dF 1.0) (dF 0.0)
    translate $ Vector3 (dF xm1) (dF 0.0) (dF 0.0)
    renderPrimitive TriangleFan $ mapM_ (\(x, y, z) -> vertex $ Vertex3 x y z) (myPoints 0.1 60)
  swapBuffers

reshape :: ReshapeCallback
reshape size = do
  viewport $= (Position 0 0, size)
  postRedisplay Nothing

idle :: IORef Double -> IORef Double -> IORef Double -> IORef Double -> IdleCallback
idle x x1 v v1 = do
  xm <- get x
  xm1 <- get x1
  when (abs (xm - xm1) < 0.2) $ do
    v $~! negate
    v1 $~! negate
  when (xm < (-0.9)) $ v $~! negate
  when (xm1 > 0.9) $ v1 $~! negate
  vm <- get v
  vm1 <- get v1
  x $~! (+ vm)
  x1 $~! (+ vm1)
  postRedisplay Nothing

main = do
  (_progName, _args) <- getArgsAndInitialize
  _window <- createWindow "Hello World"
  x <- newIORef (-0.8)
  x1 <- newIORef 0.8
  v <- newIORef 0.00018
  v1 <- newIORef (-0.00009)
  displayCallback $= display x x1
  idleCallback $= Just (idle x x1 v v1)
  mainLoop
