# BEZIER-and-MESH
Design using Bezier algorithm
This package is easy to compile easy to run using the  https://developerinsider.co/ and uses the C libraries in DOS.
Once you install C in windows10, you can run the main subroutine menu_bez.exe
Make sure your files are in the correct subdirectory. The file PARAMETR.C must by well  defined.
You can design patches of 16 control points using deferent algorithms and interpolate them using subroutine BEZIER.C through the (u) parameter.
You can connect patches with the same size of control points per side using the subroutine STICKIT.C.
You can blend the connected patches using the subroutine COMPOSE.C
When the model is finished you can view it using the subroutine GRAPH_CO.C
Using the subroutine MAKE_MES.C we desing a triangle 3D mesh.
Finally the subrourine MAKEIGS.C creates an IGES file (from the mesh file) for further analysis using other packages.
