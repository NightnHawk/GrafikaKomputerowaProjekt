# GrafikaKomputerowa
________________________________________________________________________________________________________
Project Properites
>> C/C++
    >> General
        - Additional Include Directories
        
            source/vendor;
            
            $(SolutionDir)Dependencies\GLFW\include;
            
            $(SolutionDir)Dependencies\GLAD\include;
            
            $(SolutionDir)Dependencies\assimp\include

>> Linker
    >> General
        - Additional Library Directories
        
            $(SolutionDir)Dependencies\GLFW\lib-vc2022
            
   
>> Linker
    >> Input
        - Additional Dependencies
        
            opengl32.lib;
            
            glfw3.lib;
            
            assimp-vc143-mt.lib;
            
            %(AdditionalDependencies)

________________________________________________________________________________________________________
Camera Input:
    
    WASD - basic movement defined by direction faced (stored as m_Orientation) parallel to a horizontal plane in Euclidean space.
    
    Space - uward movement, congruent to Y axis.
    
    Shift - downward movement, congruent to Y axis.
    
    ESC - closes the window.
