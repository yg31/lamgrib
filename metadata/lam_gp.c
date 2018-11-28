#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "grib_api.h"

/*
 * Test encoding of grid-point LAM fields
 * Test FA conversion to grib_api
 * v1.0 philippe.marguinaud 02/2016
 * v1.01 yann.genin 11/2018
 */



int main (int argc, char * argv[])
{
  grib_handle * h;
  size_t len;
  const char * grids[] = {"lambert_lam", "mercator_lam", "polar_stereographic_lam"};
  int igrid;
  const char * f_text = argv[1];
  double * values = NULL;
  FILE * fp;
  size_t size, nlon, nlat;
  int i;


  fp = fopen (f_text, "r");
  fscanf (fp, "%ld %ld\n", &nlon, &nlat);
  len = nlon * nlat;
  values = (double *)malloc (sizeof (double) * len);
  for (i = 0; i < len; i++)
    fscanf (fp, "%lf\n", &values[i]);
  fclose (fp);



  for (igrid = 0; igrid < 3; igrid++)
    {
       GRIB_CHECK (((h = grib_handle_new_from_samples (NULL, "reduced_gg_ml_grib2")) == NULL), 0);
       len = strlen ("lambert_lam");
       GRIB_CHECK (grib_set_string (h, "gridType", "lambert_lam", &len), 0);
       GRIB_CHECK (grib_set_long (h, "centre", 85), 0);
       len = strlen (grids[igrid]);
       GRIB_CHECK (grib_set_string (h, "gridType", grids[igrid], &len), 0);
       GRIB_CHECK (grib_set_long (h, "Nx", 64), 0);
       GRIB_CHECK (grib_set_long (h, "Ny", 64), 0);
       GRIB_CHECK (grib_set_long (h, "iScansNegatively", 0), 0);
       GRIB_CHECK (grib_set_long (h, "jScansPositively", 1), 0);
       GRIB_CHECK (grib_set_long (h, "jPointsAreConsecutive", 0), 0);
       GRIB_CHECK (grib_set_long (h, "Nux", 53), 0);
       GRIB_CHECK (grib_set_long (h, "Nuy", 53), 0);
       GRIB_CHECK (grib_set_long (h, "Ncx", 8), 0);
       GRIB_CHECK (grib_set_long (h, "Ncy", 8), 0);

       if (igrid == 0) //lambert_lam
         {
           GRIB_CHECK (grib_set_double (h, "DxInMetres", 2500.00000000000), 0);
           GRIB_CHECK (grib_set_double (h, "DyInMetres", 2500.00000000000), 0);
           GRIB_CHECK (grib_set_double (h, "latitudeOfFirstGridPointInDegrees", 66.7684949529709), 0);
           GRIB_CHECK (grib_set_double (h, "longitudeOfFirstGridPointInDegrees", 25.1580207144963), 0);
           GRIB_CHECK (grib_set_double (h, "latitudeOfSouthernPoleInDegrees", 0.000000000000000E+000), 0);
           GRIB_CHECK (grib_set_double (h, "longitudeOfSouthernPoleInDegrees", 0.000000000000000E+000), 0);
           GRIB_CHECK (grib_set_double (h, "LaDInDegrees", 67.3600000000000), 0);
           GRIB_CHECK (grib_set_double (h, "LoVInDegrees", 26.6400000000000), 0);
           GRIB_CHECK (grib_set_double (h, "Latin1InDegrees", 67.3600000000000), 0);
           GRIB_CHECK (grib_set_double (h, "Latin2InDegrees", 67.3600000000000), 0);
           GRIB_CHECK (grib_set_long (h, "projectionCentreFlag", 0), 0);
           GRIB_CHECK (grib_set_long (h, "uvRelativeToGrid", 1), 0);
         }
       else if (igrid == 1) //mercator_lam
         {
           GRIB_CHECK (grib_set_double (h, "latitudeOfFirstGridPointInDegrees", 67.9372009520603), 0);
           GRIB_CHECK (grib_set_double (h, "longitudeOfFirstGridPointInDegrees", 25.1580207144963), 0);
           GRIB_CHECK (grib_set_double (h, "LaDInDegrees", 0.), 0);
           GRIB_CHECK (grib_set_double (h, "latitudeOfLastGridPointInDegrees", 72.9372009520603), 0);
           GRIB_CHECK (grib_set_double (h, "longitudeOfLastGridPointInDegrees", 29.1580207144963), 0);
           GRIB_CHECK (grib_set_double (h, "orientationOfTheGridInDegrees", 0.), 0);
           GRIB_CHECK (grib_set_long (h, "uvRelativeToGrid", 1), 0);
         }
       else if (igrid == 2) //polar_stereographic_lam
         {
           GRIB_CHECK (grib_set_double (h, "DxInMetres", 2500.00000000000), 0);
           GRIB_CHECK (grib_set_double (h, "DyInMetres", 2500.00000000000), 0);
           GRIB_CHECK (grib_set_double (h, "latitudeOfFirstGridPointInDegrees", 67.9372009520603), 0);
           GRIB_CHECK (grib_set_double (h, "longitudeOfFirstGridPointInDegrees", 25.1580207144963), 0);
           GRIB_CHECK (grib_set_double (h, "LaDInDegrees", 0.), 0);
           GRIB_CHECK (grib_set_double (h, "orientationOfTheGridInDegrees", 0.), 0);
         }
     

       GRIB_CHECK (grib_set_long (h, "NV", 0), 0);
       GRIB_CHECK (grib_set_long (h, "year", 2009), 0);
       GRIB_CHECK (grib_set_long (h, "month", 5), 0);
       GRIB_CHECK (grib_set_long (h, "day", 28), 0);
       GRIB_CHECK (grib_set_long (h, "hour", 0), 0);
       GRIB_CHECK (grib_set_long (h, "minute", 0), 0);
       GRIB_CHECK (grib_set_long (h, "second", 0), 0);
       len = strlen ("s");
       GRIB_CHECK (grib_set_string (h, "indicatorOfUnitOfTimeRange", "s", &len), 0);
       len = strlen ("s");
       GRIB_CHECK (grib_set_string (h, "stepUnits", "s", &len), 0);
       GRIB_CHECK (grib_set_long (h, "endStep", 3600), 0);
       GRIB_CHECK (grib_set_long (h, "bitsPerValue", 16), 0);
       len = strlen ("grid_simple");
       GRIB_CHECK (grib_set_string (h, "packingType", "grid_simple", &len), 0);
       GRIB_CHECK (grib_set_long (h, "numberOfDataPoints", 4096), 0);
       len = 4096;
       GRIB_CHECK (grib_set_double_array (h, "values", values, len), 0);

       if (1)
         {
           char f[128];
           FILE * fp;
           size_t size;
           void * buffer;
	   sprintf (f, "lam_gp_%s.grib", grids[igrid]);
           fp = fopen (f, "w");
           GRIB_CHECK (grib_get_message (h, (const void**)&buffer, &size), 0);
           fwrite (buffer, 1, size, fp);
           fclose (fp);
         }

       GRIB_CHECK (grib_handle_delete (h), 0);
    }
  return 0;
}
