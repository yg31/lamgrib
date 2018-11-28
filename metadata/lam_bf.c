#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "grib_api.h"

/*
 * Test encoding of LAM spectral fields
 * v1.0 philippe.marguinaud 02/2016
 * v1.01 yann.genin 11/2018
 */


#define ILCHAM 3128 
#define NSTRON   10
#define NSMAX    31
#define NMSMAX   31

int main (int argc, char * argv[])
{
  grib_handle * h;
  size_t len;
  const char * grids[] = {"lambert_bf", "mercator_bf", "polar_stereographic_bf"};
  int igrid;
  const char * f_text = argv[1];
  double * values = NULL;
  FILE * fp;
  size_t dum;
  int i;

  
  fp = fopen (f_text, "r");
  fscanf (fp, "%d %d\n", &len, &dum);
  values = (double *)malloc (sizeof (double) * len);
  for (i = 0; i < len; i++)
    fscanf (fp, "%lf\n", &values[i]);
  fclose (fp);

  for (igrid = 0; igrid < 3; igrid++)
    {
      GRIB_CHECK (((h = grib_handle_new_from_samples (NULL, "lambert_bf_grib2")) == NULL), 0);
      GRIB_CHECK (grib_set_long (h, "centre", 85), 0);
      len = strlen (grids[igrid]);
      GRIB_CHECK (grib_set_string (h, "gridType", grids[igrid], &len), 0);
      GRIB_CHECK (grib_set_long (h, "biFourierResolutionParameterN", NSMAX), 0);
      GRIB_CHECK (grib_set_long (h, "biFourierResolutionParameterM", NMSMAX), 0);
      GRIB_CHECK (grib_set_long (h, "biFourierTruncationType", 99) , 0);


      GRIB_CHECK (grib_set_long (h, "LxInMetres", 2000), 0);
      GRIB_CHECK (grib_set_long (h, "LyInMetres", 2000), 0);

      GRIB_CHECK (grib_set_long (h, "LuxInMetres", 1800), 0);
      GRIB_CHECK (grib_set_long (h, "LuyInMetres", 1800), 0);

      GRIB_CHECK (grib_set_long (h, "LcxInMetres", 100), 0);
      GRIB_CHECK (grib_set_long (h, "LcyInMetres", 100), 0);

      if (igrid == 0)
        {
          GRIB_CHECK (grib_set_double (h, "latitudeOfFirstGridPointInDegrees", 67.9372009520603), 0);
          GRIB_CHECK (grib_set_double (h, "longitudeOfFirstGridPointInDegrees", 25.1580207144963), 0);
          GRIB_CHECK (grib_set_long (h, "latitudeOfSouthernPoleInDegrees", 0), 0);
          GRIB_CHECK (grib_set_long (h, "longitudeOfSouthernPoleInDegrees", 0), 0);
          GRIB_CHECK (grib_set_double (h, "LoVInDegrees", 26.6400000000000), 0);
          GRIB_CHECK (grib_set_double (h, "Latin1InDegrees", 67.3600000000000), 0);
          GRIB_CHECK (grib_set_double (h, "Latin2InDegrees", 67.3600000000000), 0);
          GRIB_CHECK (grib_set_long (h, "projectionCentreFlag", 0), 0);
          GRIB_CHECK (grib_set_long (h, "bitsPerValue", 16) , 0);
        }
      else if (igrid == 1)
        {
          GRIB_CHECK (grib_set_double (h, "latitudeOfFirstGridPointInDegrees", 67.9372009520603), 0);
          GRIB_CHECK (grib_set_double (h, "longitudeOfFirstGridPointInDegrees", 25.1580207144963), 0);
          GRIB_CHECK (grib_set_double (h, "LaDInDegrees", 0.), 0);
          GRIB_CHECK (grib_set_double (h, "latitudeOfLastGridPointInDegrees", 72.9372009520603), 0);
          GRIB_CHECK (grib_set_double (h, "longitudeOfLastGridPointInDegrees", 29.1580207144963), 0);
          GRIB_CHECK (grib_set_double (h, "orientationOfTheGridInDegrees", 0.), 0);
        }
      else if (igrid == 2)
        {

          GRIB_CHECK (grib_set_double (h, "latitudeOfFirstGridPointInDegrees", 67.9372009520603), 0);
          GRIB_CHECK (grib_set_double (h, "longitudeOfFirstGridPointInDegrees", 25.1580207144963), 0);
          GRIB_CHECK (grib_set_double (h, "LaDInDegrees", 0.), 0);
          GRIB_CHECK (grib_set_double (h, "orientationOfTheGridInDegrees", 0.), 0);
        }
     
      len = strlen ("bifourier_complex");
      GRIB_CHECK (grib_set_string (h, "packingType", "bifourier_complex", &len), 0);
      GRIB_CHECK (grib_set_long (h, "biFourierResolutionSubSetParameterN", NSTRON), 0);
      GRIB_CHECK (grib_set_long (h, "biFourierResolutionSubSetParameterM", NSTRON), 0);
      GRIB_CHECK (grib_set_long (h, "biFourierSubTruncationType", 77) , 0);
      GRIB_CHECK (grib_set_long (h, "biFourierDoNotPackAxes", 1), 0);
      GRIB_CHECK (grib_set_long (h, "unpackedSubsetPrecision", 2), 0);

      len = ILCHAM;
      GRIB_CHECK (grib_set_double_array (h, "values", values, len), 0);
     
      if (1)
        {
          char f[128];
          FILE * fp;
          size_t size;
          void * buffer;
	  sprintf (f, "lam_bf_%s.grib", grids[igrid]);
          fp = fopen (f, "w");
          GRIB_CHECK (grib_get_message (h, (const void**)&buffer, &size), 0);
          fwrite (buffer, 1, size, fp);
          fclose (fp);
        }
     
      GRIB_CHECK (grib_handle_delete (h), 0);
    }

  return 0;
}
