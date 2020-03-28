{-# LANGUAGE OverloadedStrings #-}

module Main where

import           Control.Monad
import           Control.Monad.Trans.RWS
import           Data.List.Split
import           Data.Maybe                           (fromMaybe, isNothing)
import           Happstack.Server
import           Text.Blaze                           ((!))
import qualified Text.Blaze.Html4.FrameSet.Attributes as Af
import qualified Text.Blaze.Html4.Strict              as H
import qualified Text.Blaze.Html4.Strict.Attributes   as A
import           Text.Blaze.Internal
import           Text.Read                            (readMaybe)

appTemplate :: String -> [H.Html] -> H.Html -> H.Html
appTemplate title headers body =
  H.html $ do
    H.head $ do
      H.title (H.toHtml title)
      H.meta ! A.httpEquiv "Content-Type" ! A.content "text/html;charset=utf-8"
      sequence_ headers
    H.body body

generateTable :: Int -> Int -> String -> H.Html
generateTable n m color =
  H.table ! Af.bgcolor (stringValue color) ! A.border "1" ! A.style "border-collapse: collapse" $
  mapM_ (\x -> H.tr $ mapM_ (\y -> H.th (H.preEscapedString "&nbsp;&nbsp;&nbsp;")) [1 .. m]) [1 .. n]

tableHtml :: String -> ServerPart Response
tableHtml s =
  ok $
  toResponse $ do
    let url = splitOn "/" s
    if length url < 4
      then "Incorrect format. Your url should be /table/<table height>/<table width>/<color>"
      else do
        let tableHeight = readMaybe (url !! 1) :: Maybe Int
        let tableWidth = readMaybe (url !! 2) :: Maybe Int
        if isNothing tableHeight || isNothing tableWidth
          then "Can't convert to number"
          else appTemplate
                 "Table generator"
                 [H.meta ! A.name "keywords" ! A.content "happstack, blaze, html"]
                 (generateTable (fromMaybe 1 tableHeight) (fromMaybe 1 tableWidth) (url !! 3))

-- open http://localhost:8000/table/8/4/black
main :: IO ()
main = simpleHTTP nullConf $ msum [dir "table" $ uriRest $ \s -> tableHtml s]
