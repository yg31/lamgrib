# lamgrib : validation of GRIB2 templates for limited area models

The following proposal was submitted by METEO-FRANCE during the WMO IPET-DRMM-IV meeting in 2016.
The following new elements were requested:
- new geographical templates :
 - Template 3.13 : Mercator with modelling subdomains definition
 - Template 3.23 : Polar stereographic with modelling subdomains definition
 - Template 3.33 : Lambert conformal with modelling subdomains definition
 - Template 3.61 : Spectral Mercator with modelling subdomains definition
 - Template 3.62 : Spectral polar stereographic with modelling subdomains definition
 - Template 3.63 : Spectral Lambert conformal with modelling subdomains definition
- new data representation template :
 - Template 5.53 : Spectral data for limited area models - complex packing

The validation tests are splitted in two parts: 
- validation of geographical domain (section 3) - metadata
- validation of data encoding (section 5 and 7) - encoding

The tests were performed using a modified version of NCEP Wgrib2 (the modifications were collected
into the wgrib2_patch/wgrib2_2.0.5_LAM.diff file) and Eccodes (branch feature/MeteoFrance_lamOMM).
