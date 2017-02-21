# CDpal
This software is used to analyze protein thermal and chemical stability data monitored by CD or fluorescence spectroscopy.
Text files in almost any format can be used as input to CDpal.
Two-state denaturation and several models for three-state denaturation are implemented.
The output are the transition midpoint temperature (Tm), change in enthalpy (ΔHm) and heat capacity (ΔCp) for thermal denaturation and transition midpoint concentration of denaturant (Cm) and the change in free energy per unit concentration of denaturant (m-value) for chemical denaturation. 
Images showing data and fitted curves can be exported in several foramts. 
CDpal is available for Windows, Mac and Linux.

Note that CDpal was originally released at:
http://liu.se/forskning/foass/tidigare-foass/patrik-lundstrom/software?l=en#CDpal
Due to recent website changes we have migrated our software to GitHub.
This repository will be used for future changes to CDpal.

Read our paper describing CDpal here:
https://www.ncbi.nlm.nih.gov/pubmed/26402034

Compilation instructions:

The current build was compiled with Qt 5.7.0 for Windows, Mac and Linux.
We cannot guarantee that a different version of Qt can be used to compile CDpal without minor modifications to the source code.
Download Qt and open the "CDpal_Multi.pro" project file.
Run qmake and then build.
