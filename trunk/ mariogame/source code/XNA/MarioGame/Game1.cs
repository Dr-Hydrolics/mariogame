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
    /// <summary>
    /// This is the main type for your game
    /// </summary>
    public class Game1 : Microsoft.Xna.Framework.Game
    {
        GraphicsDeviceManager graphics;
        SpriteBatch spriteBatch;
        Sprite hero;
        Map gameMap;
        Texture2D mapTexture;
        public Game1()
        {
            graphics = new GraphicsDeviceManager(this);               
            Content.RootDirectory = "Content";
        }

        /// <summary>
        /// Allows the game to perform any initialization it needs to before starting to run.
        /// This is where it can query for any required services and load any non-graphic
        /// related content.  Calling base.Initialize will enumerate through any components
        /// and initialize them as well.
        /// </summary>
        protected override void Initialize()
        {
            // TODO: Add your initialization logic here    
            Window.AllowUserResizing = true;
            //graphics.IsFullScreen = true;                        
            base.Initialize();
            graphics.PreferredBackBufferWidth = 640;//System.Windows.Forms.SystemInformation.VirtualScreen.Width;
            graphics.PreferredBackBufferHeight = 480;//System.Windows.Forms.SystemInformation.VirtualScreen.Height;
            graphics.ApplyChanges();
            //graphics.ToggleFullScreen();
        }

        /// <summary>
        /// LoadContent will be called once per game and is the place to load
        /// all of your content.
        /// </summary>
        protected override void LoadContent()
        {
            // Create a new SpriteBatch, which can be used to draw textures.
            
            // TODO: use this.Content to load your game content here
            spriteBatch = new SpriteBatch(graphics.GraphicsDevice);
         //   Texture2D tt = this.Content.Load<Texture2D>(@"Image\xna");
            Texture2D texttureHero = this.Content.Load<Texture2D>(@"Image\mario");
            hero = new Sprite(250, 250, 18, 36, 1, 5, 1, texttureHero);
            
            gameMap = new Map();
            gameMap.Init(@"Content\Image\maptiles.bmp");
            gameMap.LoadMapData(@"Content\Map\level1.map");
            gameMap.LoadBitmapMap();
        }

        /// <summary>
        /// UnloadContent will be called once per game and is the place to unload
        /// all content.
        /// </summary>
        protected override void UnloadContent()
        {
            // TODO: Unload any non ContentManager content here
        }

        /// <summary>
        /// Allows the game to run logic such as updating the world,
        /// checking for collisions, gathering input, and playing audio.
        /// </summary>
        /// <param name="gameTime">Provides a snapshot of timing values.</param>
        /// 
        double lastUpdate = 0;
        protected override void Update(GameTime gameTime)
        {
            // Allows the game to exit
            if (GamePad.GetState(PlayerIndex.One).Buttons.Back == ButtonState.Pressed)
                this.Exit();
            if (Keyboard.GetState().IsKeyDown(Keys.Escape) == true)
                this.Exit();
            // TODO: Add your update logic here
            if (gameTime.TotalGameTime.TotalMilliseconds - lastUpdate > 40)
            {
                hero.NextFrame();               
                lastUpdate = gameTime.TotalGameTime.TotalMilliseconds;
                if (left + 5 < 7680)
                {
                    left += 5;
                }
            }
            
            base.Update(gameTime);
        }

        /// <summary>
        /// This is called when the game should draw itself.
        /// </summary>
        /// <param name="gameTime">Provides a snapshot of timing values.</param>
        /// int 
        int left = 0;
        int top;
        protected override void Draw(GameTime gameTime)
        {            
            GraphicsDevice.Clear(Color.CornflowerBlue);
            // TODO: Add your drawing code here
            spriteBatch.Begin();
            gameMap.Draw(GraphicsDevice, spriteBatch, new System.Drawing.Rectangle(left, 0, 640, 480));            
            hero.Render(spriteBatch);
            spriteBatch.End();
            base.Draw(gameTime);
        }
    }
}
