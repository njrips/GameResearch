# GameResearch

Run Process For Ubuntu Code:Blocks

  Step 1:
  
    Install Code:Blocks
  
  Step 2:
  
    Install following library
    
      sudo apt-get install libsdl2-2.0-0 libsdl2-dev libsdl2-mixer-2.0-0 libsdl2-mixer-dev libsdl2-image-2.0-0 libsdl2-image-dev libassimp3 libassimp-dev freeglut3 freeglut3-dev
      
  Step 3:
  
    Open Code:Blocks
    
    Go Settings->Compiler->Linker settings
    
    Put below linkers as to Other linker option then ok
    
      -lGL -lGLU -lglut -lassimp  -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer
