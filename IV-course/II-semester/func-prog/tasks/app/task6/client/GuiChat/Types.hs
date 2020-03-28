module GuiChat.Types where

import           Graphics.Gloss.Data.Color
import           Graphics.Gloss.Data.Picture

data Shape
  = SCircle
  | SRect
  | SSquare
  | SCircle'
  | SRect'
  | SSquare'
  | SPencil
  deriving (Eq, Show, Read)

data Image =
  Image ImageT (Float, Float, Float, Float) (Float, Float)
  deriving (Eq, Show, Read)

data ImageT
  = TCircle Float
  | TCircle' Float
  | TSquare Float Float
  | TSquare' Float Float
  | TRect Float Float
  | TRect' Float Float
  deriving (Eq, Show, Read)

data Canvas =
  Canvas
    { cPictures :: [Picture]
    , cStart    :: Maybe (Float, Float)
    , cTo       :: (Float, Float)
    , cShape    :: Shape
    , cColor    :: Color
    }
