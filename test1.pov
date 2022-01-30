/**
	POV-RAY Dice Scene
	
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

#version 3.8;

global_settings 
{ 
	assumed_gamma 1.0 
	photons 
	{
	    count 2000
	    autostop 0
	    jitter .4
	    //save_file "test1_photonmap.ph"
	    load_file "test1_photonmap.ph"
	}
	#if (RAD = 1)
		radiosity { 
			pretrace_start 0.08
			pretrace_end 0.04
			count 35 
			nearest_count 10 
			error_bound 1.8 
			recursion_limit 3
			low_error_factor 0.5
			gray_threshold 0.0
			minimum_reuse 0.015
			maximum_reuse 0.2
			brightness 1.0
			adc_bailout 0.01
		}
	#end
}

/**************************** Main *****************************/
#include "mycolors.inc"
#include "mydice.inc"
#include "mylights.inc"
#declare CamLoc = <0,1.2,-8>;
#declare animate_dice =  false;
#declare animate_camera_pan = true;
#declare revolution = 360;
#declare reflect = 0.117;
#declare CameraLookAt = <0, 0.5, 0>;
#declare ReSizeBy = 0.5;
#declare Half_Start_Degree = Start_Degree/2;
#declare Plane1 = plane
{
	y, -1
	pigment 
	{
		hexagon
		color White color Black color Gray_web
	}
}
#declare MyIOR = interior { ior 1.5 dispersion_samples 32 dispersion 1.1 };

/*************************** Start local scene stuff ****************/
background { Black }
object { Plane1 finish { reflection 0.032 } }
object { Lights (false) }
camera
{
	perspective
	blur_samples 32
	aperture 0.25
	location CamLoc
	focal_point 0
	look_at CameraLookAt
	#if(animate_camera_pan = true)
		rotate -y*360*clock
	#end
}

/************************** Main Scene Objects **************************/
/* Stationary dice */
object {
	Create_Default_Dice()
	interior_texture { pigment { White } }
	interior { MyIOR }
	photons {
	  target
	  reflection on
	  refraction on
  	}
	pigment { Black transmit 0.815 }
	scale ReSizeBy
	finish { reflection reflect }
	rotate z*Start_Degree
	rotate x*Start_Degree
	rotate y*25
	translate <-2, -0.5, 0>
}

object {
	Create_Default_Dice()
	pigment { Amethyst }
	scale ReSizeBy
	finish { reflection reflect }
	rotate y*-Half_Start_Degree*3
	rotate z*Start_Degree*2
	translate <-1,-0.5,2>
}

object {
	Create_Default_Dice()
	interior_texture { pigment { White } }
	interior { MyIOR }
	photons {
	  target
	  reflection on
	  refraction on
  	}
	pigment { English_violet transmit 0.815}
	scale ReSizeBy
	finish { reflection reflect }
	rotate z*Start_Degree
	rotate y*-Half_Start_Degree*3
	translate <2, -0.5, 0>
}

/* 4 Dice stack */
union {
	object {
		Create_Default_Dice()
		pigment { Blue_Pantone }
		scale ReSizeBy
		finish { reflection reflect }
		rotate z*Start_Degree
		rotate y*-65
		translate <1.25, -0.5, 3>
	}
	
	object {
		Create_Default_Dice()
		interior_texture { pigment { White } }
		interior { MyIOR }
		photons {
		  target
		  reflection on
		  refraction on
	  	}
		pigment { White transmit 0.815 }
		scale ReSizeBy
		finish { reflection reflect }
		rotate -x*Start_Degree
		rotate y*-Half_Start_Degree
		translate <1.25, 0.5, 3.2>
	}
	
	object {
		Create_Default_Dice()
		pigment { Red }
		scale ReSizeBy
		finish { reflection reflect }
		rotate -y*-75
		translate <1.45, 1.5, 3.2>
	}
	
	object {
		Create_Default_Dice()
		interior_texture { pigment { White } }
		interior { MyIOR }
		photons {
		  target
		  reflection on
		  refraction on
	  	}
		pigment { Yellow transmit 0.9 }
		scale ReSizeBy
		finish { reflection reflect }
		rotate x*Start_Degree
		rotate z*Start_Degree
		rotate y*Half_Start_Degree
		translate <1.2, 2.5, 3.2>
	}
}

/* Animated 2 dice stack */
union {
	object {
		Create_Default_Dice()
		pigment { Black }
		scale ReSizeBy
		finish { reflection reflect }
		rotate x*Start_Degree
		rotate y*Half_Start_Degree
		translate <-0.2, 1, 0.2>
	}
	object {
		Create_Default_Dice()
		pigment { Dark_red  }
		scale ReSizeBy
		finish { reflection reflect }
	}
	translate <0,-0.5,0>
	#if(animate_dice=true)
		rotate y*revolution*clock
	#end
}

