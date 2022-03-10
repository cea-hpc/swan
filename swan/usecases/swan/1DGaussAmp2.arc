<?xml version="1.0"?>
<case codename="Swan" codeversion="1.0" xml:lang="en">
	<arcane>
		<title>Swan example 1D Gaussian</title>
		<timeloop>SwanLoop</timeloop>
	</arcane>
 
	<arcane-post-processing>
 		<output-period>10</output-period>
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
				<x><n>500</n><length>1000.0</length></x>
				<y><n>5</n><length>10</length></y>
			</generator>
		</mesh>
 	</meshes>
 
	<swan>
		<x-edge-length>2.0</x-edge-length>
		<y-edge-length>2.0</y-edge-length>
		<load-bathy>false</load-bathy>
		<dini>-10.0</dini>
		<dup>-10.0</dup>
		<deltat>0.1</deltat>
		<max-iter>5000000</max-iter>
		<stop-time>30.1</stop-time>
		<load-wave>false</load-wave>
		<wave-mode>3</wave-mode>
		<l-x>200.0</l-x>
		<x0>500.0</x0>
		<y0>50.</y0>
		<amp>2.0</amp>
		<sigma>20.0</sigma>
		<epsh>1.0E-5</epsh>
		<epsu>1.0E-5</epsu>
	</swan>
</case>

