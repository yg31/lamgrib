#!/bin/bash
paste $1 $2 |tail -n +2|\
  awk   'function abs(v) {return v < 0 ? -v : v}'\
'BEGIN{xmin=1000000;xmax=0;n=0;}'\
'{n=n+1;x=abs($1-$2);d=d+x; if(x>xmax)xmax=x;if(x<xmin)xmin=x}'\
'END{print "average difference " d/n " maximum difference " xmax " number of values " n }'
