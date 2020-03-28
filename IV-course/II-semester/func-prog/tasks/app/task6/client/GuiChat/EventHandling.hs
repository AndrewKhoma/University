module GuiChat.EventHandling where

import           Control.Concurrent
import           Control.Monad
import           Graphics.Gloss.Interface.IO.Game

import           GuiChat.Canvas
import           GuiChat.Types

handleEvent _ (EventKey key Down _ pos) canvas@Canvas {cShape = shape} =
  case key of
    MouseButton LeftButton -> return $ canvas {cStart = Just pos}
    _                      -> return canvas
handleEvent send (EventKey key Up _ pos) canvas@Canvas {cShape = shape} =
  case key of
    Char '0' -> return $ canvas {cShape = SPencil}
    Char '1' -> return $ canvas {cShape = SCircle}
    Char '2' -> return $ canvas {cShape = SSquare}
    Char '3' -> return $ canvas {cShape = SRect}
    Char '4' -> return $ canvas {cShape = SCircle'}
    Char '5' -> return $ canvas {cShape = SSquare'}
    Char '6' -> return $ canvas {cShape = SRect'}
    Char 'r' -> return $ canvas {cColor = red}
    Char 'g' -> return $ canvas {cColor = green}
    Char 'b' -> return $ canvas {cColor = blue}
    Char 'm' -> return $ canvas {cColor = magenta}
    Char 'y' -> return $ canvas {cColor = yellow}
    Char 'c' -> return $ canvas {cColor = cyan}
    Char 'o' -> return $ canvas {cColor = orange}
    Char 'a' -> return $ canvas {cColor = azure}
    Char 'v' -> return $ canvas {cColor = violet}
    Char 'd' -> return $ canvas {cColor = black}
    Char 'w' -> return $ canvas {cColor = white}
    MouseButton LeftButton -> do
      when (shape /= SPencil) (putMVar send (mkImage canvas pos))
      return $ canvas {cStart = Nothing}
    _ -> return canvas
handleEvent send (EventMotion pos) canvas@Canvas {cShape = SPencil, cColor = color, cStart = Just _} = do
  putMVar send (mkImage canvas pos)
  return canvas
handleEvent _ (EventMotion pos) canvas = return $ canvas {cTo = pos}
handleEvent _ _ canvas = return canvas
