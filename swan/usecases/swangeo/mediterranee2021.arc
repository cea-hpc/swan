<?xml version="1.0"?>
<case codename="SwanGeo" codeversion="1.0" xml:lang="en">
	<arcane>
		<title>SwanGeo mediterranean sea</title>
		<timeloop>SwanGeoLoop</timeloop>
	</arcane>
 
	<arcane-post-processing>
 		<output-period>100</output-period>
		<output>
			<variable>H_n</variable>
			<variable>Hplot_n</variable>
		</output>
	</arcane-post-processing>

 	<meshes>
		<mesh>
			<generator name="Cartesian2D">
				<nb-part-x>1</nb-part-x>
				<nb-part-y>1</nb-part-y>
				<face-numbering-version>4</face-numbering-version>
				<origin>0.0 0.0</origin>
				<x><n>2883</n><length>568600</length></x>
				<y><n>2043</n><length>408600</length></y>
			</generator>
		</mesh>
 	</meshes>
 
	<swan-geo>
		<deltat>1.0</deltat>
		<max-iter>1000000</max-iter>
		<stop-time>6000.0</stop-time>
		<dx>0.004</dx>
		<dy>0.004</dy>
		<bathy-lib>
	    {
		    "waveFilename":"$ENV{HOME}/workspaces/swan/swan/data/swangeo/waveMediterrannee2021.grd",
		    "waveVarName":"z",
		    "depthFilename":"$ENV{HOME}/workspaces/swan/swan/data/swangeo/depthMediterrannee15s.grd",
		    "depthVarName":"z",
		    "lonFilename":"$ENV{HOME}/workspaces/swan/swan/data/swangeo/depthMediterrannee15s.grd",
		    "lonVarName":"x",
		    "latFilename":"$ENV{HOME}/workspaces/swan/swan/data/swangeo/depthMediterrannee15s.grd",
		    "latVarName":"y"
		}
		</bathy-lib>
	</swan-geo>
</case>

