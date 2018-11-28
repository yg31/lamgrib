#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "grib_api.h"

/*
 * Test encoding of LAM gridpoint fields
 * v1.0  philippe.marguinaud@meteo.fr, 02/2016
 */


int main (int argc, char * argv[])
{
  grib_handle * h;
  const char * f_text = argv[1];
  const char * f_g1   = argv[2];
  const char * f_g2   = argv[3];
  double * values = NULL;
  FILE * fp;
  size_t size, nlon, nlat, len;
  const void * buffer = NULL;
  int err = 0;
  int i;

  if (argc != 4)
    {
      printf ("%s: text grib1 grib2\n", argv[0]);
      return 0;
    }

  fp = fopen (f_g1, "r");
  GRIB_CHECK ((h = grib_handle_new_from_file (0, fp, &err)) == NULL, 0);
  fclose (fp);

  fp = fopen (f_text, "r");
  fscanf (fp, "%ld %ld\n", &nlon, &nlat);
  len = nlon * nlat;
  values = (double *)malloc (sizeof (double) * len);
  for (i = 0; i < len; i++)
    fscanf (fp, "%lf\n", &values[i]);
  fclose (fp);

  GRIB_CHECK (grib_set_double_array (h, "values", values, len), 0);
  
  fp = fopen (f_g2, "w");
  GRIB_CHECK (grib_get_message (h, &buffer, &size), 0);
  fwrite (buffer, 1, size, fp);
  fclose (fp);
  
  GRIB_CHECK (grib_handle_delete (h), 0);

  return 0;
}
