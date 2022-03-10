<?xml version="1.0"?>
<case codename="Swan" codeversion="1.0" xml:lang="en">
	<arcane>
		<title>Swan example 2D Gaussian</title>
		<timeloop>SwanLoop</timeloop>
	</arcane>
 
	<arcane-post-processing>
 		<output-period>100</output-period>
		<output>
			<variable>H_n</variable>
			<variable>Dij_n</variable>
		</output>
	</arcane-post-processing>

 	<meshes>
		<mesh>
			<generator name="Cartesian2D">
				<nb-part-x>1</nb-part-x>
				<nb-part-y>1</nb-part-y>
				<face-numbering-version>4</face-numbering-version>
				<origin>0.0 0.0</origin>
				<x><n>2000</n><length>200000</length></x>
				<y><n>2000</n><length>200000</length></y>
			</generator>
		</mesh>
 	</meshes>
 
	<swan>
		<x-edge-length>100</x-edge-length>
		<y-edge-length>100</y-edge-length>
		<load-bathy>false</load-bathy>
		<dini>-10.0</dini>
		<dup>-10.0</dup>
		<deltat>5.0</deltat>
		<max-iter>5000000</max-iter>
		<stop-time>10000.0</stop-time>
		<load-wave>false</load-wave>
		<wave-mode>2</wave-mode>
		<l-x>200.0</l-x>
		<x0>100000.0</x0>
		<y0>100000.0</y0>
		<amp>0.02</amp>
		<sigma>10000.0</sigma>
		<epsh>1.0E-5</epsh>
		<epsu>1.0E-6</epsu>
	</swan>
</case>

