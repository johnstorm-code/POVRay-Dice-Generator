/**
	Part of POV-RAY Dice Generator/Builder
	This code does the work of managing lights in the scene
	
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

#declare lightLoc = <0, 4, 0>;
#declare light1_color = Blue;
#declare light2_color = Red;
#declare light3_color = Green;
#declare light_looklike_scale = 0.2;
#declare light_looklike_emission = 1;

#macro Create_Lookslike_Object (ShapeObject, Color, Emission, Scale)
	object { 
		ShapeObject 
		pigment { 
			Color 
		} 
		finish { 
			emission Emission
		} 
		scale Scale 
	}
#end

#macro Create_Light_Source (Location, Color, Type, Lookslike, ShowLookslike)
	light_source {
		Location
		Color
		#if(Type="spotlight")
			spotlight
		#end
		#ifdef(Lookslike)
			#if(ShowLookslike=true)
				looks_like { Lookslike }
			#end
		#end
	}
#end

/* Use above to form this macro */
#macro Lights (ShowLookslike)
	union {
		Create_Light_Source ( lightLoc+<0,0,-2>, light1_color, "spotlight", Create_Lookslike_Object(MySphere, light1_color, light_looklike_emission, light_looklike_scale ), ShowLookslike )
		Create_Light_Source ( lightLoc+<2,0,0>, light2_color, "spotlight", Create_Lookslike_Object(MySphere, light2_color, light_looklike_emission, light_looklike_scale ), ShowLookslike )
		Create_Light_Source ( lightLoc+<-2,0,0>, light3_color, "spotlight", Create_Lookslike_Object(MySphere, light3_color, light_looklike_emission, light_looklike_scale ), ShowLookslike )
	}
#end