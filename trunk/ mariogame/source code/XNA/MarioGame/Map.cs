using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.Xna.Framework.Audio;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.GamerServices;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework.Media;
using Microsoft.Xna.Framework.Net;
using Microsoft.Xna.Framework.Storage;
using System.IO;
using System.Drawing;


namespace MarioGame
{
    public class Map
    {
        private int mapRow;   
        public static int ITRUNK = 10;
        public static int IBRICK = 1;
        public static int ICOIN = 7;
        Bitmap bmMap;
        public int MapRow
        {
            get { return mapRow; }
            set { mapRow = value; }
        }
        private int mapCol;

        public int MapCol
        {
            get { return mapCol; }
            set { mapCol = value; }
        }

        protected int[,] pMapData;
        private int tileWidth;

        public int TileWidth
        {
            get { return tileWidth; }
            set { tileWidth = value; }
        }
        private int tileHeight;

        public int TileHeight
        {
            get { return tileHeight; }
            set { tileHeight = value; }
        }

        Bitmap bmTiles;
        public Map()
        {
            mapRow = 20;
            mapCol = 300;
            pMapData = new int[mapRow, mapCol];
            tileWidth = 24;
            tileHeight = 24;
            bmTiles = null;
        }
        public Map(String bmTileName)
        {
            mapRow = 20;
            mapCol = 300;
            pMapData = new int[mapRow, mapCol];
            tileWidth = 24;
            tileHeight = 24;
            bmTiles = new Bitmap(bmTileName);
            bmTiles.MakeTransparent(bmTiles.GetPixel(0, 0));
        }

        // Properties
        //int TileWidth() const { return mTileWidth; }
        //void TileWidth(int val) { mTileWidth = val; }
        //int TileHeight() const { return mTileHeight; }
        //void TileHeight(int val) { mTileHeight = val; }
        //int MapRow() const { return mMapRow; }
        //void MapRow(int val) { mMapRow = val; }
        //int MapCol() const { return mMapCol; }
        //void MapCol(int val) { mMapCol = val; }
        public void SetValueAt(int XPos, int YPos, char val)
        {
            int iCol = XPos / tileWidth;
            int iRow = YPos / tileHeight;
            if (iRow < 0 || iRow >= mapRow || iCol < 0 || iCol >= mapCol)
                return;
            pMapData[iRow, iCol] = val;
        }
        public int GetData(int iRow, int iCol)
        {
            return pMapData[iRow, iCol];
        }
        // End Properties

        // Methods
        public int Init(String bmTileName)
        {
            if (bmTiles == null)
            {
                bmTiles = new Bitmap(bmTileName);
                bmTiles.MakeTransparent(bmTiles.GetPixel(0, 0));
                return 1;
            }
            return 0;
        }
        public int Init(Bitmap bmTileName)
        {
            if (bmTiles == null)
            {
                bmTiles = bmTileName;
                bmTiles.MakeTransparent(bmTiles.GetPixel(0, 0));
                return 1;
            }
            return 0;
        }
        public int LoadMapData(String filename)
        {
            if (pMapData == null)
                return 0;
            StreamReader reader = new StreamReader(filename);
            int i = 0;
            String line;
            while (true)
            {
                line = reader.ReadLine();
                if (line == null)
                    break;
                for (int k = 0; k < mapCol; k++)
                {
                    int temp = (int)line[k];                    
                    pMapData[i, k] = (temp - 65);
                }
                i++;
            }
            reader.Close();
            return 1;
        }
        public void LoadBitmapMap()
        {
            int w = mapCol * tileWidth;
            int h = mapRow * tileHeight;
            bmMap = new Bitmap(w, h);
            Graphics memGraphics = Graphics.FromImage(bmMap);
            int i,j;
		    for(i=0 ; i<mapRow ; i++)
				for(j=0 ; j<mapCol ; j++)
		        {
                    if (pMapData[i, j] >= 0 && pMapData[i, j] <= 30 && pMapData[i, j] != ICOIN && pMapData[i, j] != ITRUNK && pMapData[i, j] != IBRICK)
                      memGraphics.DrawImage(bmTiles, new Rectangle(j * tileWidth, i * tileHeight, tileWidth, tileHeight),  new Rectangle(pMapData[i, j] * tileWidth, 0, tileWidth, tileHeight), GraphicsUnit.Pixel);
				    //MyBitmap::DrawTransparent(dcMap,j*mTileWidth,i*mTileHeight,mTileWidth,mTileHeight,
				    //dcMapTiles,pMapData[i][j]*mTileWidth,0,RGB(255,0,255));
                }
        }
        public void Draw(GraphicsDevice graphics, SpriteBatch spriteBatch, Rectangle viewPort)
        {
            Bitmap clipBitmap = new Bitmap(viewPort.Width, viewPort.Height);
            Graphics memGraphics = Graphics.FromImage(clipBitmap);
            memGraphics.DrawImage(bmMap, new Rectangle(0, 0, viewPort.Width, viewPort.Height), viewPort, GraphicsUnit.Pixel);
            clipBitmap.MakeTransparent(System.Drawing.Color.Black);
            Texture2D texture = new Texture2D(graphics, viewPort.Width, viewPort.Height);
            System.Drawing.Imaging.BitmapData data = clipBitmap.LockBits(new System.Drawing.Rectangle(0, 0, clipBitmap.Width, clipBitmap.Height), System.Drawing.Imaging.ImageLockMode.ReadOnly, clipBitmap.PixelFormat);
            byte[] bytes = new byte[data.Height * data.Stride];            
            System.Runtime.InteropServices.Marshal.Copy(data.Scan0, bytes, 0, bytes.Length);
            texture.SetData(bytes);
            clipBitmap.UnlockBits(data);
            spriteBatch.Draw(texture, new Microsoft.Xna.Framework.Vector2(0, 0), Microsoft.Xna.Framework.Graphics.Color.White);            
            memGraphics.Dispose();
            clipBitmap.Dispose();
           
        }
        public Point GetMapSize()
        {
            return new Point(mapCol * tileWidth, mapRow * tileHeight);
        }
        //void Redraw(MyBitmap* &bmMap, int row, int col, int iTile);
        public int GetObject(int xPos, int yPos)
        {
            int row = yPos / tileHeight;
            int col = xPos / tileWidth;
            if (row < 0 || col < 0)
                return 1;
            if (row >= mapRow || col >= mapCol)
                return -1;
            if (pMapData[row, col] > 0 && pMapData[row, col] < 7)
                return 1;
            return 0;
        }
        public int GetTileIndex(int iRow, int iCol)
        {
            if (iRow >= mapRow || iCol >= mapCol)
                return -1;
            if (iRow < 0 || iCol < 0)
                return 1;
            return (int)pMapData[iRow, iCol];
        }
        public int GetTileIndexAt(int xPos, int yPos)
        {
            int row = yPos / tileHeight;
            int col = xPos / tileWidth;
            return GetTileIndex(row, col);
        }
        public Point GetPos(int iRow, int iCol)
        {
            return new Point(iCol * tileWidth, iRow * tileHeight);
        }
        public Point GetPos(Microsoft.Xna.Framework.Point idx)
        {
            return new Point(idx.X * tileWidth, idx.Y * tileHeight);
        }
        public Point GetIndex(int xPos, int yPos)
        {
            return new Point(yPos / tileHeight, xPos / tileWidth);
        }
    }
}
