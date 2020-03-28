module GuiChat.Canvas where

import           Graphics.Gloss.Data.Color
import           Graphics.Gloss.Data.Picture
import           Graphics.Gloss.Geometry.Angle
import           GuiChat.Types

emptyCanvas = Canvas {cPictures = [], cStart = Nothing, cTo = (0, 0), cShape = SCircle, cColor = black}

mkImage :: Canvas -> (Float, Float) -> Image
mkImage Canvas {cStart = Just start@(x1, y1), cTo = end@(x2, y2), cShape = shape, cColor = color} pos =
  Image imageT (rgbaOfColor color) center
  where
    radius = sqrt (width ** 2 + height ** 2)
    width = abs (x1 - x2)
    height = abs (y1 - y2)
    side = sqrt (2 * radius ** 2)
    rotation = 45 - radToDeg (atan ((y1 - y2) / (x1 - x2)))
    (imageT, center) =
      case shape of
        SCircle  -> (TCircle radius, start)
        SCircle' -> (TCircle' radius, start)
        SSquare  -> (TSquare side rotation, start)
        SSquare' -> (TSquare' side rotation, start)
        SRect    -> (TRect width height, ((x1 + x2) / 2, (y1 + y2) / 2))
        SRect'   -> (TRect' width height, ((x1 + x2) / 2, (y1 + y2) / 2))
        SPencil  -> (TCircle' 3, pos)

mkPicture :: Image -> Picture
mkPicture (Image t (r, g, b, a) (x, y)) =
  adjust $
  case t of
    TCircle r    -> Circle r
    TCircle' r   -> circleSolid r
    TRect a b    -> rectangleWire a b
    TRect' a b   -> rectangleSolid a b
    TSquare a r  -> Rotate r $ rectangleWire a a
    TSquare' a r -> Rotate r $ rectangleSolid a a
  where
    adjust = Translate x y . Color (makeColor r g b a)

renderCanvas cvs@Canvas {cPictures = pics, cStart = start, cTo = to@(x, y), cShape = shape, cColor = color}
  | shape == SPencil = return $ Pictures (pics ++ [Color color $ Translate x y $ circleSolid 3])
  | (Just _) <- start = return $ Pictures (pics ++ [mkPicture (mkImage cvs to)])
  | otherwise = return $ Pictures pics
