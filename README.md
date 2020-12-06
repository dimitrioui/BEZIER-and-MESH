# BEZIER multi patch -and-MESH
Design surface using Bezier algorithm.
The package was initial developed in 1992.  
Easy to compile-easy to run, using the  https://developerinsider.co/ and uses the C libraries in DOS.
Once you install C in Windows10, you can compile and run the main subroutine MENU_BEZ.C (menu_bez.exe).
Make sure your files (of patches) are in the correct subdirectory. The file PARAMETR.C must be well  defined.
You can design third (3rd) degree Bezier patches of 16 control points using different algorithms (for the insertion) and interpolate them using subroutine BEZIER.C through the (STEP) parameter.
You can create a tree of patches (3rd degree) and save them on a hard disk. 
You can connect patches with the same size of control points per side using the subroutine STICKIT.C. You can connect as much pathes as you like and even the same patch to itself.
You can blend the connected patches using the subroutine COMPOSE.C This subroutine uses the variables (l,m0,m1) from I.D.Faux, M.J.Pratt "Computational geometry for design and manufactrure".
When the model is finished you can view it using the subroutine GRAPH_CO.C.
Using the subroutine MAKE_MES.C we desing a triangular 3D mesh.
You can view the mesh using the subrutine GRBEZ.C.
Finally the subrourine MAKEIGS.C creates the IGES file (from the mesh file) for further analysis using other packages.
The subroutine CURVEBEZ.C, helps you desing 3D Bezier curve and view the result.

