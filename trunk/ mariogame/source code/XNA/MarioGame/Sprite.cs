using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Audio;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.GamerServices;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework.Media;
using Microsoft.Xna.Framework.Net;
using Microsoft.Xna.Framework.Storage;

namespace MarioGame
{
    public class Sprite
    {
        protected int mFrameDirection; //0 vertical, 1 horizontal
        protected int mLoopType; //0 loop back to begining, 1 bounce between begin and end
        protected int mLoopDirection;
        protected int mFrameCount;	// So frame trong 1 sprite
        protected int mCurFrame;	// Frame se duoc hien thi len man hinh
        protected int mDelayCount;	// So lan lap lai toi da cua 1 frame trong qua trinh chuyen frame
        protected int mCurDelay;	// Frame hien tai da lap lai duoc bao nhieu lan
        //protected MyBitmap* mImage;	//	Anh cua sprite
        // nmnhut
        protected Texture2D mImage;
        //
        protected int mFrameWidth;	// Chieu rong cua 1 frame
        protected int mFrameHeight;	// Chieu cao cua 1 frame

        public int mXPos;	// Vi tri X cua Sprite tren man hinh
        public int mYPos;	// Vi tri Y cua Sprite tren man hinh

        public Sprite(int srcX, int srcY, int Width, int Height, int frameDirection, int frameCount, int frameDelay, Texture2D image)
        {
            mXPos = srcX;
            mYPos = srcY;
            mFrameWidth = Width;
            mFrameHeight = Height;
            mFrameDirection = frameDirection;
            mFrameCount = frameCount;
            mDelayCount = frameDelay;
            mImage = image;
            mCurFrame = 0;
            mLoopType = 0;
            mCurDelay = 0;
            mLoopDirection = 1;
        }
        public Sprite(int srcX, int srcY, int Width, int Height, int frameDirection, int frameCount, int frameDelay, String bmSrpiteName)
        {
            mXPos = srcX;
            mYPos = srcY;
            mFrameWidth = Width;
            mFrameHeight = Height;
            mFrameDirection = frameDirection;
            mFrameCount = frameCount;
            mDelayCount = frameDelay;
            //mImage = new MyBitmap(bmSrpiteName);
            mCurFrame = 0;
            mLoopType = 0;
            mCurDelay = 0;
            mLoopDirection = 1;
        }
        public void SetLoopType(int loopType)
        {
        }
        public void SetCurrentFrame(int iFrame)
        {
        }
        public void NextFrame()
        {
            if (mCurDelay >= mDelayCount)
            {
                mCurDelay = 0;
                mCurFrame = (mCurFrame + 1) % mFrameCount;
            }
            else
                mCurDelay++;
        }
        public void PreviousFrame()
        {
        }
        public void SetDelay(int Delay)
        {
        }
        //public void Render(HDC pDC);		// Hien thi frame len man hinh
        public void Render(SpriteBatch spriteBatch)		// Hien thi frame len man hinh
        {
            int imageX, imageY;
            imageX = 0;
            imageY = 0;
            if (mFrameDirection == 0)
                imageY += (mCurFrame * mFrameHeight);
            else
                imageX += (mCurFrame * mFrameWidth);            
            //mImage->DrawTransparent(pDC, mXPos, mYPos, imageX, imageY, mFrameWidth, mFrameHeight, RGB(255, 0, 255));	
            spriteBatch.Draw(mImage, new Vector2(mXPos, mYPos), new Rectangle(imageX, imageY, mFrameWidth, mFrameHeight), Color.White);
        }
        public void RenderBlend(SpriteBatch spriteBatch, int alphaBlend)
        {
        }
        // public void RenderWithEllipse(HDC pDC, int alphaBlend);
        public void RenderWithEllipse(SpriteBatch spriteBatch, int alphaBlend)
        {
        }
        public void FlipFrame()
        {
        }
        public void SetPos(int x, int y)
        {
        }
        public int GetCurDelay()
        {
            return mCurDelay;
        }
        public void SetCurDelay(int curDelay)
        {
            mCurDelay = curDelay;
        }
        public int GetFrameDelay()
        {
            return mDelayCount;
        }
    }
}
