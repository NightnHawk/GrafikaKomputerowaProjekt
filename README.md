# GrafikaKomputerowa
________________________________________________________________________________________________________
Project Properites
>> C/C++
    >> General
        - Additional Include Directories
        
            source/vendor;
            
            $(SolutionDir)Dependencies\GLFW\include;
            
            $(SolutionDir)Dependencies\GLAD\include;

>> Linker
    >> General
        - Additional Library Directories
        
            $(SolutionDir)Dependencies\GLFW\lib-vc2022
            
   
>> Linker
    >> Input
        - Additional Dependencies
        
            opengl32.lib;
            
            glfw3.lib;
