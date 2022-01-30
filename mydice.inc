/**
	POV-RAY Dice Generator/Builder
	This code does the work of generating dice objects using CSG
	
    Copyright (C) 2021  John Storm

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
    
    **/

#declare Start_Degree = 90;
#declare Dots_Emission = 0.45;
#declare Dots_Reflection = 1;
#declare Dots_Scale = 0.17;
#declare Shape_Box = 1.55;

/* All Dice begin as a Box;  and all Dots in a dice are Spheres;  both are constrained to a full block (-1 to 1) with 0-coord at center */
#declare MyBox = box { -1, 1 }
#declare MySphere = sphere { 0, 1 }
	
/* A set of Dots to form a side are constructed as unions; the pattern is "laid-out" so it can (simply) be rotated to form new ones */
#macro Create_Dice(Side1_Dots_Color, Side2_Dots_Color, Side3_Dots_Color, Side4_Dots_Color, Side5_Dots_Color, Side6_Dots_Color)	
	#declare MySide_6 = union 
	{
		object { MySphere scale Dots_Scale translate <0,-0.5,-1> }
		object { MySphere scale Dots_Scale translate <0,0.5,-1> }
		object { MySphere scale Dots_Scale translate <0.5,0.5,-1> }
		object { MySphere scale Dots_Scale translate <0.5,-0.5,-1> }
		object { MySphere scale Dots_Scale translate <-0.5,0.5,-1> }
		object { MySphere scale Dots_Scale translate <-0.5,-0.5,-1> }
		rotate Start_Degree*3*x//270
	}
	#declare MySide_5 = union 
	{
		object { MySphere scale Dots_Scale translate <0,0,-1> }
		object { MySphere scale Dots_Scale translate <0.5,0.5,-1> }
		object { MySphere scale Dots_Scale translate <0.5,-0.5,-1> }
		object { MySphere scale Dots_Scale translate <-0.5,0.5,-1> }
		object { MySphere scale Dots_Scale translate <-0.5,-0.5,-1> }
		// start
	}
	#declare MySide_4 = union 
	{
		object { MySphere scale Dots_Scale translate <0.5,0.5,-1> }
		object { MySphere scale Dots_Scale translate <0.5,-0.5,-1> }
		object { MySphere scale Dots_Scale translate <-0.5,0.5,-1> }
		object { MySphere scale Dots_Scale translate <-0.5,-0.5,-1> }
		rotate -Start_Degree*y//90
	}
	#declare MySide_3 = union 
	{
		object { MySphere scale Dots_Scale translate <0,0,-1> }
		object { MySphere scale Dots_Scale translate <0.5,-0.5,-1> }
		object { MySphere scale Dots_Scale translate <-0.5,0.5,-1> }
		rotate -Start_Degree*3*y//270
	}
	#declare MySide_2 = union 
	{
		object { MySphere scale Dots_Scale translate <0,0.5,-1> }
		object { MySphere scale Dots_Scale translate <0,-0.5,-1> }
		rotate -Start_Degree*2*y//180
	}
	/* Single Dot, so it fits only by itself - NOTE: the Dot's size (scale) is overriden here */
	#declare MySide_1 = object
	{
		object { MySphere scale 0.25 translate <0,0,-1.05> }
		rotate Start_Degree*x//90
	}
	
	/* To get the dots to traverse the box at each side, simply use the result of difference between them -- this forms the Box with Dotted sides */
	#declare SideBox = difference 
	{
		object { MyBox }
		object { MySide_6 pigment { color Side6_Dots_Color } finish { emission Dots_Emission reflection Dots_Reflection } }
		object { MySide_5 pigment { color Side5_Dots_Color } finish { emission Dots_Emission reflection Dots_Reflection } }
		object { MySide_4 pigment { color Side4_Dots_Color } finish { emission Dots_Emission reflection Dots_Reflection } }
		object { MySide_3 pigment { color Side3_Dots_Color } finish { emission Dots_Emission reflection Dots_Reflection } }
		object { MySide_2 pigment { color Side2_Dots_Color } finish { emission Dots_Emission reflection Dots_Reflection } }
		object { MySide_1 pigment { color Side1_Dots_Color } finish { emission Dots_Emission reflection Dots_Reflection } } 
	}
	
	/* To obtain the "square-round" ends of the box to form the Dice, we intersect a Sphere with the dotted-box (SideBox) */
	#declare Dice = intersection 
	{
		object { MySphere scale Shape_Box }
		object { SideBox }
	}
	
	Dice
#end
/* Default with internal defined colors */
#macro Create_Default_Dice()
	Create_Dice(Amaranth_red, Celadon_blue, Byzantine, Hot_magenta, Bright_green, Middle_blue)
#end