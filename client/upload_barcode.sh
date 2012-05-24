#!/bin/bash
#
# This script starts the zbarcam program, which captures video from
# the first video device and looks for QR codes.  When it finds one,
# it launches a web browser with the following URL:
#
# http://192.168.7.2:7777/UUID/XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX
#
# This script should be launched as so:
#
# zbarcam | upload_barcode.sh
#

for (( ; ; )) ; do
   read CODE;
   if [[ "$?" != "0" ]]; then 
       exit 1
   fi;

   if [[ ( "$CODE" =~ ^QR-Code: ) || ( "$CODE" =~ ^CODE-128: ) ]]; then 
       URL=${CODE/QR-Code:/};
       if [[ "$URL" =~ "BONEDONGLE.ORG" && "$URL" != "$LAST_URL" ]]; then
	   BONE_URL=${URL/BONEDONGLE.ORG/192.168.7.2:7777};
       else
	   BONE_URL=http://192.168.7.2:7777/$URL
       fi;
       echo Will launch browser to $BONE_URL
       x-www-browser -new-tab $BONE_URL &
       LAST_URL=$URL;
   else
       echo Ignoring code: $CODE;
   fi;
done;
